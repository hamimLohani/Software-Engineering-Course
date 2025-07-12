import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ArrayList<Account> accounts = new ArrayList<>();
        accounts.add(new Account("0001", "Nafis", 1000));
        accounts.add(new Account("0002", "Rabin", 1000));
        accounts.add(new Account("0003", "Latif", 5000));
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("==== Menu ====");
            System.out.println("\t1. Create new account");
            System.out.println("\t2. Debit");
            System.out.println("\t3. Credit");
            System.out.println("\t4. Transfer");
            System.out.println("\t5. Show Account");
            System.out.println("\t6. Exit");
            System.out.print("Your choice : ");

            int opt = scanner.nextInt();
            scanner.nextLine();
            if (opt == 1){
                System.out.print("Enter name : ");
                String name = scanner.nextLine();
                System.out.print("Enter id : ");
                String id = scanner.nextLine();
                System.out.print("Enter balance(optional) : ");
                int balance = scanner.nextInt();
                scanner.nextLine();
                accounts.add(new Account(id, name, balance));
            } else if (opt == 2){
                System.out.print("Enter id : ");
                String id = scanner.nextLine();
                Account acc = accountCheck(accounts, id);
                if (acc != null) {
                    System.out.print("Enter balance : ");
                    int balance = scanner.nextInt();
                    scanner.nextLine();

                    System.out.println("New balance " + acc.debit(balance));
                }
            } else if (opt == 3) {
                System.out.print("Enter id : ");
                String id = scanner.nextLine();
                Account acc = accountCheck(accounts, id);
                if (acc != null) {
                    System.out.print("Enter balance : ");
                    int balance = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("New balance " + acc.debit(balance));
                }
            } else if (opt == 4) {
                System.out.print("Enter id (from): ");
                String fromId = scanner.nextLine();
                Account fromAcc = accountCheck(accounts, fromId);
                System.out.print("Enter id (to): ");
                String toId = scanner.nextLine();
                Account toAcc = accountCheck(accounts, toId);
                if (fromAcc != null && toAcc != null) {
                    System.out.print("Enter balance : ");
                    int balance = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("New balance " + fromAcc.transferTo(toAcc, balance));
                }
            } else if (opt == 5) {
                System.out.print("Enter id : ");
                String id = scanner.nextLine();
                Account acc = accountCheck(accounts, id);
                System.out.println(acc.toString());

            } else if (opt == 6) {
                scanner.close();
                System.exit(1);
            } else  continue;

        }
    }
    public static Account accountCheck(ArrayList<Account> accounts, String id) {
        for (Account account : accounts)
            if (account.id.equals(id))
                return account;

        System.out.println("Account doesn't exit.");
        return null;
    }
}
