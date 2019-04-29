

public class ArrayTest {
    public static void main(String[] args) {
        // declare: don't allocate memory
        double[] a;

        // initialize 1: allocate memory
        a = new double[10];

        // give value
        a[0] = 0.0;
        a[1] = 0.1;
        a[2] = 0.2;
        a[3] = 0.3;
        a[4] = 0.4;

        // initialize 2
        double[] b = {0.1, 0.4, 0.6, 0.3};


        // display 1
        for (int i=0; i<a.length; i++){
            System.out.println(a[i]);
        }

        // display 2
        for (double ele: b){
            System.out.println(ele);
        }


        double[] c = a; // same memory address, two references.
        c = new double[7];
    }
}

