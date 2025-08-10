import java.util.ArrayList;
import java.util.List;

public class Administration {

    public void showAverageAge(Student students[]) {
        int total = 0;
        for (int i = 0; i < students.length; i++) {
            total += students[i].getAge();
        }
        System.out.println("Average age: " + total/students.length);

    }
    public void showDetails(int registrationID, Student students[]) {
        for (Student student : students) {
            if (student.getRegistrationID() == registrationID) {
                System.out.println(student);
            }
        }
    }
    public void showLastInDepartment(String department, Student students[]) {
        double lastInDepartment = 4.0;
        Student student1 = null;
        System.out.println("Department: " + department);
        for (Student student : students) {
            if (student.getCgpa() < lastInDepartment && student.getDepartment().equals(department)) {
                lastInDepartment = student.getCgpa();
                student1 = student;
            }
        }
        System.out.println("Last In Department: " + student1.getName());
    }
    public void showTop3InSession(String session, Student students[]) {
        double topInSession = 0;
        Student student1 = null;
        Student student2 = null;
        Student student3 = null;
        System.out.println("Session: " + session);
        for (Student student : students) {
            if (student.getCgpa() > topInSession && student.getSession().equals(session)) {
                topInSession = student.getCgpa();
                student1 = student;
            }
        }
        topInSession = 0;
        for (Student student : students) {
            if (student.getCgpa() > topInSession && student1 != student && student.getSession().equals(session)) {
                topInSession = student.getCgpa();
                student2 = student;
            }
        }
        topInSession = 0;
        for (Student student : students) {
            if (student.getCgpa() > topInSession && student2 != student && student1 != student && student.getSession().equals(session)) {
                topInSession = student.getCgpa();
                student3 = student;
            }
        }

        System.out.println("Top 1st In Session: " + student1.getName());
        System.out.println("Top 2nd In Session: " + student2.getName());
        System.out.println("Top 3rd In Session: " + student3.getName());
    }
    public void splitStudentInfo(Student students[]) {
        List<String> halls = new ArrayList<String>();
        for (Student student : students) {
            if (!halls.contains(student.getHall())) {
                halls.add(student.getHall());
            }
        }

        for (String hall : halls) {
            System.out.println("Hall: " + hall);
            for (Student student : students) {
                if (student.getHall().equals(hall)) {
                    System.out.println(student);
                }
            }
        }
    }
}
