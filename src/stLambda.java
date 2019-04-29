import java.util.Arrays;
import java.util.List;

public class stLambda {

    //To iterate
    public static void main(String[] args) {
        String[] names = {"Rafael Nadal", "Novak Djokovic",
                "Stanislas Wawrinka",
                "David Ferrer","Roger Federer",
                "Andy Murray","Tomas Berdych",
                "Juan Martin Del Potro"};

        List<String> players = Arrays.asList(names);

        //tradional
        for(String p: players) {
            System.out.print(p + ",");
        }

        System.out.println();

        //使用 lambda 表达式以及函数操作(functional operation)
        players.forEach((player) -> System.out.print(player + "-"));

        //Java 8 中使用双冒号操作符(double colon operator)
        players.forEach(System.out::println);
    }
}
