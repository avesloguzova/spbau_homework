package ru.spbau.avesloguzova.task03;

/**
 * Function returns Boolean
 */
public abstract class Predicate<T> extends Function<T, Boolean> {
    /**
     * Returns predicate that is always true
     *
     * @param <T> type of predicate
     * @return Predicate
     */
    public static <T> Predicate<T> alwaysTrue() {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return true;
            }
        };
    }

    /**
     * Returns predicate that is always false
     *
     * @param <T> type of predicate
     * @return Predicate
     */
    public static <T> Predicate<T> alwaysFalse() {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return false;
            }
        };
    }

    /**
     * Returns predicate that checks its argument for being null
     *
     * @param <T> type of predicate
     * @return Predicate
     */
    public static <T> Predicate<T> notNull() {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return null != arg;
            }
        };
    }

    /**
     * Returns predicate that checks if arg1 equals arg2
     *
     * @param arg1 argument to compare with
     * @param <T>  type of arguments
     * @return Predicate
     */
    static <T extends Comparable<? super T>> Predicate<T> equals(final T arg1) {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg2) {
                return arg1.compareTo(arg2) == 0;
            }
        };
    }

    /**
     * Returns predicate that checks if arg1 less then arg2
     *
     * @param arg1 argument to compare with
     * @param <T>  type of arguments
     * @return Predicate
     */
    static <T extends Comparable<? super T>> Predicate<T> less(final T arg1) {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg2) {
                return arg1.compareTo(arg2) < 0;
            }
        };
    }

    /**
     * Inverts the predicate
     *
     * @return inverted Predicate
     */
    public Predicate<T> not() {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return !Predicate.this.apply(arg);
            }
        };
    }

    /**
     * Returns conjunction of two predicates
     *
     * @param other Predicate to conjunct
     * @return constructed Predicate
     */
    public Predicate<T> and(final Predicate<? super T> other) {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return Predicate.this.apply(arg) && other.apply(arg);
            }
        };
    }

    /**
     * Return disjunction of two predicates
     *
     * @param other Predicate to disjunct
     * @return Newly constructed predicate
     */
    public Predicate<T> or(final Predicate<? super T> other) {
        return new Predicate<T>() {
            @Override
            public Boolean apply(T arg) {
                return Predicate.this.apply(arg) || other.apply(arg);
            }
        };
    }


}
