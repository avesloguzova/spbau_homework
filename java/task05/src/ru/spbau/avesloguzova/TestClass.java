package ru.spbau.avesloguzova;

import java.util.Random;

/**
 * Created by av on 5/28/15.
 */
public class TestClass {
    int pr1;
    boolean pr3;
    String pr2;
    private static final Random rand = new Random();
     public static TestClass getRandomInstance(){
         TestClass obj = new TestClass();
         obj.pr1 = rand.nextInt();
         obj.pr2 = String.valueOf(rand.nextDouble());
         obj.pr3 = rand.nextBoolean();
         return obj;
     }

    public int getPr1() {
        return pr1;
    }

    public void setPr1(int pr1) {
        this.pr1 = pr1;
    }

    public boolean getPr3() {
        return pr3;
    }

    public void setPr3(boolean pr3) {
        this.pr3 = pr3;
    }

    public String getPr2() {
        return pr2;
    }

    public void setPr2(String pr2) {
        this.pr2 = pr2;
    }

    @Override
    public String toString() {
        return "TestClass1{" +
                "pr1=" + pr1 +
                ", pr3=" + pr3 +
                ", pr2='" + pr2 + '\'' +
                '}';
    }
}
