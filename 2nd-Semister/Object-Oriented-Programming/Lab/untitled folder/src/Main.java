
public class Main {

    private static final String pathName = "1.txt";
    private static final String text = "hello world";

    public static void main(String[] args) {

        WriteFile writeFile = new WriteFile("1.txt", text);
        WriteFile writeFile1 = new WriteFile("2.txt", text);
        WriteFile writeFile2 = new WriteFile("3.txt", text);
        ReadFile readFile = new ReadFile(pathName);

        writeFile.method1();
        writeFile2.method3();
        writeFile1.method2();
        readFile.method1();
        readFile.method2();
        readFile.method3();




        readFile.image("input.jpg", "copy.jpg");
    }
}