package com.dbtransaction;

import com.dbtransaction.command.Command;
import com.dbtransaction.command.DeleteStudentCommand;
import com.dbtransaction.command.InsertStudentCommand;
import com.dbtransaction.command.UpdateStudentCommand;
import com.dbtransaction.connection.DatabaseConnection;
import com.dbtransaction.manager.TransactionManager;
import com.dbtransaction.model.Student;
import com.dbtransaction.repository.StudentRepository;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.sql.Connection;
import java.sql.Statement;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class DatabaseTransactionTest {

    private final StudentRepository repository = new StudentRepository();
    private final TransactionManager tm = new TransactionManager();

    @BeforeEach
    void setUp() throws Exception {
        // Ensure table exists and is completely cleared before each test
        Connection conn = DatabaseConnection.getConnection();
        assertNotNull(conn, "Database connection should not be null.");
        try (Statement stmt = conn.createStatement()) {
            stmt.execute("DELETE FROM students;");
        }
    }

    @AfterAll
    static void tearDownAll() {
        DatabaseConnection.closeConnection();
    }

    @Test
    void testInsertStudentCommandAndUndoRedo() {
        Student s = new Student("S001", "Alice", "alice@example.com", "CSE");
        Command insertCmd = new InsertStudentCommand(repository, s);

        // 1. Execute Insert
        assertTrue(tm.executeCommand(insertCmd), "Command execution should succeed.");
        Student fetched = repository.findStudentById("S001");
        assertNotNull(fetched, "Student should exist after insertion.");
        assertEquals("Alice", fetched.getName());
        assertEquals(1, tm.getHistoryStackSize());
        assertEquals(0, tm.getRedoStackSize());

        // 2. Undo Insert (Rollback)
        assertTrue(tm.rollbackLast(), "Rollback should succeed.");
        assertNull(repository.findStudentById("S001"), "Student should be deleted after undo.");
        assertEquals(0, tm.getHistoryStackSize());
        assertEquals(1, tm.getRedoStackSize());

        // 3. Redo Insert
        assertTrue(tm.redoLast(), "Redo should succeed.");
        fetched = repository.findStudentById("S001");
        assertNotNull(fetched, "Student should exist again after redo.");
        assertEquals("Alice", fetched.getName());
        assertEquals(1, tm.getHistoryStackSize());
        assertEquals(0, tm.getRedoStackSize());
    }

    @Test
    void testUpdateStudentCommandAndUndo() {
        Student s = new Student("S002", "Bob", "bob@example.com", "EEE");
        repository.insertStudent(s);

        // Update name and department
        Student updated = new Student("S002", "Bobby", "bob@example.com", "CSE");
        Command updateCmd = new UpdateStudentCommand(repository, updated);

        // 1. Execute Update
        assertTrue(tm.executeCommand(updateCmd), "Update command should succeed.");
        Student fetched = repository.findStudentById("S002");
        assertEquals("Bobby", fetched.getName());
        assertEquals("CSE", fetched.getDepartment());

        // 2. Undo Update
        assertTrue(tm.rollbackLast(), "Undo update should succeed.");
        fetched = repository.findStudentById("S002");
        assertEquals("Bob", fetched.getName(), "Name should revert to Bob.");
        assertEquals("EEE", fetched.getDepartment(), "Department should revert to EEE.");

        // 3. Redo Update
        assertTrue(tm.redoLast(), "Redo update should succeed.");
        fetched = repository.findStudentById("S002");
        assertEquals("Bobby", fetched.getName());
        assertEquals("CSE", fetched.getDepartment());
    }

    @Test
    void testDeleteStudentCommandAndUndo() {
        Student s = new Student("S003", "Charlie", "charlie@example.com", "ME");
        repository.insertStudent(s);

        Command deleteCmd = new DeleteStudentCommand(repository, "S003");

        // 1. Execute Delete
        assertTrue(tm.executeCommand(deleteCmd), "Delete command should succeed.");
        assertNull(repository.findStudentById("S003"), "Student should be deleted.");

        // 2. Undo Delete
        assertTrue(tm.rollbackLast(), "Undo delete should succeed.");
        Student fetched = repository.findStudentById("S003");
        assertNotNull(fetched, "Student should be restored.");
        assertEquals("Charlie", fetched.getName());
        assertEquals("ME", fetched.getDepartment());
    }

    @Test
    void testRollbackAll() {
        Student s1 = new Student("S101", "John", "john@example.com", "BBA");
        Student s2 = new Student("S102", "Doe", "doe@example.com", "MBA");

        // Chain of commands: Insert S1 -> Insert S2 -> Update S1
        assertTrue(tm.executeCommand(new InsertStudentCommand(repository, s1)));
        assertTrue(tm.executeCommand(new InsertStudentCommand(repository, s2)));

        Student updatedS1 = new Student("S101", "Johnny", "johnny@example.com", "BBA");
        assertTrue(tm.executeCommand(new UpdateStudentCommand(repository, updatedS1)));

        // Verify state prior to rollback all
        assertEquals(3, tm.getHistoryStackSize());
        assertEquals("Johnny", repository.findStudentById("S101").getName());
        assertNotNull(repository.findStudentById("S102"));

        // Rollback all
        tm.rollbackAll();

        // Verify database is cleared completely and history is empty
        assertEquals(0, tm.getHistoryStackSize());
        assertNull(repository.findStudentById("S101"));
        assertNull(repository.findStudentById("S102"));
    }

    @Test
    void testInvalidCommands() {
        // Try to update non-existing student
        Student s = new Student("S999", "Ghost", "ghost@example.com", "None");
        Command updateCmd = new UpdateStudentCommand(repository, s);
        assertFalse(tm.executeCommand(updateCmd), "Executing update on non-existing student should fail.");
        assertEquals(0, tm.getHistoryStackSize(), "Failed command should not be added to history.");

        // Try rollback on empty history
        assertFalse(tm.rollbackLast());

        // Try redo on empty redo stack
        assertFalse(tm.redoLast());
    }
}
