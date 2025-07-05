import java.util.ArrayList;

public class DepositPremiumAccount extends Account {
    private int installment = 0;
    private final double interest = 7;
    private final double minimumBalance = 0;
    public  DepositPremiumAccount(String id, String name, double balance)
    {
        super(id, name, balance, 3);
        installment++;
    }
    public DepositPremiumAccount(String id, String name)
    {
        super(id, name, 0, 3);
        installment++;
    }

    @Override
    public double deposit(double amount,  double interest)
    {
        installment++;
        return super.deposit(amount, this.interest);
    }

    @Override
    public  double withdraw(double amount,  double minimumBalance)
    {
        double balance = 0;
        if (installment >= 5)
        {
            balance = super.withdraw(amount, this.minimumBalance);
        }
        else
        {
            System.out.println("Remain installment: " + (5 - installment));
        }
        return balance;
    }

    @Override
    public double transferTo(double amount, double minimumBalance, String id,  ArrayList<Account> accounts)
    {
        System.out.println("You can not transfer money");
        return super.getBalance();
    }
}