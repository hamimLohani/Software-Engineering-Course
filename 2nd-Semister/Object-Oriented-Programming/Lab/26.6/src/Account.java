import java.util.ArrayList;

public abstract class Account
{
    protected String id;
    protected String name;
    protected double balance;
    protected int accountType;

    public Account(String id, String name, double balance,  int accountType)
    {
        this.id = id;
        this.name = name;
        this.balance = balance;
        this.accountType = accountType;
    }

    public double deposit(double amount, double interest)
    {
        if (balance >= 0)
        {
            balance = balance + amount + balance * interest / 100;
        }
        else
        {
            System.out.println("Insufficient balance");
        }
        return balance;
    }
    public  double withdraw(double amount, double minimumBalance)
    {
        if (balance >= minimumBalance)
        {
            balance = balance - amount;
        }
        else
        {
            System.out.println("Insufficient balance");
        }
        return balance;
    }
    public double transferTo(double amount, double minimumBalance, String id, ArrayList<Account> accounts)
    {
        Account acc = Main.accountCheck(id, accounts);
        if (acc != null)
        {
            withdraw(amount, minimumBalance);
            acc.deposit(amount, 0);
        }
        else
        {
            System.out.println("Account not found");
        }
        return balance;
    }

}