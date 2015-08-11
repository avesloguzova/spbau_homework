package ru.spbau.avesloguzova.task03;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Function Tester.
 *
 * @author <Authors name>
 * @version 1.0
 * @since <pre>Mar 30, 2015</pre>
 */
public class FunctionTest {

    Function<Integer, Integer> mult2;
    Function<Integer, String> toCharacter;


    @Before
    public void before() throws Exception {
        mult2 = new Function<Integer, Integer>() {
            @Override
            public Integer apply(Integer arg) {
                return arg * 2;
            }
        };
        toCharacter = new Function<Integer, String>() {
            @Override
            public String apply(Integer arg) {
                return Integer.toString(arg);
            }
        };

    }

    /**
     * Method: apply(T arg)
     */
    @Test
    public void testApply() throws Exception {
        assertEquals(42, (int) mult2.apply(21));

    }

    /**
     * Method: then(final Function<? super R, S> f)
     */
    @Test
    public void testThen() throws Exception {
        assertEquals("42", mult2.then(toCharacter).apply(21));
    }


} 
