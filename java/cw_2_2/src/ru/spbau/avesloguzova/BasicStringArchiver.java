package ru.spbau.avesloguzova;

/**
 * Created by av on 5/26/15.
 */
public class BasicStringArchiver implements StringArchiver {
    @Override
    public String archive(String raw) {
        return raw;
    }

    @Override
    public String extract(String archived) {
        return archived;
    }
}
