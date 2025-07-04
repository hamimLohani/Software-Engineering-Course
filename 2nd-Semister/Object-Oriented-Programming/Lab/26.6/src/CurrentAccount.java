import java.util.ArrayList;

public class CurrentAccount extends Account{
    private final double interest = 0;
    private final double minimumBalance = 0;
    public CurrentAccount(String id, String name, double balance) {
        super(id, name, balance, 2);
    }
    public CurrentAccount(String id, String name) {
        super(id, name, 0, 2);
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