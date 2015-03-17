package ru.spbau.vesloguzova.task02;

import java.io.IOException;

/**
 * Created by av on 3/15/15.
 */
public class ResourceUnavailableException extends IOException {
    public ResourceUnavailableException(String s, Exception e) {
        super(s,e);
    }

    public ResourceUnavailableException(String s) {
        super(s);
    }
}
