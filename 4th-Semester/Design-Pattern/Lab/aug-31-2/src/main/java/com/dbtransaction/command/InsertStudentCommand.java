package com.dbtransaction.command;

import com.dbtransaction.model.Student;
import com.dbtransaction.repository.StudentRepository;

/**
 * Concrete Command to insert a student.
 */
public class InsertStudentCommand implements Command {
    private final StudentRepository repository;
    private final Student student;

    public InsertStudentCommand(StudentRepository repository, Student student) {
        this.repository = repository;
        this.student = student;
    }

    @Override
    public boolean execute() {
        return repository.insertStudent(student);
    }

    @Override
    public boolean undo() {
        if (student == null) return false;
        return repository.deleteStudent(student.getId());
    }

    @Override
    public String getDescription() {
        return String.format("INSERT student %s (ID: %s)", student.getName(), student.getId());
    }
}
