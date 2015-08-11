package ru.spbau.avesloguzova;

import java.io.File;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.*;

public class Main {


    public static void main(String[] args) {
        StressTest test = new StressTest(1);
        test.serializationThenDeserialization(5000,5000);
        test.sperializationAndDeserialization(1000);
        test.shutdown();

    }
}
class StressTest{
    public static final String TESTFILE = "testfile";
    private final ExecutorService pool;
    private final int filescount;
    private final Set<String> files;
    private final DistributedSerializator<TestClass> serializator;
    private final Random rand;

    StressTest(int maxFilesCount ){
        filescount = maxFilesCount;
        pool = Executors.newCachedThreadPool();
        files = new ConcurrentSkipListSet<>();
        serializator = new DistributedSerializator<>();
        rand = new Random();
    }
    public void serializationThenDeserialization(int serializationCount, int deserializationCount){

        for (int i = 0; i < serializationCount; i++) {
            pool.submit(new Serialization());
        }
        for (int i = 0; i < deserializationCount; i++) {
            pool.submit(new Deserialization());
        }

    }
    public void sperializationAndDeserialization(int count){
        for (int i = 0; i < count; i++) {
            pool.submit(new Serialization());
            pool.submit(new Deserialization());
        }
    }

    public void shutdown(){
        pool.shutdown();
        serializator.shutdown();
    }
    public  class Serialization implements Runnable{
        @Override
        public void run() {
            String filename = TESTFILE + String.valueOf(rand.nextInt(filescount));
            files.add(filename);
            try {
                serializator.serialize(TestClass.getRandomInstance(), filename).get();
            } catch (InterruptedException|ExecutionException e) {
                System.out.println(String.format("Serialization to file %s failed", filename));
            }
        }
    }
    public class Deserialization implements Runnable{

        @Override
        public void run() {

            String fileName = TESTFILE + String.valueOf(rand.nextInt(filescount));
            if (files.contains(fileName)){   try {
                serializator.deserialize(fileName).get();
            } catch (InterruptedException|ExecutionException e) {
                System.out.println(String.format("Serialization to file %s failed", fileName));
            }
            }
        }
    }
}