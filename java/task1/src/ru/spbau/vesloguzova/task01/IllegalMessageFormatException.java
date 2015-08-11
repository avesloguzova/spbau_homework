package ru.spbau.vesloguzova.task01;

/**
 * Signals that the format of the input file does not correct.
 */
public class IllegalMessageFormatException extends Exception {
    /**
     * Constructs a new exception with the specified detail message.
     *
     * @param message the detail message.
     */
    public IllegalMessageFormatException(String message) {
        super(message);
    }

    /**
     * Constructs a new exception with the specified detail message and cause.
     *
     * @param message the detail message.
     * @param cause the cause for th exception
     */
    public IllegalMessageFormatException(String message, Throwable cause) {
        super(message, cause);
    }


}
