package ru.spbau.vesloguzova.task02;

import java.io.*;
import java.net.URL;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

/**
 * Compresses files or URL-pages to general archive with name
 * which passed in constructor
 * @author avesloguzova
 */
public class Compressor implements Closeable {
    private final ZipOutputStream zipOutputStream;
    private final DataOutputStream outputStream;

    /**
     * Creates a new MessageFileReader, given the name of the
     * file to read from.
     * @param outputFileName name of archive. If outputFileName is null then
     *                       a NullPointerException is thrown.
     *
     * @throws IOException if the named file exists but is a directory rather
     *                     than a regular file, does not exist but cannot be
     *                     created, or cannot be opened for any other reason.
     */
    Compressor(String outputFileName) throws IOException {

        this.zipOutputStream = new ZipOutputStream(new FileOutputStream(outputFileName, false));
        this.outputStream = new DataOutputStream(this.zipOutputStream);
        this.zipOutputStream.putNextEntry(new ZipEntry(""));
    }


    /**
     * Adds a file to the current archive
     *
     * @param file Object of File. If file is null then
     *             a NullPointerException is thrown.
     *
     * @throws ResourceUnavailableException if an I/O error occurs during reading file or
     *                                      if an SecurityException was thrown or file can't be read
     * @throws IOException if an I/O error occurs during writing to archive
     */
    void compressFile(File file) throws IOException {
        String path = FileUtils.getRelativePath(file);
        byte[] contents = FileUtils.readFile(file);
        this.outputStream.writeUTF(path);//cross-platform solution
        this.outputStream.writeInt(contents.length);
        this.outputStream.write(contents);
    }
    /**
     * Adds a web page to the current archive
     * @param url Object of URL. If file is null then
     *            a NullPointerException is thrown.
     * @throws ResourceUnavailableException if an I/O error occurs during loading page
     * @throws IOException if an I/O error occurs during writing to archive
     */
    void compressWebPage(URL url) throws IOException {
        byte[] contents;
        try (URLDataLoader loader = new URLDataLoader(url)) {
            contents = loader.load();
        } catch (IOException e) {
            throw new ResourceUnavailableException("Some I/O error occurred while reading from URL");
        }
        this.outputStream.writeUTF(Compressor.getCompressedPath(url));
        this.outputStream.writeInt(contents.length);
        this.outputStream.write(contents);


    }


    private static String getCompressedPath(URL url) {

        String path = "http" + File.separator + url.getHost();
        if (url.getPort() > 0) {
            path += ":" + url.getPort();
        }
        path += url.getPath().replaceAll("/", "_");
        return path;
    }

    /**
     * Closes output stream and archive
     * @throws IOException
     */
    @Override
    public void close() throws IOException {
        this.zipOutputStream.closeEntry();
        this.outputStream.close();
    }
}
