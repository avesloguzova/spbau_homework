package ru.spbau.avesloguzova.p2p.server.server;

import com.google.gson.Gson;
import org.apache.log4j.Logger;
import ru.spbau.avesloguzova.p2p.api.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 *
 * @author avesloguzova
 */
public class Backend implements AutoCloseable {

    private final static Logger LOG = Logger.getLogger(Backend.class);
    public static final String RESPONSE_TO_BAD_REQUEST = "FAIL - Bad request.";
    private AtomicBoolean isStop;
    private ThreadPoolExecutor executorService;
    private ConcurrentHashMap<String, ClientInfo> clients;
    private ConcurrentHashMap<String, BookInfo> books;
    private final int port;
    private final int backlog;
    private final int partsCount;
    private final List<ClientListener> listeners;

    public Backend(int port, int backlog, int partsCount) throws IOException {
        this.port = port;
        this.backlog = backlog;
        this.partsCount = partsCount;

        isStop = new AtomicBoolean(false);
        executorService = new ThreadPoolExecutor(10, 100, 10, TimeUnit.SECONDS, new ArrayBlockingQueue<Runnable>(200));
        clients = new ConcurrentHashMap<>();
        books = new ConcurrentHashMap<>();
        listeners = new ArrayList<>();
    }

    public void start() {
        executorService.submit(() -> {
            try (ServerSocket socket = new ServerSocket(port, backlog,
                    InetAddress.getByName("localhost"))) {
                while (!isStop.get()) {
                    handle(socket.accept());
                }
            } catch (IOException e) {
                LOG.error("I/O error occurs when waiting for a connection.");
            }
        });


    }

    public void stop() {
        isStop.compareAndSet(false, true);
        executorService.shutdown();
    }

    private void handle(final Socket socket) {
        executorService.submit(() -> {
            try {
                String response = processRequest(socket);
                socket.getOutputStream().write(response.getBytes());
            } catch (IOException e) {
                LOG.warn("I/O error occurs when creating or reading the input stream, the socket is closed, the socket is not connected, or the socket input has been shutdown using");
            }
        });

    }

    private String processRequest(Socket socket) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        InetAddress address = socket.getInetAddress();
        String client = address.getCanonicalHostName();
        String request = reader.readLine();
        String response = null;
        if (request == null || request.isEmpty()) {
            response = RESPONSE_TO_BAD_REQUEST;
        } else {
            request = request.trim();
            try{
            switch (request) {
                case Protocol.CONNECT_COMMAND:
                    response = addClient(client);
                    LOG.info(String.format("Client %s connected",client));
                    break;
                case Protocol.DISCONNECT_COMMAND:
                    response = removeClient(client);
                    LOG.info(String.format("Client %s disconnected",client));
                    break;
                case Protocol.ADD_NEW_BOOK_COMMAND:
                    response = addBook(client);
                    LOG.info(String.format("New book add by client %s",client));
                    break;
                default:

                    if (request.startsWith("UPDATE")) {
                        String body = readBody(reader);
                        response = processUpdateRequest(client, request, body);
                        LOG.info(String.format("Update index by client %s",client));
                    } else {
                        if (request.startsWith("GET")) {
                            response = processGetRequest(request);
                        } else {
                            response = RESPONSE_TO_BAD_REQUEST;
                        }
                    }


            }} catch (BadRequestException e) {
                e.printStackTrace();
            }
        }
        return response;
    }

    private String addBook(String client) {
        List<Integer> range = IntStream.rangeClosed(0, partsCount)
                .boxed().collect(Collectors.toList());
        Book book = new Book(UUID.randomUUID().toString(), range);
        clients.get(client).addBook(book);
        books.putIfAbsent(book.getId(),BookInfo.getNewBookInfo(client,book));
        return String.format("OK %s",book.getId());
    }

    private String removeClient(String client) {
        for (ClientListener listener : listeners) {
            listener.disconnectHandler(client);
        }
        clients.remove(client);

        return "OK";
    }

    private String addClient(String client) {
        for (ClientListener listener : listeners) {
            listener.connectHandler(client);
        }
        clients.putIfAbsent(client, new ClientInfo());

        return "OK " + String.valueOf(partsCount);
    }

    private String processGetRequest(String request) throws BadRequestException {
        StringBuilder response = new StringBuilder();
        Gson gson = new Gson();
        if(request.equals(Protocol.GET_ALL_BOOKS_COMMAND)){
            ServerInfo info = new ServerInfo();
            info.availiableBooks = Collections.list(books.keys());
            response.append("OK\n");
            response.append(gson.toJson(info));
        }else{
            if(request.startsWith(Protocol.GET_BOOK_PREFIX)){
                String id = Protocol.parseGetBookInfoCommand(request);
                if(id == null){
                    return RESPONSE_TO_BAD_REQUEST;
                }
                Book book = new Book(id,books.get(id));
                response.append("OK\n");
                response.append(gson.toJson(book));
            }else {
                if(request.startsWith(Protocol.GET_SEED_PREFIX)){
                    String[] ids = Protocol.parseGetSeedCommand(request);
                    if(ids==null){
                        return RESPONSE_TO_BAD_REQUEST;
                    }
                    String bookId = ids[0];
                    int  partIndex = Integer.valueOf(ids[1]);
                    response.append("OK\n");
                    response.append(gson.toJson(books.get(bookId).getParts().get(partIndex)));
                }else{
                    return RESPONSE_TO_BAD_REQUEST;
                }
            }
        }
        return response.toString();

    }

    private String processUpdateRequest(String client, String request, String body) throws BadRequestException {
        String response = null;
        if (body.isEmpty()) {
            response = RESPONSE_TO_BAD_REQUEST;
        } else {
            switch (request) {
                case Protocol.UPDATE_ALL_COMMAND:
                    putClientInfo(client, parseClientInfo(body));
                    break;
                case Protocol.UPDATE_BOOK_INFO_COMMAND:
                    putToBookInfo(client, parseBook(body));
                    break;
                default:
                    throw new BadRequestException("Unknown update command");
            }

        }
        return response;
    }

    private void putToBookInfo(String client, Book book) {
        clients.get(client).updateBook(book);
    }

    private Book parseBook(String body) {
        Gson gson = new Gson();
        return gson.fromJson(body, Book.class);
    }

    private void putClientInfo(String client, ClientInfo info) {
        clients.put(client, info);
        for (Book book : info.getBooks()) {
            if (!books.containsKey(book.getId())) {
                books.putIfAbsent(book.getId(), new BookInfo());
            }
            BookInfo bookInfo = books.get(book.getId());
            for (Integer part : book.getParts()) {
                if (!bookInfo.getParts().containsKey(part)) {
                    bookInfo.getParts().putIfAbsent(part, new Part(part));
                }
                bookInfo.getParts().get(part).addSeed(client);
            }
        }
    }

    private ClientInfo parseClientInfo(String body) {
        Gson gson = new Gson();
        return gson.fromJson(body, ClientInfo.class);
    }

    private String readBody(BufferedReader reader) {
        return reader.lines().reduce("", (s, s2) -> s + s2);
    }

    public Enumeration<String> getClients() {
        return clients.keys();
    }

    public ClientInfo getClientInfo(String url) {
        return clients.get(url);
    }

    public void addListener(ClientListener listener) {
        if (listener != null) {
            listeners.add(listener);
        }
    }


    @Override
    public void close() throws Exception {
        stop();
    }

    public interface ClientListener {
        void connectHandler(String clientAddress);

        void disconnectHandler(String clientAddress);
    }
}
