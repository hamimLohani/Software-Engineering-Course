//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        Emplyee[] employee = new Emplyee[4];

        employee[0] = new SalariedEmployee("jon", "ho", "101010", 10000);
        employee[1] = new CommissionEmployee("rafiq", "de", "101011", 10000, .1);
        employee[2] = new HourlyEmployee("halk", "se", "101012", 16, 20);
        employee[3] = new HourlyEmployee("mac", "se", "101013", 16, 50);


        for(Emplyee e: employee)
        {
            System.out.println(e.toString() + " Earning: " + e.earning());
        }
    }
}