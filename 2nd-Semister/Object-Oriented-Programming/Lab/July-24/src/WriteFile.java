import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class WriteFile {

    private final String fileName;
    private String text;

    public WriteFile(String fileName,  String text) {
        this.fileName = fileName;
        this.text = text;
    }

    public void method1() {
        try {
            FileWriter fileWriter = new FileWriter(fileName);
            fileWriter.write(text);
            fileWriter.close();
        } catch (IOException e) {
            System.out.println("Error opening file " + fileName + ": " + e.getMessage());
        }
    }

    public void method2() {
        try {
            Files.writeString(Path.of(fileName), text);
        } catch (IOException e) {
            System.out.println("Error writing to file " + fileName + ": " + e.getMessage());
        }
    }

    public void method3() {
        try {
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(fileName));
            bufferedWriter.write(text);
            bufferedWriter.close();
        } catch (IOException e) {
            System.out.println("Error opening file " + fileName + ": " + e.getMessage());
        }
    }
}
