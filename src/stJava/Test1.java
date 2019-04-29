package stJava;

/*
 * This sample is to get class name;
 * When ClassNotFoundError occurred;
 */
public class Test1 {
    public static void main(String[] args) {
        Test1 t = new Test1();
        System.out.println(t.getClass().getName());
    }
}
