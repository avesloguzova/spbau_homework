package ru.spbau.avesloguzova.p2p.api;

import java.util.Collections;
import java.util.List;

/**
 * Created by av on 6/23/15.
 */
public class Book {
    private final String id;
    private final List<Integer> parts;

    public Book(String id, List<Integer> parts) {
        this.id = id;
        this.parts = parts;
    }

    public Book(String id,BookInfo bookInfo) {

        this.id = id;
        parts = Collections.list(bookInfo.getParts().keys());
    }

    public String getId() {
        return id;
    }

    public List<Integer> getParts() {
        return parts;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Book book = (Book) o;

        return !(id != null ? !id.equals(book.id) : book.id != null);

    }

    @Override
    public int hashCode() {
        return id != null ? id.hashCode() : 0;
    }
}
