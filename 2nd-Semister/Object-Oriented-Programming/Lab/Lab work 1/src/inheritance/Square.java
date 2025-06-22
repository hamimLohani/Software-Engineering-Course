package inheritance;

public class Square extends Rectangle {
    public Square() {
        super();

    }

    public Square(double side) {
        super(side, side);
    }

    public Square(double side, String color, boolean filled) {
        super(side, side, color, filled);
    }

    public void setSide(double side) {
        setLength(side);
        setWidth(side);
    }

    public double getSide() {
        return getLength();
    }

    public String toString() {
        return super.toString();
    }

}