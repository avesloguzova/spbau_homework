package ru.spbau.avesloguzova.task03;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by sasha on 3/29/15.
 */
public final class FunctionUtils {

    /**
     * Right-associative fold of a list  that has no base case.
     *
     * @param function Function to apply T -> T -> T
     * @param <T>      list type
     * @return Function
     */
    static <T> Function<List<? extends T>, T>
    foldr(final Function2<? super T, ? super T, ? extends T> function) {
        return new Function<List<? extends T>, T>() {
            @Override
            public T apply(List<? extends T> arg) {
                if (null == arg || arg.isEmpty()) {
                    return null;
                } else if (arg.size() == 1) {
                    return arg.get(0);
                } else {
                    ListIterator<? extends T> it = arg.listIterator(arg.size());
                    T acc = it.previous();
                    while (it.hasPrevious()) {
                        acc = function.apply(acc, it.previous());
                    }
                    return acc;
                }
            }
        };
    }

    /**
     * Takes the first few items in the list
     *
     * @param count number of items to be return
     * @param <T>   list type
     * @return List size equals count if size of received list is more or equals count,
     * else return copy of received list or empty list if count less then 0
     */
    static <T> Function<List<? extends T>, List<T>>
    take(final int count) {
        return new Function<List<? extends T>, List<T>>() {
            @Override
            public List<T> apply(List<? extends T> arg) {
                List<T> results = new ArrayList<>();
                int i = 0;
                for (T elem : arg) {
                    if (i < count) {
                        results.add(elem);
                        i++;
                    } else {
                        break;
                    }
                }
                return results;
            }
        };
    }


    /**
     * Applies a function to each element of given list
     *
     * @param function Function to be applied
     * @param <U>      type of argument of function and list
     * @param <V>      type of return value
     * @return Function
     */
    static <U, V> Function<List<? extends U>, List<V>> map(final Function<? super U, ? extends V> function) {
        return new Function<List<? extends U>, List<V>>() {
            @Override
            public List<V> apply(List<? extends U> arg) {
                List<V> results = new ArrayList<>();
                for (U element : arg) {
                    results.add(function.apply(element));
                }
                return results;
            }
        };
    }

    /**
     * Filters list
     *
     * @param pred predicate
     * @param <T>  type of list
     * @return filtered list
     */
    static <T> Function<List<? extends T>, List<T>>
    filter(final Predicate<? super T> pred) {
        return new Function<List<? extends T>, List<T>>() {
            @Override
            public List<T> apply(List<? extends T> arg) {
                List<T> results = new ArrayList<>();
                for (T el : arg) {
                    if (pred.apply(el)) {
                        results.add(el);
                    }
                }
                return results;
            }
        };
    }

}
