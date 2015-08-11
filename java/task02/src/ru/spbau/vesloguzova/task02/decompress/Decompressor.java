package ru.spbau.vesloguzova.task02.decompress;

import ru.spbau.vesloguzova.task02.utils.FileUtils;

import java.io.Closeable;
import java.io.IOException;

/**
 * Decompress file from archive with given name to current directory
 *
 * @author avesloguzova
 */
public class Decompressor implements Closeable {
    private final ArchiveReader reader;

    /**
     * Creates Decompressor by path to archive
     *
     * @param path path to archive
     * @throws IOException if an I/O error occurs during reading from archive
     */
    public Decompressor(String path) throws IOException {
        reader = new ArchiveReader(path);
    }

    /**
     * Closes archive
     *
     * @throws IOException if an I/O error occurs during closing archive
     */
    @Override
    public void close() throws IOException {
        reader.close();
    }

    /**
     * Decompress next file from archive and writes it to current directory by related path
     *
     * @throws IOException if an I/O error occurs during reading from archive
     */
    public void decompressNextFile() throws IOException {
        ArchiveEntry entry = reader.readNext();
        FileUtils.writeFile(entry.getPath(), entry.getBuffer());
    }

    /**
     * Checks is archive available to read
     *
     * @return true if archive is available for reading
     * @throws IOException if an I/O error occurs during reading from archive
     */
    public boolean available() throws IOException {
        return reader.available();
    }
}
