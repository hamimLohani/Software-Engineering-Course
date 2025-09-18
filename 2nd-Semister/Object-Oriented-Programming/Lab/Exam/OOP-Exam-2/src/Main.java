import java.io.*;
import java.util.HashMap;
import java.util.Map;


public class Main {

    public static Map<String, Account> accounts = new HashMap<>();
    public static Account account;


    public static void main(String[] args) {

        accounts.put("hamim", new Account("hamim", "123"));
        accounts.put("rakib", new Account("rakib", "123"));
        accounts.put("l", new Account("l", "1234"));
        accounts.put("a", new Account("a", "1234"));

        String fileName = "demo.txt";
        String text = "";
            try {
                BufferedReader file = new BufferedReader(new InputStreamReader(new  FileInputStream(fileName)));
                text = file.readLine();
                file.close();
            } catch (IOException e) {
                System.out.println("Error opening file " + fileName + ": " + e.getMessage());
            }
            System.out.printf(text);
        new LoginForm();
    }
}