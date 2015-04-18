package ru.spbau.avesloguzova.task03;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

/**
 * Function2 Tester.
 *
 * @author <Authors name>
 * @version 1.0
 * @since <pre>Mar 30, 2015</pre>
 */
public class Function2Test {

    Base testBase;
    Derived testDerived;
    Function2<Base, Integer, Base> add;
    Function<Base, Integer> unbox;

    @Before
    public void before() throws Exception {
        testBase = new Base(1);
        testDerived = new Derived(2, 1.0);
        add = new Function2<Base, Integer, Base>() {
            @Override
            public Base apply(Base arg1, Integer arg2) {
                return new Base(arg1.n + arg2);
            }
        };
        unbox = new Function<Base, Integer>() {
            @Override
            public Integer apply(Base arg) {
                return arg.n;
            }
        };
    }

    /**
     * Method: apply(T1 arg1, T2 arg2)
     */
    @Test
    public void testApply() throws Exception {
        assertEquals(42, add.apply(testBase, 41).n);
        assertEquals(42, add.apply(testDerived, 40).n);
    }

    /**
     * Method: then(final Function<? super R, S> mult2)
     */
    @Test
    public void testThen() throws Exception {
        assertEquals(42, (int) add.then(unbox).apply(testBase, 41));
        assertEquals(42, (int) add.then(unbox).apply(testDerived, 40));
    }

    /**
     * Method: bind1(final T1 arg1)
     */
    @Test
    public void testBind1() throws Exception {
        assertEquals(42, add.bind1(testBase).apply(41).n);
        assertEquals(42, add.bind1(testDerived).apply(40).n);
    }

    /**
     * Method: bind2(final T2 arg2)
     */
    @Test
    public void testBind2() throws Exception {
        Function<Base, Base> bind2 = add.bind2(40);
        assertEquals(41, bind2.apply(testBase).n);
        assertEquals(42, bind2.apply(testDerived).n);
    }


} 
