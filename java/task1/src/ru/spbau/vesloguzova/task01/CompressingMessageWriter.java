package ru.spbau.vesloguzova.task01;

import java.io.Closeable;
import java.io.IOException;

/**
 * CompressingMessageWriter is proxy writer that takes 2 messages, concatenates
 * them and write to specified writer.
 *
 * @author avesloguzova
 */
public class CompressingMessageWriter implements MessageWriter, Closeable {

    private final MessageWriter writer;
    private Message buffer = null;

    /**
     * Constructs a new MessageWriter with underlying writer.
     *
     * @param writer the underlying writer.
     */
    public CompressingMessageWriter(MessageWriter writer) {
        this.writer = writer;
    }

    /**
     * Writes message with compressing two messages in one.
     *
     * @param message Message to write.
     * @throws IOException if an input or output error occurs during writing messages.
     */
    @Override
    public void writeMessage(Message message) throws IOException {
        if (null == buffer) {
            buffer = new Message(message);
        } else {
            buffer.append(message);
            Message tmp = buffer;
            buffer = null;
            writer.writeMessage(tmp);

        }

    }

    /**
     * Closes the underling writer and writes buffered message.
     *
     * @throws IOException if an input or output error occurs during closing underling writer
     */
    @Override
    public void close() throws IOException {
        if (null != buffer) {
            writer.writeMessage(buffer);
        }
        writer.close();

    }
}
