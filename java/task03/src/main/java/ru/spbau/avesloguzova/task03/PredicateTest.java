package ru.spbau.avesloguzova.task03;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * Predicate Tester.
 *
 * @author <Authors name>
 * @version 1.0
 * @since <pre>Mar 30, 2015</pre>
 */
public class PredicateTest {

    Integer testIntegerPos;
    Integer testIntegerNeg;
    Predicate<Integer> less0;
    Predicate<Integer> isEven;

    @Before
    public void before() throws Exception {
        testIntegerNeg = -1;
        testIntegerPos = 1;

        less0 = new Predicate<Integer>() {
            @Override
            public Boolean apply(Integer arg) {
                return arg < 0;
            }
        };
        isEven = new Predicate<Integer>() {
            @Override
            public Boolean apply(Integer arg) {
                return arg % 2 == 0;
            }
        };
    }

    @Test
    public void testPredicate() throws Exception {
        assertTrue(less0.apply(testIntegerNeg));
        assertFalse(less0.apply(testIntegerPos));

    }

    /**
     * Method: not()
     */
    @Test
    public void testNot() throws Exception {
        final Predicate<Integer> more0 = less0.not();
        assertFalse(more0.apply(testIntegerNeg));
        assertTrue(more0.apply(testIntegerPos));
    }

    /**
     * Method: and(final Predicate<? super T> other)
     */
    @Test
    public void testAnd() throws Exception {
        Predicate<Integer> less0AndEven = less0.and(isEven);
        assertFalse(less0AndEven.apply(testIntegerPos));
        assertFalse(less0AndEven.apply(2));
        assertFalse(less0AndEven.apply(testIntegerNeg));
        assertTrue(less0AndEven.apply(-2));
    }

    /**
     * Method: or(final Predicate<? super T>other)
     */
    @Test
    public void testOr() throws Exception {
        Predicate<Integer> less0OrEven = less0.or(isEven);
        assertFalse(less0OrEven.apply(testIntegerPos));
        assertTrue(less0OrEven.apply(2));
        assertTrue(less0OrEven.apply(testIntegerNeg));
        assertTrue(less0OrEven.apply(-2));
    }

    /**
     * Method: alwaysTrue()
     */
    @Test
    public void testAlwaysTrue() throws Exception {
        assertTrue(Predicate.alwaysTrue().apply(null));
    }

    /**
     * Method: alwaysFalse()
     */
    @Test
    public void testAlwaysFalse() throws Exception {
        assertFalse(Predicate.alwaysFalse().apply(null));
    }

    /**
     * Method: notNull()
     */
    @Test
    public void testNotNull() throws Exception {
        assertTrue(Predicate.<Integer>notNull().apply(testIntegerPos));
        assertFalse(Predicate.notNull().apply(null));
    }

    /**
     * Method: equals(final T arg1)
     */
    @Test
    public void testEquals() throws Exception {
        assertTrue(Predicate.equals(testIntegerPos).apply(testIntegerPos));
        assertFalse(Predicate.equals(testIntegerPos).apply(testIntegerNeg));
    }

    /**
     * Method: less(final T arg1)
     */
    @Test
    public void testLess() throws Exception {
        assertTrue(Predicate.<Integer>less(0).apply(1));
        assertFalse(Predicate.<Integer>less(1).apply(0));
    }


} 
