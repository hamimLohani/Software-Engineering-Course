package com.dbtransaction.repository;

import com.dbtransaction.connection.DatabaseConnection;
import com.dbtransaction.model.Student;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Receiver in the Command Pattern. Performs actual SQL operations on SQLite database.
 */
public class StudentRepository {

    /**
     * Inserts a student record.
     */
    public boolean insertStudent(Student student) {
        if (student == null) return false;
        String sql = "INSERT INTO students (id, name, email, department) VALUES (?, ?, ?, ?);";
        Connection conn = DatabaseConnection.getConnection();
        if (conn == null) return false;

        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, student.getId());
            pstmt.setString(2, student.getName());
            pstmt.setString(3, student.getEmail());
            pstmt.setString(4, student.getDepartment());
            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            System.err.println("[StudentRepository] Error inserting student: " + e.getMessage());
            return false;
        }
    }

    /**
     * Updates an existing student record.
     */
    public boolean updateStudent(Student student) {
        if (student == null) return false;
        String sql = "UPDATE students SET name = ?, email = ?, department = ? WHERE id = ?;";
        Connection conn = DatabaseConnection.getConnection();
        if (conn == null) return false;

        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, student.getName());
            pstmt.setString(2, student.getEmail());
            pstmt.setString(3, student.getDepartment());
            pstmt.setString(4, student.getId());
            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            System.err.println("[StudentRepository] Error updating student: " + e.getMessage());
            return false;
        }
    }

    /**
     * Deletes a student record by ID.
     */
    public boolean deleteStudent(String id) {
        if (id == null || id.trim().isEmpty()) return false;
        String sql = "DELETE FROM students WHERE id = ?;";
        Connection conn = DatabaseConnection.getConnection();
        if (conn == null) return false;

        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, id);
            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;
        } catch (SQLException e) {
            System.err.println("[StudentRepository] Error deleting student: " + e.getMessage());
            return false;
        }
    }

    /**
     * Finds a student by their unique ID.
     */
    public Student findStudentById(String id) {
        if (id == null || id.trim().isEmpty()) return null;
        String sql = "SELECT id, name, email, department FROM students WHERE id = ?;";
        Connection conn = DatabaseConnection.getConnection();
        if (conn == null) return null;

        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, id);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return new Student(
                            rs.getString("id"),
                            rs.getString("name"),
                            rs.getString("email"),
                            rs.getString("department")
                    );
                }
            }
        } catch (SQLException e) {
            System.err.println("[StudentRepository] Error finding student by id: " + e.getMessage());
        }
        return null;
    }

    /**
     * Retrieves all student records.
     */
    public List<Student> getAllStudents() {
        List<Student> students = new ArrayList<>();
        String sql = "SELECT id, name, email, department FROM students ORDER BY id ASC;";
        Connection conn = DatabaseConnection.getConnection();
        if (conn == null) return students;

        try (PreparedStatement pstmt = conn.prepareStatement(sql);
             ResultSet rs = pstmt.executeQuery()) {
            while (rs.next()) {
                students.add(new Student(
                        rs.getString("id"),
                        rs.getString("name"),
                        rs.getString("email"),
                        rs.getString("department")
                ));
            }
        } catch (SQLException e) {
            System.err.println("[StudentRepository] Error retrieving students: " + e.getMessage());
        }
        return students;
    }
}
