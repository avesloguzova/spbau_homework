package ru.spbau.avesloguzova;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Array;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import java.util.concurrent.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static java.util.concurrent.Executors.newFixedThreadPool;

/**
 * Serialize and deserialize classes with default constructor and properties.
 * Each property corresponds to a getter, each writable property corresponds to a setter.
 * Serialization and deserialization occur in parallel thread.
 * There is 10 threads for all serialization and deserialization.
 *
 * @author avesloguzova
 */
public class DistributedSerializator<T> implements AutoCloseable {
    private static final String SUFFIX = ".properties";
    private static final int MAX_THREAD_COUNT = 10;
    private final ConcurrentHashMap<String, Future<T>> tasks;
    private final ConcurrentHashMap<String, Lock> fileLocks;
    private final ExecutorService threadPool;
    private Class<?> cls;

    /**
     * Creates instanse of DistributedSerializator
     */
    public DistributedSerializator() {
        tasks = new ConcurrentHashMap<>();
        fileLocks = new ConcurrentHashMap<>();
        threadPool = newFixedThreadPool(MAX_THREAD_COUNT);
    }

    /**
     * Serialize all properties of objectToSerialization to file with fileName.
     *
     * @param objectToSerialization object to serialization
     * @param fileName              name of result file
     * @return result of execution as Future<Boolean>. If computed result is true then serialization was completed successfully,
     * otherwise some error occurs.
     */
    public Future<Boolean> serialize(T objectToSerialization, String fileName) {
        if (cls == null) {
            cls = objectToSerialization.getClass();
        }
        SerializationTask task = new SerializationTask(objectToSerialization, fileName);
        return threadPool.submit(task);
    }

    /**
     * Deserialize all writable properties to new object with type T from file.
     *
     * @param fileName name of file with properties
     * @return Future<T> represents the result of an asynchronous
     * deserialization.
     */
    public Future<T> deserialize(String fileName) {
        DeserializationTask task = new DeserializationTask(fileName);
        Future<T> result = threadPool.submit(task);
        tasks.put(fileName, result);
        return result;
    }


    /**
     * Returns result of deserialization from file with fileName. If deserialization task wasn't run early
     * then will be create new task. Wait for result if deserialization task isn't competed yet.
     *
     * @param fileName name of file with properties
     * @return Object of type T
     * @throws DeserializationException if any error occurred during the deserialization
     * @throws InterruptedException     if the current thread was interrupted
     *                                  while waiting
     */
    public T get(String fileName) throws DeserializationException, InterruptedException {
        Future<T> future;
        if (tasks.containsKey(fileName)) {
            future = tasks.get(fileName);
        } else {
            tasks.putIfAbsent(fileName, deserialize(fileName));
            future = tasks.get(fileName);
        }
        try {
            return future.get();
        } catch (ExecutionException e) {
            throw new DeserializationException("An error occurred during deserialization", e);
        }
    }

    /**
     * Method to be invoked when all tasks received.
     * Initiates an orderly shutdown in which previously submitted
     * tasks are executed, but no new tasks will be accepted.
     * Invocation has no additional effect if already shut down.
     */
    public void shutdown() {
        threadPool.shutdown();
    }

    private Lock getLock(String fileName) {
        Lock lock;
        if (fileLocks.containsKey(fileName)) {
            lock = fileLocks.get(fileName);

        } else {
            lock = new ReentrantLock();
            fileLocks.putIfAbsent(fileName, lock);
            lock = fileLocks.get(fileName);
        }
        return lock;
    }

    @Override
    public void close() throws Exception {
        shutdown();
    }

    private class SerializationTask implements Callable<Boolean> {
        private final T serializationObject;
        private final String fileName;

        public SerializationTask(T o, String name) {
            serializationObject = o;
            fileName = name;
        }

        @Override
        public Boolean call() throws Exception {
            Method[] methods = serializationObject.getClass().getMethods();
            Map<String, Method> propertiesNames = getProperties(methods);
            Properties properties = new Properties();
            properties.setProperty("class", serializationObject.getClass().getCanonicalName());
            for (String property : propertiesNames.keySet()) {
                properties.setProperty(property, String.valueOf(propertiesNames.get(property).invoke(serializationObject)));
            }
            if (!Thread.interrupted()) {
                writeProperties(properties);
            }
            if (!Thread.interrupted()) {
                return true;
            } else {
                removeFile();
                return false;
            }
        }

        private void writeProperties(Properties properties) throws IOException, InterruptedException {
            Lock lock = getLock(fileName);
            try {
                lock.lockInterruptibly();
                try (FileOutputStream fileOutputStream = new FileOutputStream(fileName + SUFFIX)) {
                    properties.store(fileOutputStream, "");
                } catch (IOException e) {
                    removeFile();
                    throw e;
                }
            } catch (InterruptedException e) {
                removeFile();
                throw e;
            } finally {
                lock.unlock();
            }

        }

        private void removeFile() {
            File file = new File(fileName + SUFFIX);
            if (file.exists()) {
                //noinspection ResultOfMethodCallIgnored
                file.delete();
            }
        }

        private Map<String, Method> getProperties(Method[] methods) {
            Map<String, Method> result = new HashMap<>();
            for (Method method : methods) {
                if (isGetPropertyMethod(method)) {
                    result.put(getPropertyName(method), method);
                }
            }
            return result;
        }

        private String getPropertyName(Method method) {
            return method.getName().substring(3);
        }

        private boolean isGetPropertyMethod(Method method) {
            String name = method.getName();
            return name.startsWith("get") && !name.equals("getClass");
        }
    }

    private class DeserializationTask implements Callable<T> {
        private final String fileName;

        public DeserializationTask(String fileName) {
            this.fileName = fileName;
        }

        @Override
        public T call() throws Exception {

            Properties properties = readProperties();
            Class<?> aClass = Class.forName((String) properties.get("class"));
            checkValid(aClass);
            @SuppressWarnings("unchecked") T obj = (T) aClass.newInstance();
            Method[] methods = aClass.getMethods();
            Map<String, Method> propertiesNames = getProperties(methods);
            for (String property : propertiesNames.keySet()) {
                String value = properties.getProperty(property);
                Method method = propertiesNames.get(property);
                Class<?> parameterClass = method.getParameterTypes()[0];
                if (parameterClass.isPrimitive()) {
                    Class<?> cls = Array.get(Array.newInstance(parameterClass, 1), 0).getClass();
                    method.invoke(obj, cls.getConstructor(String.class).newInstance(value));
                } else {
                    method.invoke(obj, value);
                }
            }
            return obj;
        }

        private void checkValid(Class<?> aClass) throws DeserializationException, UnexceptedClassException {
            if (cls != null) {
                if (!aClass.equals(cls)) {
                    throw new UnexceptedClassException(String.format("Unexpected Class. Class %s expected, class %s given", cls.getCanonicalName(), aClass.getCanonicalName()));
                }
            }
        }

        private Properties readProperties() throws IOException, InterruptedException {
            Lock lock = getLock(fileName);
            try {
                lock.lockInterruptibly();
                try (FileInputStream inputStream = new FileInputStream(fileName + SUFFIX)) {
                    Properties properties = new Properties();
                    properties.load(inputStream);
                    return properties;
                }
            } finally {
                lock.unlock();
            }
        }

        private Map<String, Method> getProperties(Method[] methods) {
            Map<String, Method> result = new HashMap<>();
            for (Method method : methods) {
                if (isSetMethod(method)) {
                    result.put(getPropertyName(method), method);
                }
            }
            return result;
        }

        private boolean isSetMethod(Method method) {
            return method.getName().startsWith("set");
        }

        private String getPropertyName(Method method) {
            return method.getName().substring(3);
        }

    }
}
