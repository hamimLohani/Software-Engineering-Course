public class BasePlusCommissionEmployee extends CommissionEmployee
{
    private double baseSalary;

    public BasePlusCommissionEmployee(String firstame, String lastName, String securityNumber, double grossSales,  double commissionRate, double baseSalary)
    {
        super(firstame, lastName, securityNumber, grossSales, commissionRate);
        if (baseSalary <= 0) {
            throw new IllegalArgumentException("Base Salary Must be greater than 0");
        }
        this.baseSalary = baseSalary;
    }
    @Override
    public double earning()
    {
        return 1.1 * baseSalary + super.earning();
    }
    @Override
    public String toString()
    {
        return super.toString() + " Base Salary: " + baseSalary;
    }
}
