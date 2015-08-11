package ru.spbau.vesloguzova.task01;

import java.io.*;
import java.util.LinkedList;
import java.util.List;

/**
 * Reads Message from a file.
 * Message format:
 * count of lines
 * lines of messages
 * The class includes methods for reading message and closing reader.
 *
 * @author avesloguzova
 */
public class FileMessageReader implements Closeable {
    private final BufferedReader reader;
    private final String fileName;

    /**
     * Creates a new MessageFileReader, given the name of the
     * file to read from.
     *
     * @param fileName the name of the file to read from
     * @throws FileNotFoundException if the named file does not exist,
     *                               is a directory rather than a regular file,
     *                               or for some other reason cannot be opened for reading.
     */
    public FileMessageReader(String fileName) throws FileNotFoundException {
        reader = new BufferedReader(new FileReader(fileName));
        this.fileName = fileName;
    }

    /**
     * Reads message from file.
     *
     * @return The message was read from file.
     * @throws IllegalMessageFormatException if the format of file does not correct.
     * @throws IOException if an I/O error occurs during read message.
     */
    public Message readMessage() throws IllegalMessageFormatException, IOException {
        List<String> lines = new LinkedList<>();
        int lineCount;
        try {

            lineCount = Integer.parseInt(reader.readLine());
            for (int i = 0; i < lineCount; i++) {
                lines.add(reader.readLine());
            }

        } catch (EOFException e) {
            throw new IllegalMessageFormatException("Wrong message format in file \"" + fileName + "\". Unexcepted end of message.", e);
        } catch (NumberFormatException nfe) {
            throw new IllegalMessageFormatException("Wrong message format in file \"" + fileName + "\". Unknown number of lines.",nfe);
        }

        return new Message(lines);
    }

    /**
     * Tells whether file is ready to be read.
     *
     * @throws IOException if an I/O error occurs.
     */
    public boolean ready() throws IOException {
        return reader.ready();
    }

    /**
     * Closes the reader.
     *
     * @throws IOException if an I/O error occurs during closing file.
     */
    @Override
    public void close() throws IOException {
        reader.close();
    }
}
