package com.dbtransaction.command;

import com.dbtransaction.model.Student;
import com.dbtransaction.repository.StudentRepository;

/**
 * Concrete Command to delete a student.
 */
public class DeleteStudentCommand implements Command {
    private final StudentRepository repository;
    private final String studentId;
    private Student deletedStudent; // Cached state to restore on undo

    public DeleteStudentCommand(StudentRepository repository, String studentId) {
        this.repository = repository;
        this.studentId = studentId;
    }

    @Override
    public boolean execute() {
        // Find the student record before deletion to cache its details
        Student current = repository.findStudentById(studentId);
        if (current == null) {
            System.err.println("[DeleteStudentCommand] Error: Student with ID " + studentId + " not found.");
            return false;
        }

        // Cache a deep copy of the student to re-insert on undo
        this.deletedStudent = new Student(current);

        // Perform deletion
        return repository.deleteStudent(studentId);
    }

    @Override
    public boolean undo() {
        if (deletedStudent == null) {
            System.err.println("[DeleteStudentCommand] Error: No student details cached to undo.");
            return false;
        }
        return repository.insertStudent(deletedStudent);
    }

    @Override
    public String getDescription() {
        return String.format("DELETE student %s (ID: %s)",
                deletedStudent != null ? deletedStudent.getName() : "",
                studentId);
    }
}
