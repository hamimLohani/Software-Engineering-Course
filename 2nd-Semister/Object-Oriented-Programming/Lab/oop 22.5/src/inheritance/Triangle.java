package inheritance;

public class Triangle extends Shape {

    private double base;
    private double height;

    public Triangle(String name, double base, double height) {
        super(name);
        this.base = base;
        this.height = height;
    }

    public double getArea() {
        return height * base * .5;
    }
}