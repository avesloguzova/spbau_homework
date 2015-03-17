package ru.spbau.vesloguzova.task02;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by av on 3/14/15.
 */
final public class FileUtils {
    private static final URI currentDir = new File(".").getAbsoluteFile().toURI();

    static public void writeFile(String path, byte[] buffer) throws ResourceUnavailableException {
        File parent = (new File(path)).getParentFile();

            if (parent != null && !parent.canWrite()) {
                throw new ResourceUnavailableException("Access denied to "+parent.getAbsolutePath()+" by OS.");

            } else {
                try (FileOutputStream out = new FileOutputStream(path)) {
                    out.write(buffer);
                } catch (IOException e) {
                    throw new ResourceUnavailableException("Some I/O error occurred while writing file "+ path);
                }
            }

    }

    static public byte[] readFile(File file) throws ResourceUnavailableException {
        try{
        if (file.canRead()) {
            try (FileInputStream fileInputStream = new FileInputStream(file)) {
                byte[] data = new byte[(int) file.length()];
                fileInputStream.read(data);
                return data;
            }

        } else {
            throw new ResourceUnavailableException("Access denied by OS or SecurityManager.");
        }
        }catch (SecurityException e){
            throw new ResourceUnavailableException("Access denied by OS or SecurityManager.", e);
        }
        catch (IOException e) {
            throw new ResourceUnavailableException("An error occurred while reading.",e);
        }
    }

    static public List<File> getAllFilesRecursevly(File path) {
        List<File> files = new LinkedList<>();
        if (path.isDirectory()) {
            try {
                File[] fileList = path.listFiles();
                if (null != fileList) {
                    for (File file : fileList) {
                        if (file.isDirectory()) {
                            files.addAll(getAllFilesRecursevly(file));
                        } else files.add(file);
                    }
                }
            }catch (SecurityException e){
                //TODO
            }
        } else {
            files.add(path);
        }
        return files;
    }

    static public String getRelativePath(File file) {
        return currentDir.relativize(file.toURI()).getPath();
    }
//    public static void main(String[] args) throws MalformedURLException {
//        System.out.println(getCompressedPath(new URL("http://goole.com/yandex/yahoo")));
//    }


}
