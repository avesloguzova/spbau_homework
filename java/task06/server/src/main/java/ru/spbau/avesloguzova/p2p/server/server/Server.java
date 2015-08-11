package ru.spbau.avesloguzova.p2p.server.server;
import org.apache.log4j.Logger;

import java.io.IOException;

/**
 * Created by av on 6/23/15.
 */
public class Server {
    private final static Logger LOG = Logger.getLogger(Server.class);
    public static void main(String[] args){
       runServer(8080,100,100);
    }
    private static void runServer(int port, int backlog,int parts){
        try {
            Backend backend = new Backend(port,backlog,parts);
            backend.start();
            LOG.info(String.format("Server start on port %d",port));
        } catch (IOException e) {
            LOG.error("Can't start server",e);
        }
    }
}
