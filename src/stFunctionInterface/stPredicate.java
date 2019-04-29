package stFunctionInterface;

import java.util.function.*;

public class stPredicate {
    public static void main(String[] args) {
        Predicate<Integer> b = x -> x > 6;
        Predicate<Integer> s = x -> x < 3;
        Predicate<Integer> p = x -> x < 9;


        System.out.println(b.test(10));
        System.out.println(b.negate().test(10));
        System.out.println(b.and(s).test(8));
        System.out.println(b.or(p).test(7));

        System.out.println(Predicate.isEqual("hello").test("world"));
        System.out.println(Predicate.isEqual("hello").test("hello"));
    }
}


//calculate string length
class CalculateStringLength implements Function<String, Integer> {
    @Override
    public Integer apply(String s) {
        return s.length();
    }
}

//if return type is boolean, use Predicate instead.
/*
class stFunctionInterface.IsStringEmpty implements Function<String, boolean> {
    @Override
    public boolean apply(String s) {
        return s == null || s.isEmpty();
    }
}
*/
class IsStringEmpty implements Predicate<String> {
    @Override
    public boolean test(String s) {
        return s == null || s.isEmpty();
    }
}

//two parameters
class TwoStringLength implements BiFunction<String, String, Integer> {
    @Override
    public Integer apply(String s, String s2) {
        return s.length() + s2.length();
    }
}


//types of parameter and return are same
class Combine implements UnaryOperator<String> {
    @Override
    public String apply(String s) {
        return s + "suffix";
    }
}

//if parameters are basic data type, to avoid
class IntPre implements IntPredicate {

    @Override
    public boolean test(int value) {
        return false;
    }
}