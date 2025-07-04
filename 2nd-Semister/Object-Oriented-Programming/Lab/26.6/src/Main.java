import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        ArrayList<Account> accounts = new ArrayList<Account>();
        Account account;

        while (true) {
            System.out.println("====== Menu ======");
            System.out.println("1. Create Account (Saving Account)");
            System.out.println("2. Create Account (Current Account)");
            System.out.println("3. Create Account (Deposit Premium Account)");
            System.out.println("4. Withdraw");
            System.out.println("5. Deposit");
            System.out.println("6. Transfer Money");
            System.out.println("7. Exit");
            System.out.print("Enter your choice: ");

            Scanner input = new Scanner(System.in);
            int choice = input.nextInt();
            input.nextLine();
            if (choice == 1) {
                System.out.print("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.print("Enter holder Name: ");
                    String name = input.nextLine();
                    System.out.print("Enter amount to be deposited: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    if (amount >= 1000) {
                        account = new SavingAccount(id, name, amount);
                        accounts.add(account);
                    } else {
                        System.out.println("Amount to be deposited is less than 1000");
                    }
                }
            } else if (choice == 2) {
                System.out.print("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.print("Enter holder Name: ");
                    String name = input.nextLine();
                    System.out.print("Enter amount to be deposited: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    account = new SavingAccount(id, name, amount);
                    accounts.add(account);
                }
            } else if (choice == 3) {
                System.out.println("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.print("Enter holder Name: ");
                    String name = input.nextLine();
                    System.out.print("Enter amount to be deposited: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    account = new SavingAccount(id, name, amount);
                    accounts.add(account);
                }
            } else if (choice == 4) {
                System.out.print("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.println("Enter money to be withdrawn: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    acc.withdraw(amount, 0);
                } else {
                    System.out.println("Account not found");
                }
            } else if (choice == 5) {
                System.out.print("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.println("Enter money to be deposited: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    acc.deposit(amount, 0);
                } else {
                    System.out.println("Account not found");
                }
            } else if (choice == 6) {
                System.out.print("Enter Account ID: ");
                String id = input.nextLine();
                Account acc = accountCheck(id, accounts);
                if (acc != null) {
                    System.out.println("Enter Account to deposited: ");
                    String toId = input.nextLine();
                    Account toAcc = accountCheck(toId, accounts);
                    System.out.println("Enter money to be deposited: ");
                    double amount = input.nextDouble();
                    input.nextLine();
                    acc.transferTo(amount, 0, toId, accounts);

                }
            } else if (choice == 7) {
                input.close();
                System.exit(1);
            }
        }
    }
    public static Account accountCheck(String id, ArrayList<Account> accounts) {
        for (Account account : accounts)
            if (account.id.equals(id))
                return account;

        System.out.println("Account doesn't exit.");
        return null;
    }
}