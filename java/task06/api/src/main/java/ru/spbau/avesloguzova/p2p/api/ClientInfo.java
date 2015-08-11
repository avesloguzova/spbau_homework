package ru.spbau.avesloguzova.p2p.api;


import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Created by av on 6/23/15.
 */
public class ClientInfo {

    private final List<Book> books;

    public ClientInfo() {
        this.books = new ArrayList<>();
    }
    
    synchronized public void addBook(Book book){
        books.add(book);
    }
    synchronized public void updateBook(Book book){
        books.remove(book);
        books.add(book);
    }
    public List<Book> getBooks() {
        return Collections.unmodifiableList(books);
    }
}
