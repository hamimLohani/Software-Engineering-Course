package com.dbtransaction.model;

/**
 * Model representing a Student record.
 */
public class Student {
    private String id;
    private String name;
    private String email;
    private String department;

    // Default constructor
    public Student() {}

    // Parameterized constructor
    public Student(String id, String name, String email, String department) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.department = department;
    }

    // Copy constructor to preserve state for commands
    public Student(Student other) {
        if (other != null) {
            this.id = other.id;
            this.name = other.name;
            this.email = other.email;
            this.department = other.department;
        }
    }

    // Getters and Setters
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    @Override
    public String toString() {
        return String.format("Student[ID: %s, Name: %s, Email: %s, Dept: %s]", id, name, email, department);
    }
}
