public class stString {
    public static void main(String[] args) {
        String a = "abcdf";
        String b = "abcdf"; // both refer to same address
        System.out.println(a == b);     //true, this considers both value and address
        System.out.println(a.equals(b)); // true, this only compares value

        a = new String("abcdef");
        b = new String("abcdef");
        System.out.println(a == b); //false
        System.out.println(a.equals(b));
    }
}
