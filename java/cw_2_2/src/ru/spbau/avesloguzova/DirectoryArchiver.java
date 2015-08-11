package ru.spbau.avesloguzova;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Created by av on 5/26/15.
 */
public interface DirectoryArchiver {
    static String requare = "StringArchiver";//requares split by ,
    void archive(File folder, String filename) throws IOException;
    void extract(File folder, String filename) throws IOException;

}
