package ru.spbau.vesloguzova.task01;

import java.io.Closeable;
import java.io.IOException;

/**
 * Interface for writing messages to character streams.
 * A subclass must implement are write(Message) and close() methods.
 *
 * @author avesloguzova
 */
public interface MessageWriter extends Closeable {
    /**
     * @param message Message to write.
     * @throws IOException if an input or output error occurs during writing messages.
     */
    void writeMessage(Message message) throws IOException;
}
