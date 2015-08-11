package ru.spbau.avesloguzova;

/**
 * Created by av on 5/26/15.
 */
public class DeserializationException extends Exception {
    public DeserializationException() {
    }

    public DeserializationException(String message) {
        super(message);
    }

    public DeserializationException(String message, Throwable cause) {
        super(message, cause);
    }

    public DeserializationException(Throwable cause) {
        super(cause);
    }
}
