package ru.spbau.vesloguzova.task02.decompress;

/**
 * ArchiveEntry is representation of file in archive
 */
public class ArchiveEntry {
    private final String path;
    private final byte[] buffer;

    /**
     * Creates empty archive entry with path
     *
     * @param path path to file
     */
    public ArchiveEntry(String path) {

        this.path = path;
        this.buffer = null;
    }

    /**
     * Creates ArchiveEntry with path and contents
     *
     * @param path
     * @param buffer
     */
    public ArchiveEntry(String path, byte[] buffer) {


        this.path = path;
        this.buffer = buffer;
    }


    /**
     * @return
     */
    public String getPath() {
        return path;
    }

    public byte[] getBuffer() {
        return buffer;
    }

    public boolean empty() {
        return null == buffer;
    }
}
