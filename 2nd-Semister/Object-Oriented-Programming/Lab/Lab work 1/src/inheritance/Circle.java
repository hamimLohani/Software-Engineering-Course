package inheritance;

import java.lang.reflect.Field;

public class Circle extends Shape {
    final static double PI = 3.1416;
    private double radius;

    public Circle() {
        radius = 1.0;
    }

    public Circle(double radius) {
        this.radius = radius;
    }

    public Circle(double radius, String color, boolean filled){
        super(color, filled);
        this.radius = radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }

    public double getArea() {
        return PI * radius * radius;
    }

    public double getParimeter() {
        return 2 * PI * radius;
    }

    public String toString() {
        return super.toString();
    }

}