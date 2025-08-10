public class Student {

    private String name;
    private int registrationID;
    private String department;
    private String session;
    private int age;
    private double cgpa;
    private String hall;

    public Student(String name, int registrationID, String department, String session, int age, double cgpa, String hall) {
        this.name = name;
        this.registrationID = registrationID;
        this.department = department;
        this.session = session;
        this.age = age;
        this.cgpa = cgpa;
        this.hall = hall;
    }

    public String getName() {
        return name;
    }
    public int getRegistrationID() {
        return registrationID;
    }
    public String getDepartment() {
        return department;
    }
    public String getSession() {
        return session;
    }
    public int getAge() {
        return age;
    }
    public double getCgpa() {
        return cgpa;
    }
    public String getHall() {
        return hall;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setRegistrationID(int registrationID) {
        this.registrationID = registrationID;
    }
    public void setDepartment(String department) {
        this.department = department;
    }
    public void setSession(String session) {
        this.session = session;
    }
    public void setAge(int age) {
        this.age = age;
    }
    public void setCgpa(double cgpa) {
        this.cgpa = cgpa;
    }
    public void setHall(String hall) {
        this.hall = hall;
    }

    @Override
    public String toString() {
        return "Student [name=" + name + ", registrationID=" + registrationID + ", department=" + department
                + "session=" + session + ", age=" + age + ", cgpa=" + cgpa + ", hall=" + hall + "]";
    }
}


