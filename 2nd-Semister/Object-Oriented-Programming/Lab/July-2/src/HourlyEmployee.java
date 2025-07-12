public class HourlyEmployee extends Emplyee
{
    private double wage;
    public double hour;
    public HourlyEmployee(String firstName,String lastName,String securityNumber, double wage, double hour)
    {
        super(firstName, lastName, securityNumber);
        if (wage <= 0) {
            throw new IllegalArgumentException("Wage Must be greater than 0");
        }
        this.wage = wage;
        if (hour <= 0 || hour > 168) {
            throw new IllegalArgumentException("Hourly Salary Must be between 0 and 168");
        }
        this.hour = hour;
    }
    @Override
    public double earning() {
        if (hour <= 40) {
            return (wage * hour);
        } else {
            return (wage * hour * 1.5);
        }
    }
    @Override
    public String toString()
    {
        return super.toString() + " Hourly Employee: " + this.hour + " Wage: " + this.wage;
    }
}
