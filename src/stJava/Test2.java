package stJava;

import scala.reflect.internal.pickling.UnPickler;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;

/*
 * This is taken from https://www.youtube.com/watch?v=1bCgzjatcr4
 * Explain how debugger is used
 */
public class Test2 {
    public static void main(String[] args) {
        ArrayList<String> students = new ArrayList<>();
        ArrayList<Integer> scores = new ArrayList<>();
        System.out.println("Enter Student name");
        Scanner sc = new Scanner(System.in);

        String newStudent;
        do {
            newStudent = sc.nextLine();
            if (!newStudent.equals("")) {
                students.add(newStudent);
            }
        } while (!newStudent.equals(""));

        for (String student: students) {
            System.out.format("Enter %s's score ", student);
            scores.add(sc.nextInt());
        }

        int sum = 0;
        for(Integer score: scores) {
            sum += score; //for error: sum = score
        }

        double average = sum / students.size();
        System.out.println(average);
    }
}
