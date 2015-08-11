package ru.spbau.vesloguzova.task02.utils;

/**
 * Utils class contains constants and methods to print archive structure
 *
 * @author avesloguzova
 */
public final class PrintUtils {
    /**
     * Prefix for hidden files
     */
    public static final String HIDDEN_PREFIX = ".";
    /**
     * Delimiter for prefix
     */
    public static final String STR_DELIMITER = "|";
    /**
     * Prefix for file/dir name
     */
    public static final String NAME_PREFIX = "|_";


    /**
     * Checks if the name starts with HIDDEN_PREFIX
     *
     * @param name name of file
     * @return
     */
    public static boolean hidden(String name) {
        {
            if (name.startsWith(HIDDEN_PREFIX)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Returns blank string with given length
     *
     * @param length length of string
     * @return blank string
     */
    public static String getWhiteSpaces(int length) {
        StringBuilder stringBuilder = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            stringBuilder.append(" ");
        }
        return stringBuilder.toString();
    }
}
