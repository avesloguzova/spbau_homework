package ru.spbau.avesloguzova;

import java.io.File;
import java.lang.reflect.Field;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by av on 5/26/15.
 */
public class PluginManager {
   Map<Class,Class[]> requares = new HashMap<>();

//    Map<String, >
    List<Class> notSatisfiedClasses = new ArrayList<>();
    List<Class> classes = new ArrayList<>();
    PluginManager(String pluginDirectory) throws MalformedURLException, ClassNotFoundException, NoSuchFieldException, IllegalAccessException {
        URLClassLoader loader = new URLClassLoader(new URL[]{new File(pluginDirectory).toURL()});
        String[] files = new File(pluginDirectory).list();

        for (String file:files){
            if(file.contains(".class")){
                Class cls = loader.loadClass(file.replace(".class",""));
                classes.add(cls);
                Field requare = cls.getField("requare");
                String value = (String) requare.get(null);
                requares.put(cls,getRequriments(value.split(",")));

            }

        }
    }

    private List<Class> getRequriments(String[] classNames) throws ClassNotFoundException {
        List<Class> result = new ArrayList<>();
        for (int i = 0; i < classNames.length; i++){
            Class<?> clazz = Class.forName(classNames[i]);
            result[i]= clazz;
        }
        return result;
    }

    <T> List<Class<? extends T>> getRealisations (Class<T> parent){
        return null;
    }
}
