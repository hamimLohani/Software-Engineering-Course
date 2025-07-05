public class SalariedEmployee extends Emplyee
{
    private double weeklySalary;

    public  SalariedEmployee(String firstName, String lastName, String securityNumber, double weeklySalary)
    {
        super(firstName, lastName, securityNumber);
        if (weeklySalary <= 0) {
            throw new IllegalArgumentException("Weekly Salary Must be greater than 0");
        }
        this.weeklySalary = weeklySalary;
    }
    public double earning()
    {
        if (weeklySalary <= 0) {
            throw new IllegalArgumentException("Weekly Salary Must be greater than 0");
        }
        return weeklySalary;
    }
    @Override
    public String toString()
    {
        return super.toString();
    }
}
