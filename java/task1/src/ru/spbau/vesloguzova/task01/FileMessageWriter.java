package ru.spbau.vesloguzova.task01;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

/**
 * Writes message to file.
 * Message format:
 *      count of lines
 *      lines of messages
 */
public class FileMessageWriter implements MessageWriter {

    private final BufferedWriter writer;

    /**
     * Constructs a FileMessageWriter object given a file name
     *
     * @param filename Name of output file
     * @throws IOException if the named file exists but is a directory rather
     *                     than a regular file, does not exist but cannot be
     *                     created, or cannot be opened for any other reason.
     */
    public FileMessageWriter(String filename)
            throws IOException {
        writer = new BufferedWriter(new FileWriter(filename, false));
    }

    /**
     * Writes message to a file
     *
     * @param msg Message to write
     * @throws IOException if an input or output error occurs during writing to file.
     */
    public void writeMessage(Message msg) throws IOException {
        List<String> lines = msg.getLines();
        writer.write(Integer.toString(lines.size()));
        writer.newLine();
        for (String line : lines) {
            writer.write(line);
            writer.newLine();
        }
        writer.flush();
    }

    /**
     * Closes writer.
     *
     * @throws IOException if an input or output error occurs during closing file.
     */
    public void close() throws IOException {
        writer.close();
    }
}
