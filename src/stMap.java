import java.util.HashMap;

public class stMap {
    public static void main(String[] args) {
        //HashMap
        //init
        HashMap<String, Integer> map1 = new HashMap<String, Integer>();

        //insert
        map1.put("jack", 20);
        map1.put("rose", 18);
        map1.put("lucy", 17);
        map1.put("java", 25);
        System.out.println(map1);
        map1.put("jack", 30); //will cover previous value
        System.out.println(map1);

        //combine 2 maps
        HashMap<String, Integer> map2 = new HashMap<String, Integer>();
        map2.put("Zhang", 100);
        map2.put("Xu", 20);
        map1.putAll(map2);
        System.out.println(map1);

        //remove
        map1.remove("jack");
        System.out.println(map1);

        //get
        System.out.println(map1.get("Zhang"));

        //judge
        System.out.println(map1.isEmpty());
        System.out.println(map1.containsKey("java"));
        System.out.println(map1.containsValue("20"));
    }
}
