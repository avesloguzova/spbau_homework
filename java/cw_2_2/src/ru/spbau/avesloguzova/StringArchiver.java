package ru.spbau.avesloguzova;

/**
 * Created by av on 5/26/15.
 */
public interface StringArchiver {
    static String requare = "";
    String archive(String raw);

    String extract(String archived);
}
