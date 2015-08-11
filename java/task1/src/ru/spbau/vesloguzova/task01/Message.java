package ru.spbau.vesloguzova.task01;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * The Message class represents the text message.
 * The class includes methods for appending other message
 * and getting lines of message.
 *
 * @author avesloguzova
 */
public class Message {

    private final List<String> lines;

    /**
     * Constructs a message containing elements of the list.
     *
     * @param lines list contains lines
     */
    public Message(List<String> lines) {
        this.lines = new ArrayList<>(lines);
    }

    /**
     * Constructs copy of the message.
     *
     * @param message the message will be copied
     */
    public Message(Message message) {
        lines = new ArrayList<>(message.lines);
    }

    /**
     * Appends all of lines the of other message to the end of this message.
     *
     * @param message the message whose elements are to be appended
     *                into end of this message.
     */
    public void append(Message message) {
        lines.addAll(message.lines);
    }

    /**
     * Returns an unmodifiable list of lines.
     *
     * @return unmodifiable list of lines.
     */
    public List<String> getLines() {
        return Collections.unmodifiableList(lines);
    }
}
