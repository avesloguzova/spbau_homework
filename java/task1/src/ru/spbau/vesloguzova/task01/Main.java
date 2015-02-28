package ru.spbau.vesloguzova.task01;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Main class of application
 */
public class Main {

    /**
     * Gets messages from file given the name as command line argument.
     * Writes compressed messages to file or standard output.
     * @param args command line arguments
     */
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java -jar task01.jar <input-filename> [output-filename]");
            return;
        }
        try (FileMessageReader reader = new FileMessageReader(args[0]);
             CompressingMessageWriter writer = new CompressingMessageWriter(
                     args.length > 1 ? new FileMessageWriter(args[1])
                             : new ConsoleMessageWriter())) {
            while (reader.ready()) {
                Message msg = reader.readMessage();
                writer.writeMessage(msg);
            }
        } catch (FileNotFoundException e) {
            System.err.println("Input file not found or output file is a directory rather than a regular file," +
                    " does not exist but cannot be created, or cannot be opened for any other reason .\n"
                    + e.getMessage());
            processException(e);
        } catch (IllegalMessageFormatException e) {
            System.err.println("Illegal message format was detected.\n" + e.getMessage());
            processException(e);
        } catch (IOException e) {
            System.err.println("Unexpected error while reading input or writing output.\n" + e.getMessage());
            processException(e);
        }
    }

    private static void processException(Exception exception) {
        for (Throwable e : exception.getSuppressed()) {
            System.err.println(e.getMessage());
        }

    }
}
