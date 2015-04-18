package ru.spbau.avesloguzova.task03;

import java.util.Comparator;

/**
 * Comparator of elements with type T.
 * Applies function to arguments and compare results
 */
public class FunctionalComparator<T, R extends Comparable<? super R>>
        implements Comparator<T> {

    private final Function<? super T, R> function;

    /**
     * Creates comparator with function
     *
     * @param function th function to be applied to arguments of comparator
     */
    public FunctionalComparator(Function<? super T, R> function) {
        this.function = function;
    }

    /**
     * Compares its two arguments for order.  Returns
     *
     * @param arg1 the first object to be compared
     * @param arg2 the second object to be compared
     * @return a negative integer, zero, or a positive integer
     * as the first argument is less than, equal to,
     * or greater than the second
     */
    @Override
    public int compare(T arg1, T arg2) {
        R obj1 = function.apply(arg1);
        R obj2 = function.apply(arg2);
        return obj1.compareTo(obj2);
    }
}
