package ru.spbau.avesloguzova.task03;

/**
 *  Function with two arguments with T1 and T2. It's return object of type R
 */
public abstract class Function2<T1, T2, R> {

    /**
     * Apply arguments to function
     *
     * @param arg1 first argument with type T1
     * @param arg2 second argument with type T2
     * @return object of type R
     */
    public abstract R apply(T1 arg1, T2 arg2);

    /**
     * Composition with other function. Other function gets object of type R and returns object of type S.
     *
     * @param function function for composition
     * @param <S>      return type of function
     * @return Function from T1 and T2 to type S
     */
    public <S> Function2<T1, T2, S> then(final Function<? super R, S> function) {
        return new Function2<T1, T2, S>() {
            public S apply(T1 arg1, T2 arg2) {
                return function.apply(Function2.this.apply(arg1, arg2));
            }
        };
    }

    /**
     * Bind first argument of function
     *
     * @param arg1 value of argument
     * @return Function with argument of type T2
     */
    public Function<T2, R> bind1(final T1 arg1) {
        return new Function<T2, R>() {
            @Override
            public R apply(T2 arg2) {
                return Function2.this.apply(arg1, arg2);
            }
        };
    }

    /**
     * Bind second argument of function
     *
     * @param arg2 value of argument
     * @return Function with argument of type T1
     */
    public Function<T1, R> bind2(final T2 arg2) {
        return new Function<T1, R>() {
            @Override
            public R apply(T1 arg1) {
                return Function2.this.apply(arg1, arg2);
            }
        };
    }

}
