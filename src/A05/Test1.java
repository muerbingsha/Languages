package A05;

import java.util.Arrays;
import java.util.List;

public class Test1 {

    public static void main(String[] args) {


    }


    // Arrays.asList()
    public static void method1() {
        System.out.println("transfer data to list");
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5);
        list.forEach(System.out::println);

        System.out.println("transfer array to list");
        Integer[] a = {1, 2, 3};
        List<Integer> list2 = Arrays.asList(a);
        list2.forEach(System.out::println);

        System.out.println("transfer primitive type array to list");
        int[] b = {1, 2, 3};
        List<int[]> list3 = Arrays.asList(b);
        System.out.println(list3.size());
        System.out.println(Arrays.toString(list3.get(0)));
    }


}
