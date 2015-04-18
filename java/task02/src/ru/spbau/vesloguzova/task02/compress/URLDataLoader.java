package ru.spbau.vesloguzova.task02.compress;

import java.io.ByteArrayOutputStream;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

/**
 * Loads contents of web-page by URLConnection
 *
 * @author avesloguzova
 */
public class URLDataLoader implements Closeable {
    private static final int BUFFER_SIZE = 1024;
    final InputStream inputStream;

    public URLDataLoader(URL url) throws IOException {
        URLConnection connection = url.openConnection();
        inputStream = connection.getInputStream();
    }

    byte[] load() throws IOException {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        byte[] buffer = new byte[BUFFER_SIZE];
        int length;
        while ((length = inputStream.read(buffer)) > 0) {
            byteArrayOutputStream.write(buffer, 0, length);
        }
        return byteArrayOutputStream.toByteArray();
    }

    @Override
    public void close() throws IOException {
        inputStream.close();
    }
}
