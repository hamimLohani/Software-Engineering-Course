public class TestMyTriangle {

    public static void main(String[] args) {

        MyPoint p1 = new MyPoint(3, 4);
        MyPoint p2 = new MyPoint(5, 4);
        MyPoint p3 = new MyPoint();

        p3.setXY(new int[]{2, 3});

        System.out.println("Point-1 X = " + p1.getX());
        System.out.println("Point-1 Y = " + p1.getY());

        System.out.println("Point-2 X = " + p2.getXY()[0] + " Y = " + p2.getXY()[1]);

        System.out.println("Distance(P1-P2): " + p1.distance(p2));
        System.out.println("Distance(P1-(0, 0)): " + p1.distance());
        System.out.println("Distance(P1-(5, 7)): " + p1.distance(5, 7));

        MyTriangle t1 = new MyTriangle(p1, p2, p3);

        System.out.println("Triangle 1 = " + t1);

        System.out.println("Total Distance of edges = " + t1.getPerimeter());
        System.out.println("Type = " + t1.getType());

        MyTriangle t2 = new MyTriangle(0,0,1,1,1,0);
        System.out.println("Triangle 2 = " + t2);
        System.out.println("Total Distance of edges = " + t2.getPerimeter());
        System.out.println("Type = " + t2.getType());

        MyTriangle t3 = new MyTriangle(1,1,2,2,3,3);
        System.out.println("Triangle 3 = " + t3);
        System.out.println("Total Distance of edges = " + t3.getPerimeter());
        System.out.println("Type = " + t3.getType());

    }
}