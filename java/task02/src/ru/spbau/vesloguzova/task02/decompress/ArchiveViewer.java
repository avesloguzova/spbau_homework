package ru.spbau.vesloguzova.task02.decompress;

import ru.spbau.vesloguzova.task02.utils.PrintUtils;

import java.io.IOException;
import java.util.ArrayList;

/**
 * Class for printing file structure of archive
 *
 * @author avesloguzova
 */
public class ArchiveViewer {


    private final TreeNode root;

    /**
     * @param filename path to file with archive
     * @throws IOException if an I/O error occurs during reading from archive
     */
    public ArchiveViewer(String filename) throws IOException {
        try (ArchiveReader reader = new ArchiveReader(filename)) {
            root = buidTree(reader);
        }
    }

    /**
     * Prints tree to standard output
     */
    public void printArchiveStructure() {

        for (TreeNode node : root.childs) {
            node.print(new StringBuilder());
        }
    }


    private TreeNode buidTree(ArchiveReader reader) throws IOException {
        TreeNode rootElem = new TreeNode("");
        while (reader.available()) {
            ArchiveEntry elem = reader.readNextEmptyEntry();
            String[] path = elem.getPath().split("/");
            rootElem.addToChilds(path, 0);

        }
        rootElem.setLast();
        return rootElem;
    }

    private static class TreeNode {
        final ArrayList<TreeNode> childs;
        final String name;
        boolean isLast;

        public TreeNode(String name) {
            this.name = name;
            childs = new ArrayList<>();
        }

        public void addToChilds(String[] path, int i) {
            if (i >= path.length)
                return;
            int index = exists(path[i]);
            if (index >= 0) {
                childs.get(index).addToChilds(path, i + 1);
            } else {
                TreeNode node = new TreeNode(path[i]);
                childs.add(node);
                node.addToChilds(path, i + 1);
            }
        }

        private int exists(String name) {
            for (int j = 0; j < childs.size(); j++) {
                if (childs.get(j).name.equals(name)) {
                    return j;
                }
            }
            return -1;
        }

        public void setLast() {
            if (!childs.isEmpty()) {
                this.isLast = true;
                childs.get(childs.size() - 1).setLast();
            }
        }

        public void print(StringBuilder prefix) {
            if (PrintUtils.hidden(name)) {
                return;
            }
            if (isLast) {
                System.out.print(PrintUtils.getWhiteSpaces(prefix.length()));
                prefix.append(PrintUtils.getWhiteSpaces(name.length() + 1));
            } else {
                System.out.print(prefix.toString());
                prefix.append(PrintUtils.STR_DELIMITER).append(PrintUtils.getWhiteSpaces(name.length() + 1));
            }
            System.out.println(PrintUtils.NAME_PREFIX + name);
            for (TreeNode node : childs) {
                node.print(new StringBuilder(prefix));
            }
        }
    }
}
