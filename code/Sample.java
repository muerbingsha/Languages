package DataStructure.Set;

import java.util.EnumMap;
import java.util.EnumSet;

public class Sample {
    enum Level {
        LOW, MEDIUM, HIGH;
    }

    enum Work {
        LOW(1),  //calls constructor with value 3
        MEDIUM(2),
        HIGH(3);

        private final int code;

        // 7 - constructor
        Work(int code) {
            this.code = code;
        }

        // 6 - method
        private int getCode() {
            return this.code;
        }
    }

    public static void main(String[] args) {
        Level a = Level.HIGH;
        System.out.println(a);


        //  1 - switch
        switch (a) {
            case LOW: System.out.println("Low case"); break;
            case MEDIUM: System.out.println("Medium case"); break;
            case HIGH: System.out.println("High case"); break;
        }

        // 2 - if
        if (a == Level.HIGH) System.out.println("Yes!");

        // 3 - loop
        for (Level l:  Level.values()) {
            System.out.println(l);
        }

        // 4 - toString
        System.out.println(a.toString());

        // 5 - value
        Level b = Level.valueOf("HIGH");
        try {
            System.out.println(b);
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }

        // 6 - methods
        Work w = Work.LOW;
        System.out.println(w); // print enum string
        System.out.println(w.getCode());


        // 8 - enum set: subset of the enum
        EnumSet<Level> set = EnumSet.of(Level.LOW, Level.HIGH);
        for(Level l: set) {
            System.out.println(l);
        }

        // 9 - enum map: enum as keys
        EnumMap<Level, Integer> map = new EnumMap<Level, Integer>(Level.class);
        map.put(Level.LOW, 10);
        map.put(Level.MEDIUM, 20);
        map.put(Level.HIGH, 30);
        System.out.println(map.get(Level.HIGH));

    }


}

