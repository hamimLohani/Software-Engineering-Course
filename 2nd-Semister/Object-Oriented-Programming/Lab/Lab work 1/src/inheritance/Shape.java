package inheritance;

public abstract class Shape {
    private String color;
    private boolean filled;


    public Shape() {
        color = "red";
        filled = true;
    }

    public Shape(String color, boolean filled) {
        this.color = color;
        this.filled = filled;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    public String getColor() {
        return color;
    }

    public boolean getFilled() {
        return filled;
    }

    public String toString() {
        String string = "A Shape with color of " + getColor() + " and ";
        if (getFilled()) string = string + "filled";
        else string = string + "Not filled";

        return string;
    }

}