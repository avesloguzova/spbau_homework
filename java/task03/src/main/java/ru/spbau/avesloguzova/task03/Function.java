package ru.spbau.avesloguzova.task03;

/**
 * Class of function. It's get object of type T and returns object of type R
 */
public abstract class Function<T, R> {
    /**
     * Applies argument to function
     *
     * @param arg argument of type T
     * @return result of apply argument to function
     */
    abstract public R apply(T arg);

    /**
     * Composition with other function. Other function gets object of type R and returns object of type S.
     *
     * @param function function for composition
     * @param <S>      return type of function
     * @return function from type T to type S
     */
    public <S> Function<T, S> then(final Function<? super R, S> function) {
        return new Function<T, S>() {

            @Override
            public S apply(T arg) {
                return function.apply(Function.this.apply(arg));
            }
        };
    }


}
