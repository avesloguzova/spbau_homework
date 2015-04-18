package ru.spbau.vesloguzova.task02.exceptions;

import java.io.IOException;

/**
 * Wrapped exception for SecurityException and IOException
 * during while reading and writing files.It's enables to
 * check error for writing or reading single file and skip
 * it while decompressing or compressing files.
 * It's extends IOException because someone will has the ability
 * don't skip SecurityException and IOException for single file.
 *
 * @author avesloguzova
 */
public class ResourceUnavailableException extends IOException {

    /**
     * Creates exception by message and cause exception
     *
     * @param message The detail message (which is saved for later retrieval
     *                by the {@link #getMessage()} method)
     * @param cause   The cause (which is saved for later retrieval by the
     *                {@link #getCause()} method).  (A null value is permitted,
     *                and indicates that the cause is nonexistent or unknown.)
     */
    public ResourceUnavailableException(String message, Exception cause) {
        super(message, cause);
    }

    public ResourceUnavailableException(String s) {
        super(s);
    }
}
