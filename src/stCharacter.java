public class stCharacter {
    public static void main(String[] args) {
        char a = 'a';
        char b = 'a';
        System.out.println(a == b);

        Character c = 'a';
        Character d = 'a';
        System.out.println(c == d);
        System.out.println(c.equals(d)); //Character has this more.

    }
}
