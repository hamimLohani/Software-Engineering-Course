public abstract class Emplyee
{
    private String firstame;
    private String lastName;
    private String securityNumber;

    public  Emplyee(String firstame, String lastName, String securityNumber)
    {
        this.firstame = firstame;
        this.lastName = lastName;
        this.securityNumber = securityNumber;
    }
    public abstract double earning();
    public String getFirstName()
    {
        return firstame;
    }
    public String toString()
    {
        return "First Name: " + firstame + "Last Name: " + lastName + "Security Number: " + securityNumber;
    }
}
