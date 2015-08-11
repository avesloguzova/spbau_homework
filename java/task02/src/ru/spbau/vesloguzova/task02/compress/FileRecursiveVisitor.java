package ru.spbau.vesloguzova.task02.compress;

import java.io.File;
import java.util.LinkedList;
import java.util.List;

/**
 * @author avesloguzova
 */
public class FileRecursiveVisitor {
    private final SecurityErrorHandler handler;

    /**
     * Creates FileRecursiveVisitor by handler of SecurityException
     *
     * @param handler
     */
    public FileRecursiveVisitor(SecurityErrorHandler handler) {
        this.handler = handler;

    }

    /**
     * Recursive visit directory and collect all visible files. If SecurityException was thrown handle it by handler.
     *
     * @param dir Directory
     * @return List of files
     */
    public List<File> getAllFilesRecursevly(File dir) {
        List<File> files = new LinkedList<>();
        try {
            if (dir.isDirectory()) {
                File[] fileList = dir.listFiles();
                if (null != fileList) {
                    for (File file : fileList) {
                        files.addAll(getAllFilesRecursevly(file));
                    }
                }
            } else {
                if (dir.exists()) {
                    files.add(dir);
                }
            }
        } catch (SecurityException e) {
            if (null != handler) {
                handler.handle(e, dir.getPath());
            } else {
                throw e;
            }
        }
        return files;
    }
}
