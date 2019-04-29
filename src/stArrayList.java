
import java.util.ArrayList;


public class stArrayList {
    public static void main(String[] args) {
        ArrayList<Integer> ids = new ArrayList<Integer>();
        int total = ids.size();
        System.out.println("ids size is " + total);
        System.out.println("ids elements are " + ids);

        ids.add(2);
        ids.add(3);
        total = ids.size();
        System.out.println("ids size is " + total);
        System.out.println("ids elements are " + ids);

        ids.clear();
        total = ids.size();
        System.out.println("ids size is " + total);
        System.out.println("ids elements are " + ids);

        ids.add(2);
        ids.add(3);
        for(int i=0; i<ids.size(); i++){
            System.out.println(ids.get(i));
        }
    }
}
