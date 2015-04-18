package ru.spbau.avesloguzova.task03;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

/**
 * FunctionalComparator Tester.
 *
 * @author <Authors name>
 * @version 1.0
 * @since <pre>Mar 30, 2015</pre>
 */
public class FunctionalComparatorTest {
    FunctionalComparator<Base, Integer> testComparator;
    Derived testObj1;
    Base testObj2;
    Derived testObj3;

    @Before
    public void before() throws Exception {
        Function<Base, Integer> function = new Function<Base, Integer>() {
            @Override
            public Integer apply(Base arg) {
                return arg.n;
            }
        };
        testComparator = new FunctionalComparator<>(function);
        testObj1 = new Derived(42, 1.0);
        testObj2 = new Base(42);
        testObj3 = new Derived(0, 1.0);

    }

    /**
     * Method: compare(T arg1, T arg2)
     */
    @Test
    public void testCompare() throws Exception {
        assertEquals(0, testComparator.<Base>compare(testObj1, testObj2));
        assertNotEquals(0, testComparator.compare(testObj1, testObj3));
    }


} 
