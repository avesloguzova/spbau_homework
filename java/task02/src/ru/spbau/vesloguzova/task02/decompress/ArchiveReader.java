package ru.spbau.vesloguzova.task02.decompress;

import java.io.*;
import java.util.zip.ZipInputStream;

/**
 * Class for reading files from given archive
 */
public class ArchiveReader implements Closeable {

    private final DataInputStream inputStream;

    /**
     * Creates a new ArchiveReader from path to archive
     *
     * @param path path to archive
     * @throws IOException
     */
    public ArchiveReader(String path) throws IOException {
        ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(path));
        inputStream = new DataInputStream(new BufferedInputStream(zipInputStream));
        zipInputStream.getNextEntry();
    }

    /**
     * @return
     * @throws IOException
     */
    public boolean available() throws IOException {
        return inputStream.available() > 0 && readable();
    }

    private boolean readable() throws IOException {
        inputStream.mark(1);
        int result = inputStream.read();
        inputStream.reset(); // TODO Google it!
        return result >= 0;
    }

    /**
     * @return
     * @throws IOException
     */
    public ArchiveEntry readNext() throws IOException {
        String path = inputStream.readUTF();
        int size = inputStream.readInt();
        byte[] buffer = getContents(size);
        return new ArchiveEntry(path, buffer);

    }

    /**
     * @return
     * @throws IOException
     */
    public ArchiveEntry readNextEmptyEntry() throws IOException {
        String path = inputStream.readUTF();
        int size = inputStream.readInt();
        inputStream.skipBytes(size);
        return new ArchiveEntry(path);
    }

    private byte[] getContents(int size) throws IOException {

        byte[] buffer = new byte[size];
        inputStream.readFully(buffer);
        return buffer;
    }

    /**
     * @throws IOException
     */
    @Override
    public void close() throws IOException {
        inputStream.close();
    }

}
