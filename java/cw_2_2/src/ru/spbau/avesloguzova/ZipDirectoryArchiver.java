package ru.spbau.avesloguzova;

import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

/**
 * Created by av on 5/26/15.
 */
public class ZipDirectoryArchiver implements DirectoryArchiver {
    private final StringArchiver stringArchiver;

    public ZipDirectoryArchiver(StringArchiver stringArchiver) {

        this.stringArchiver = stringArchiver;
    }

    @Override
    public void archive(File folder, String filename) throws IOException {
        try (ZipOutputStream zipOutputStream = new ZipOutputStream(new FileOutputStream(filename, false))) {
            zipOutputStream.putNextEntry(new ZipEntry(""));
            try (DataOutputStream outputStream = new DataOutputStream(zipOutputStream)) {

                File[] files = folder.listFiles();
                for (File file : files) {
                    try (FileInputStream fis = new FileInputStream(file)) {
                        byte[] data = new byte[(int) file.length()];
                        fis.read(data);
                        fis.close();

                        String str = stringArchiver.archive(new String(data, "UTF-8"));
                        outputStream.writeUTF(file.getName());
                        outputStream.writeInt(str.length());
                        outputStream.write(str.getBytes());
                    }
                }
            }
        }

    }

    @Override
    public void extract(File folder, String filename) throws IOException {
        try (ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(filename))) {
            zipInputStream.getNextEntry();
            try (DataInputStream inputStream = new DataInputStream(new BufferedInputStream(zipInputStream))) {
                while (inputStream.available()>0){
                    String file  = inputStream.readUTF();
                    int size = inputStream.readInt();
                    byte[] data = new byte[size];
                    inputStream.readFully(data);
                    String content = new String(data, "UTF-8");
                    try(FileWriter writer = new FileWriter(folder.getPath()+file)){
                        writer.write(stringArchiver.extract(content));
                    }

                }
            }
        }

    }
}
