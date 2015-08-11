package ru.spbau.avesloguzova;

/**
 * Created by av on 5/28/15.
 */
public class UnexceptedClassException extends Exception {
    public UnexceptedClassException() {
    }

    public UnexceptedClassException(String message) {
        super(message);
    }

    public UnexceptedClassException(String message, Throwable cause) {
        super(message, cause);
    }

    public UnexceptedClassException(Throwable cause) {
        super(cause);
    }
}
