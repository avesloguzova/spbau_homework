package ru.spbau.vesloguzova.task02;

import ru.spbau.vesloguzova.task02.compress.Compressor;
import ru.spbau.vesloguzova.task02.compress.FileRecursiveVisitor;
import ru.spbau.vesloguzova.task02.compress.SecurityErrorHandler;
import ru.spbau.vesloguzova.task02.decompress.ArchiveViewer;
import ru.spbau.vesloguzova.task02.decompress.Decompressor;
import ru.spbau.vesloguzova.task02.exceptions.ResourceUnavailableException;

import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.List;

/**
 * Main class of application.
 */
final public class Main {

    public static final String HTTP_PREFIX = "http://";

    /**
     * Checks the args.
     * Runs compression if "compress" is first argument, second argument is name of output file
     * and following arguments is relative paths to directories/files  or valid URL.
     * Runs decompression if "decompress" is first argument and name of archive is second argument
     * Prints structure of archive if "list" is first argument and name of archive is second argument
     *
     * @param args command line arguments
     */
    public static void main(String[] args) {
        if (args.length < 2) {
            printUsageAndExit();
            return;
        }

        switch (args[0]) {
            case "compress":
                compress(args);
                break;
            case "decompress":
                decompress(args[1]);
                break;
            case "list":
                list(args[1]);
                break;
            default:
                printUsageAndExit();
                break;
        }
    }

    private static void printUsageAndExit() {
        System.out.println("Usage: task02 compress|decompress|list <filename> [paths]");
        System.exit(1);
    }

    private static void compress(String[] args) {

        FileRecursiveVisitor visitor = new FileRecursiveVisitor(new SecurityErrorHandler() {
            @Override
            public void handle(SecurityException e, String path) {
                System.err.printf("Can't read file %s. Access denied by OS or Security Manager", path);
            }
        });

        try (Compressor compressor = new Compressor(args[1])) {
            for (int i = 2; i < args.length; i++) {
                String path = args[i];

                if (isURL(path)) {
                    compressURL(compressor, path);
                } else {

                    List<File> files = visitor.getAllFilesRecursevly(new File(args[i]));
                    for (File file : files) {
                        compressFile(compressor, path, file);
                    }
                }

            }
        } catch (IOException e) {
            System.err.println("Some I/O error occurred while compressing");
        }
    }

    private static boolean isURL(String path) {
        return path.startsWith(HTTP_PREFIX);
    }

    private static void compressFile(Compressor compressor, String path, File file) throws IOException {
        try {
            compressor.compressFile(file);
        } catch (ResourceUnavailableException e) {
            System.err.printf("Can't read file from %s\n", path);
            System.err.println(e.getMessage());
            if (null != e.getCause()) {
                System.err.println(e.getCause().getMessage());
            }
        }
    }

    private static void compressURL(Compressor compressor, String path) throws IOException {
        try {
            compressor.compressWebPage(new URL(path));
        } catch (MalformedURLException e) {
            System.err.printf("The url %s is malformed\n", path);
            System.err.println(e.getMessage());
        } catch (ResourceUnavailableException e) {
            System.err.printf("Can't read data from %s\n", path);
            System.err.println(e.getMessage());
        }
    }

    private static void list(String filePath) {
        try {
            ArchiveViewer archiveReader = new ArchiveViewer(filePath);
            archiveReader.printArchiveStructure();
        } catch (IOException e) {
            System.err.println("Some I/O error occurred while reading archive or printing archive structure");
            System.err.println(e.getMessage());
        }
    }

    private static void decompress(String filePath) {
        try (Decompressor decompressor = new Decompressor(filePath)) {
            while (decompressor.available()) {
                try {
                    decompressor.decompressNextFile();
                } catch (ResourceUnavailableException e) {
                    System.err.println("Can't write file.");
                    System.err.println(e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Some I/O error occurred while reading archive");
            System.err.println(e.getMessage());
        }


    }
}
