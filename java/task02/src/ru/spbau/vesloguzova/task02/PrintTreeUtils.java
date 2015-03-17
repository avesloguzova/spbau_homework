package ru.spbau.vesloguzova.task02;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by av on 3/15/15.
 */
public class PrintTreeUtils {
    public static void main(String[] args){
        List<String> paths = new LinkedList<>();
        paths.add("dir/dirdir/dirdirdir");
        paths.add("dir/dirdir/2");
        printTree(paths);
    }
    public static void printTree(List<String> paths) {
        Collections.sort(paths);
        String[] prevPath = null;
        for (String path : paths) {
            String[] currentPath = path.split("/");
            if(checkIsHidden(currentPath))
                continue;
            if (null != prevPath) {
                StringBuilder indent = new StringBuilder();
                for (int i = 0; i < Math.min(prevPath.length, currentPath.length); i++) {
                    if (currentPath[i].equals(prevPath[i])) {
                        indent.append("|").append(getWhiteSpaces(currentPath[i].length() + 1));
                    } else {
                        printPathTail(currentPath, indent, i);
                        break;
                    }

                }
            } else {
                StringBuilder indent = new StringBuilder();
                printPathTail(currentPath, indent, 0);
            }
            prevPath = currentPath;
        }
    }

    private static boolean checkIsHidden(String[] currentPath) {
        for (String name: currentPath){
            if(name.startsWith(".")){
                return true;
            }
        }
        return false;
    }

    private static void printPathTail(String[] currentPath, StringBuilder indent, int i) {
        for (int j = i; j < currentPath.length; j++) {
            System.out.print(indent.toString());
            System.out.print("|_");
            System.out.println(currentPath[j]);
            indent.append("|").append(getWhiteSpaces(currentPath[j].length() + 1));
        }
    }

    public static String getWhiteSpaces(int length) {
        StringBuilder stringBuilder = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            stringBuilder.append(" ");
        }
        return stringBuilder.toString();
    }
}
