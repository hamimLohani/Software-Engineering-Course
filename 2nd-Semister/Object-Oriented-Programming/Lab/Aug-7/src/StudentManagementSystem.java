import java.util.*;

public class StudentManagementSystem {
    public static void main(String[] args) {

        List<Student> students = new ArrayList<>();

        Student s1 = new Student(1, "ali", "CS");
        Student s2 = new Student(2, "latif", "EEE");
        Student s3 = new Student(3, "bob", "SE");
        Student s4 = new Student(4, "alex", "Math");
        Student s5 = new Student(5, "john", "CS");
        students.add(s1);
        students.add(s2);
        students.add(s3);
        students.add(s4);
        students.add(s5);

        System.out.println("List of students:");
        for (Student student : students) {
            System.out.println(student);
        }

        Student s6 = new Student(6, "alex", "Math");

        students.add(2, s6);

        students.remove(s2);

        students.remove(3);

        System.out.println("\nUpdated List of students:");
        for (Student student : students) {
            System.out.println(student);
        }

        Set<Student> course = new HashSet<Student>();
        course.add(s1);
        course.add(s2);
        course.add(s3);
        course.add(s4);
        course.add(s5);

        System.out.println("\nSet of Students:");
        for (Student student : course) {
            System.out.println(student);
        }

        if (course.contains(s5)) {
            System.out.println("There exist that student in the course");
        } else {
            course.add(s5);
        }

        if (course.contains(s4)) {
            System.out.println("There exist that student in the course name: " + s4.getStudentName());
        } else {
            System.out.println("Student does not exist in the course");
        }

        for (Student student : course) {
            System.out.println(student);
        }

        Map<Integer, Student> map = new HashMap<>();
        for (Student student : course) {
            map.put(student.getStudentID(), student);
        }

        Student student = map.get(s1.getStudentID());

        if (student != null) {
            System.out.println("Student exist : " + student);
        } else {
            System.out.println("Student does not exist in the course");
        }

    }
}