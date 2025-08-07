public class Student {

    private int studentID;
    private String StudentName;
    private String major;

    public Student(int studentID, String studentName, String major) {
        this.studentID = studentID;
        this.StudentName = studentName;
        this.major = major;
    }

    public int getStudentID() {
        return studentID;
    }

    public String getStudentName() {
        return StudentName;
    }

    public String getMajor() {
        return major;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return studentID == student.studentID;
    }

    @Override
    public int hashCode() {
        return studentID;
    }

    @Override
    public String toString() {
        return studentID + "\t" + StudentName + "\t" + major;
    }
}