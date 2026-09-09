package com.dbtransaction.command;

import com.dbtransaction.model.Student;
import com.dbtransaction.repository.StudentRepository;

/**
 * Concrete Command to update an existing student.
 */
public class UpdateStudentCommand implements Command {
    private final StudentRepository repository;
    private final Student updatedStudent;
    private Student previousStudent; // Cached state to restore on undo

    public UpdateStudentCommand(StudentRepository repository, Student updatedStudent) {
        this.repository = repository;
        this.updatedStudent = updatedStudent;
    }

    @Override
    public boolean execute() {
        // Find existing student state before performing update
        Student current = repository.findStudentById(updatedStudent.getId());
        if (current == null) {
            System.err.println("[UpdateStudentCommand] Error: Student with ID " + updatedStudent.getId() + " not found.");
            return false;
        }

        // Cache a deep copy of the original state for undo
        this.previousStudent = new Student(current);

        // Perform update
        return repository.updateStudent(updatedStudent);
    }

    @Override
    public boolean undo() {
        if (previousStudent == null) {
            System.err.println("[UpdateStudentCommand] Error: No previous state cached to undo.");
            return false;
        }
        return repository.updateStudent(previousStudent);
    }

    @Override
    public String getDescription() {
        return String.format("UPDATE student info (ID: %s)", updatedStudent.getId());
    }
}
