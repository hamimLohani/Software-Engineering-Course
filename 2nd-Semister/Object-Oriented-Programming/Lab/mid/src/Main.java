public class Main {
    public static void main(String[] args) {

        Student[] students = new Student[21];

        students[0] = new Student("hamim", 1, "CSE", "22-23", 20, 3.3, "FH");
        students[1] = new Student("lohani", 2, "CSE", "22-23", 20, 2.3, "SH");
        students[2] = new Student("inzamamul", 3, "CSE", "22-23", 20, 2.5, "FH");
        students[3] = new Student("latif", 4, "CSE", "21-22", 20, 1.3, "SH");
        students[4] = new Student("karim", 5, "CSE", "20-21", 20, 2.6, "FH");
        students[5] = new Student("ratul", 6, "CSE", "20-21", 20, 3.6, "SH");
        students[6] = new Student("asis", 1, "EEE", "22-23", 20, 3.5, "SH");
        students[7] = new Student("naim", 2, "EEE", "20-21", 20, 3.2, "FH");
        students[8] = new Student("darun", 3, "EEE", "20-21", 20, 3.3, "OA");
        students[9] = new Student("mithila", 4, "EEE", "23-24", 20, 3.4, "FH");
        students[10] = new Student("tamim", 5, "EEE", "22-23", 20, 3.7, "SH");
        students[11] = new Student("akaied", 6, "EEE", "20-21", 20, 3.9, "OA");
        students[12] = new Student("moonjin", 1, "ISRT", "21-22", 20, 3.1, "SH");
        students[13] = new Student("dayeen", 2, "ISRT", "23-24", 20, 2.2, "FH");
        students[14] = new Student("nafis", 3, "ISRT", "20-21", 20, 2.4, "OA");
        students[15] = new Student("rayhan", 4, "ISRT", "23-24", 20, 2.5, "FH");
        students[16] = new Student("rashik", 5, "ISRT", "20-21", 20, 2.6, "SH");
        students[17] = new Student("akkhar", 6, "ISRT", "22-23", 20, 2.7, "OA");
        students[18] = new Student("oasi", 1, "IIT", "21-22", 20, 2.8, "FH");
        students[19] = new Student("nafisa", 2, "IIT", "22-23", 20, 2.9, "SH");
        students[20] = new Student("alex", 3, "IIT", "22-23", 20, 4.00, "FH");

        Administration administration = new Administration();

        administration.showAverageAge(students);

        administration.showDetails(2, students);

        administration.showLastInDepartment("CSE", students);
        administration.showLastInDepartment("EEE", students);
        administration.showLastInDepartment("IIT", students);
        administration.showLastInDepartment("ISRT", students);

        administration.showTop3InSession("22-23", students);
        administration.showTop3InSession("23-24", students);
        administration.showTop3InSession("21-22", students);
        administration.showTop3InSession("20-21", students);

        administration.splitStudentInfo(students);
    }
}