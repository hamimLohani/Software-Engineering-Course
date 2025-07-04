package inheritance;

public class Circle extends Shape {
    final static double PI = 3.1416;
    private double radius;

    public Circle(String name, double radius) {
        super(name);
        this.radius = radius;
    }

    public double getArea() {
        return  radius * radius * PI;
    }

}