package ru.spbau.avesloguzova.p2p.api;

/**
 * Created by av on 6/25/15.
 */
public final class Protocol {
    public static final String CONNECT_COMMAND = "CONNECT";
    public static final String DISCONNECT_COMMAND = "DISCONNECT";
    public static final String UPDATE_ALL_COMMAND = "UPDATE ALL";
    public static final String UPDATE_BOOK_INFO_COMMAND = "UPDATE";
    public static final String ADD_NEW_BOOK_COMMAND = "ADD";
    public static final String GET_ALL_BOOKS_COMMAND = "GET BOOK ALL";
    public static final String GET_BOOK_PREFIX = "GET BOOK";
    public static final String GET_SEED_PREFIX = "GET SEED";

    public static String getBookInfoCommand(String bookId){
        return String.format(GET_BOOK_PREFIX + " %s",bookId);
    }
    public static String getSeedCommand(String bookId, int part){
        return String.format(GET_SEED_PREFIX + " %s %d",bookId,part);
    }


    public static String parseGetBookInfoCommand(String request){
        return null;
    }
    public static String[] parseGetSeedCommand(String request){
        return null;
    }
}
