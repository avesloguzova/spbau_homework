package ru.spbau.vesloguzova.task01;

import java.io.Flushable;
import java.io.IOException;

/**
 * Writes messages to the "standard" output stream.
 * Example of format:
 * Message 1
 * 1.1 ...
 * 1.2 ...
 * Message 2
 * 2.1 ...
 * 2.2 ...
 * 2.3 ...
 *
 * @author avesloguzova
 */
public class ConsoleMessageWriter implements MessageWriter, Flushable {
    private int counter = 0;

    /**
     * Writes the message to the "standard" output stream
     *
     * @param message The message will be written to the standard output
     */
    @Override
    public void writeMessage(Message message) throws IOException {
        counter++;
        System.out.printf("Message %d\n", counter);
        int i = 1;
        for (String line: message.getLines()) {
            System.out.printf("%d.%d %s\n", counter, i, line);
            i++;
        }
    }

    /**
     * Flushes writer
     * @throws IOException
     */
    @Override
    public void close() throws IOException {
        flush();
    }

    /**
     * Flushes "standard" output
     * @throws IOException
     */
    @Override
    public void flush() throws IOException {
        System.out.flush();
    }
}
