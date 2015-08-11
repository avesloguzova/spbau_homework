package ru.spbau.avesloguzova.task03;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

/**
 * FunctionUtils Tester.
 *
 * @author <Authors name>
 * @version 1.0
 * @since <pre>Mar 30, 2015</pre>
 */
public class FunctionUtilsTest {

    Function2<Base, Base, Base> add;
    Function<Base, Base> add42;
    Predicate<Base> isEven;
    int testSize = 100;
    List<Derived> testList = new ArrayList<>(testSize);
    List<Derived> oneElementList = new ArrayList<>(1);
    List<Base> emptyList = new ArrayList<>();

    @Before
    public void before() throws Exception {
        add = new Function2<Base, Base, Base>() {
            @Override
            public Base apply(Base arg1, Base arg2) {
                return new Base(arg1.n + arg2.n);
            }
        };
        add42 = add.bind2(new Base(42));
        isEven = new Predicate<Base>() {
            @Override
            public Boolean apply(Base arg) {
                return arg.n % 2 == 0;
            }
        };
        oneElementList.add(new Derived(42, 1.0));
        for (Integer i = 1; i <= testSize; i++) {
            testList.add(new Derived(i, 1.0));
        }
    }


    /**
     * Method: foldr(final Function2<? super T, ? super T, ? extends T> mult2)
     */
    @Test
    public void testFoldr() throws Exception {
        Function<List<? extends Base>, Base> foldr = FunctionUtils.foldr(add);
        assertEquals(5050, foldr.apply(testList).n);
        assertEquals(42, foldr.apply(oneElementList).n);
        assertNull(foldr.apply(emptyList));
        assertNull(foldr.apply(null));
    }

    /**
     * Method: take(final int count)
     */
    @Test
    public void testTake() throws Exception {
        Function<List<? extends Base>, List<Base>> take = FunctionUtils.<Base>take(2);
        assertEquals(2, take.apply(testList).size());
        assertEquals(0, take.apply(emptyList).size());
    }

    /**
     * Method: map(final Function<? super U, ? extends V> mult2)
     */
    @Test
    public void testMap() throws Exception {
        Function<List<? extends Base>, List<Base>> map = FunctionUtils.map(add42);
        Function<List<? extends Base>, Base> foldr = FunctionUtils.foldr(add);
        assertEquals(9250, foldr.apply(map.apply(testList)).n);
        assertEquals(84, foldr.apply(map.apply(oneElementList)).n);
        assertEquals(0, map.apply(emptyList).size());
    }

    /**
     * Method: filter(final Predicate<? super T> pred)
     */
    @Test
    public void testFilter() throws Exception {
        Function<List<? extends Base>, List<Base>> filter = FunctionUtils.filter(isEven);
        assertEquals(50, filter.apply(testList).size());
        assertEquals(1, filter.apply(oneElementList).size());
        assertEquals(0, filter.apply(emptyList).size());
    }


} 
