package ru.spbau.vesloguzova.task02;

import java.io.*;
import java.util.LinkedList;
import java.util.List;
import java.util.zip.ZipInputStream;

/**
 *
 */
public class Decompressor implements Closeable {

    private final DataInputStream inputStream;

    public Decompressor(String inFilename) throws IOException {
        ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(inFilename));
        inputStream = new DataInputStream(new BufferedInputStream(zipInputStream));
        zipInputStream.getNextEntry();
    }

    void printArchiveStructure() throws IOException {
        List<String> paths = new LinkedList<>();
        while (inputStream.available() > 0) {
            String path = inputStream.readUTF();
            int size = inputStream.readInt();
            inputStream.skipBytes(size);
            paths.add(path);
        }
        PrintTreeUtils.printTree(paths);
    }

    public boolean available() throws IOException {
        return inputStream.available() > 0;
    }

    public void decompressNext() throws IOException {
        if (inputStream.available() > 0) {
            String path = inputStream.readUTF();
            byte[] buffer = getContents();
            FileUtils.writeFile(path, buffer);
        }
    }

    private byte[] getContents() throws IOException {
        int size = inputStream.readInt();
        byte[] buffer = new byte[size];
        inputStream.readFully(buffer);
        return buffer;
    }

    @Override
    public void close() throws IOException {
        inputStream.close();
    }

}
