package inheritance;

import javax.sound.midi.Soundbank;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<String> menu = new ArrayList<>();
        menu.add("Menu");
        menu.add("Circle");
        menu.add("Rectangle");
        menu.add("Triangle");
        menu.add("Exit");

        Shape shape;

        do{
            clearScreen();
            System.out.println("==== " + menu.getFirst() + " ====");
            for (int i = 1; i < menu.size(); i++)
                System.out.println(i + ". " + menu.get(i));

            System.out.print("Please select an option : ");
            int opt = scanner.nextInt();

            if (opt == 1) {
                System.out.println(" ==== Get Circle Area ====");
                System.out.print("Enter radius : ");
                double radius = scanner.nextDouble();
                shape = new Circle(radius);
                System.out.println("Area : " + shape.getArea());

            } else if (opt == 2) {
                System.out.println(" ==== Get Rectangle Area ====");
                System.out.print("Enter length : ");
                double height = scanner.nextDouble();
                System.out.print("Enter Width : ");
                double width = scanner.nextDouble();
                shape = new Rectangle("Rectangle", height, width);
                System.out.println("Area : " + shape.getArea());

            } else if (opt == 3) {
                System.out.println(" ==== Get Triangle Area ====");
                System.out.print("Enter base : ");
                double base = scanner.nextDouble();
                System.out.print("Enter height : ");
                double height = scanner.nextDouble();
                shape = new Triangle("Triangle", height, base);
                System.out.println("Area : " + shape.getArea());

            } else if (opt == 4) {
                scanner.close();
                System.exit(0);
            } else continue;
            scanner.nextLine();
            scanner.nextLine();
        } while (true);
    }

    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}