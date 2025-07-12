import java.util.ArrayList;

public class SavingAccount  extends Account{
    private final double interest = 2.5;
    private final double minimumBalance = 0;
    public SavingAccount(String id, String name, double balance)
    {
        super(id, name, balance, 1);
    }
    public SavingAccount(String id, String name)
    {
        super(id, name, 0, 1);
    }

    @Override
    public double deposit(double amount, double interest)
    {
        return super.deposit(amount, this.interest);
    }

    @Override
    public  double withdraw(double amount,  double minimumBalance)
    {
        return super.withdraw(amount, this.minimumBalance);
    }

    @Override
    public double transferTo(double amount, double minimumBalance, String id, ArrayList<Account> accounts)
    {
        return super.transferTo(amount, this.minimumBalance, id, accounts);
    }

}