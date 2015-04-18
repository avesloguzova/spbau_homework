package ru.spbau.vesloguzova.task02.utils;

import ru.spbau.vesloguzova.task02.exceptions.ResourceUnavailableException;

import java.io.*;

/**
 * Utils class contains methods for reading and writing files to disk
 *
 * @author avesloguzova
 */
final public class FileUtils {

    /**
     * Writes contants of buffer to file by path. Wrap exceptions into ResourceUnavailableException.
     *
     * @param path   path to file
     * @param buffer content of file
     * @throws ResourceUnavailableException
     */
    static public void writeFile(String path, byte[] buffer) throws ResourceUnavailableException {

        File parent = (new File(path)).getParentFile();

        if (null != parent && parent.mkdirs() && !parent.canWrite()) {
            throw new ResourceUnavailableException("Access denied to " + parent.getAbsolutePath() + " by OS.");

        } else {
            try (FileOutputStream out = new FileOutputStream(path)) {
                out.write(buffer);
            } catch (IOException e) {
                throw new ResourceUnavailableException("Some I/O error occurred while writing file " + path);
            }
        }


    }

    /**
     * Reads contents of file to byte array. Wrap exceptions into ResourceUnavailableException.
     *
     * @param file
     * @return
     * @throws ResourceUnavailableException
     */
    static public byte[] readFile(File file) throws ResourceUnavailableException {
        try {
            if (file.canRead()) {
                try (DataInputStream fileInputStream = new DataInputStream(new FileInputStream(file))) {
                    byte[] data = new byte[(int) file.length()];
                    fileInputStream.readFully(data);
                    return data;
                }

            } else {
                throw new ResourceUnavailableException("Access denied by OS or SecurityManager.");
            }
        } catch (SecurityException e) {
            throw new ResourceUnavailableException("Access denied by OS or SecurityManager.", e);
        } catch (IOException e) {
            throw new ResourceUnavailableException("An error occurred while reading.", e);
        }
    }

}
