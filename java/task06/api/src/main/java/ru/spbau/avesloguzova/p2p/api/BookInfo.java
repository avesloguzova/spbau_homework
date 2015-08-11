package ru.spbau.avesloguzova.p2p.api;

import java.util.concurrent.ConcurrentHashMap;

/**
 * Created by av on 6/23/15.
 */
public class BookInfo {
    private final ConcurrentHashMap<Integer,Part> parts;

    public BookInfo() {
        parts = new ConcurrentHashMap<>();
    }

    public ConcurrentHashMap<Integer, Part> getParts() {
        return parts;
    }
    public static BookInfo getNewBookInfo(String client, Book book){
        BookInfo info = new BookInfo();
        for (Integer index: book.getParts()){
            info.parts.put(index,new Part(index,client));
        }
        return info;
    }
}
