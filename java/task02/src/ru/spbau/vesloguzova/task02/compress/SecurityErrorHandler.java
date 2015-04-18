package ru.spbau.vesloguzova.task02.compress;

/**
 * Interface of handler of SecurityException in recursive files search
 *
 * @author avesloguzova
 */
public interface SecurityErrorHandler {
    /**
     * Handles exception occurred for file
     *
     * @param e    SecurityException
     * @param path to file throws exception
     */
    public void handle(SecurityException e, String path);
}
