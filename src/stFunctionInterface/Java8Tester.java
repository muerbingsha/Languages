package stFunctionInterface;

import javax.sound.midi.Soundbank;
import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;


/*
 * Predicate Callback
 */
public class Java8Tester {
    public static void main(String[] args) {
        List<Integer> l = Arrays.asList(1,2, 3, 4);
        //method 1
        System.out.println("Output all elements");
        eval(l, n->true);

        //method 2
        System.out.println("Output all even numbers");
        eval2(l, n->n%2==0);

        //method 3
        System.out.println("Output all numbers bigger than 3");
        l.stream().filter(n->n>3).forEach(System.out::println);
    }

    public static void eval(List<Integer> list, Predicate<Integer> predicate) {
        for(Integer e: list) {
            if (predicate.test(e)) {
                System.out.println(e + " ");
            }
        }
    }

    public static void eval2(List<Integer> list, Predicate<Integer> predicate) {
        list.stream().filter(predicate).forEach(System.out::println);
    }


}

