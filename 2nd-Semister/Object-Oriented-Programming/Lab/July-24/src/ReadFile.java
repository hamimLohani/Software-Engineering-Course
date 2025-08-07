
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ReadFile {

    private final String fileName;
    private String text;

    public ReadFile(String fileName) {

        this.fileName = fileName;
    }

    public String method1() {
        try {
            FileReader file = new FileReader(fileName);
            StringBuilder stringBuilder = new StringBuilder();
            while (file.ready()) {
                stringBuilder.append((char) file.read());
            }
            text = stringBuilder.toString();
            file.close();
        } catch (IOException e) {
            System.out.println("Error opening file " + fileName + ": " + e.getMessage());
        }
        return text;
    }

    public String method2() {
        try {
            text = String.valueOf(Files.readAllLines(Paths.get(fileName)));
        } catch (IOException e) {
            System.out.println("Error reading file " + fileName + ": " + e.getMessage());
        }
        return text;
    }

    public String method3() {
        try {
            BufferedReader file = new BufferedReader(new InputStreamReader(new  FileInputStream(fileName)));
            text = file.readLine();
            file.close();
        } catch (IOException e) {
            System.out.println("Error opening file " + fileName + ": " + e.getMessage());
        }
        return text;
    }

    public void image(String sourcePath, String destinationPath) {
        try {
            FileInputStream fis = new FileInputStream(sourcePath);
            FileOutputStream fos = new FileOutputStream(destinationPath);

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            fis.close();
            fos.close();

            System.out.println("File copied successfully.");
        } catch (IOException e) {
            System.out.println("Error copying file: " + e.getMessage());
        }
    }
}
