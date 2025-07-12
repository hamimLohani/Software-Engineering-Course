public class CommissionEmployee extends Emplyee
{
    public double grossSales;
    public double commissionRate;
    public CommissionEmployee(String firstame, String lastName, String securityNumber, double grossSales,  double commissionRate)
    {
        super(firstame, lastName, securityNumber);
        if (commissionRate < 0 || commissionRate > 1) {
            throw new IllegalArgumentException("Commission Rate must be between 0 and 1");
        }
        this.commissionRate = commissionRate;
        if (grossSales < 0) {
            throw new IllegalArgumentException("Gross sales must be >= 0.0");
        }
        this.grossSales = grossSales;
    }
    @Override
    public double earning()
    {
        return grossSales * commissionRate;
    }
    @Override
    public String toString()
    {
        return super.toString() + " Gross Sale: " + grossSales + " Commission Rate: " + commissionRate;
    }
}
