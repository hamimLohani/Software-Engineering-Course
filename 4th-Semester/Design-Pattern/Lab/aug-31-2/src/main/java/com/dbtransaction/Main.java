package com.dbtransaction;

import com.dbtransaction.command.Command;
import com.dbtransaction.command.DeleteStudentCommand;
import com.dbtransaction.command.InsertStudentCommand;
import com.dbtransaction.command.UpdateStudentCommand;
import com.dbtransaction.connection.DatabaseConnection;
import com.dbtransaction.manager.TransactionManager;
import com.dbtransaction.model.Student;
import com.dbtransaction.model.TransactionLog;
import com.dbtransaction.repository.StudentRepository;

import java.util.List;
import java.util.Scanner;

/**
 * Main Client class for the Database Transaction Simulator.
 */
public class Main {
    // ANSI Colors for premium console UI
    private static final String RESET = "\u001B[0m";
    private static final String CYAN = "\u001B[36m";
    private static final String GREEN = "\u001B[32m";
    private static final String YELLOW = "\u001B[33m";
    private static final String RED = "\u001B[31m";
    private static final String BLUE = "\u001B[34m";
    private static final String PURPLE = "\u001B[35m";

    public static void main(String[] args) {
        StudentRepository repository = new StudentRepository();
        TransactionManager transactionManager = new TransactionManager();
        Scanner scanner = new Scanner(System.in);

        // Pre-establish database connection at startup
        DatabaseConnection.getConnection();

        System.out.println(CYAN + "===============================================" + RESET);
        System.out.println(CYAN + "   DATABASE TRANSACTION SIMULATOR (JAVA)       " + RESET);
        System.out.println(CYAN + "===============================================" + RESET);

        boolean running = true;
        while (running) {
            printMenu(transactionManager);
            System.out.print(YELLOW + "Choose an option: " + RESET);
            String input = scanner.nextLine().trim();

            switch (input) {
                case "1":
                    handleInsert(scanner, repository, transactionManager);
                    break;
                case "2":
                    handleUpdate(scanner, repository, transactionManager);
                    break;
                case "3":
                    handleDelete(scanner, repository, transactionManager);
                    break;
                case "4":
                    displayAllStudents(repository);
                    break;
                case "5":
                    System.out.println(PURPLE + "\n[Action] Performing Undo (Rollback)..." + RESET);
                    transactionManager.rollbackLast();
                    break;
                case "6":
                    System.out.println(PURPLE + "\n[Action] Performing Redo..." + RESET);
                    transactionManager.redoLast();
                    break;
                case "7":
                    System.out.println(PURPLE + "\n[Action] Performing Rollback All..." + RESET);
                    transactionManager.rollbackAll();
                    break;
                case "8":
                    displayLogs(transactionManager);
                    break;
                case "9":
                    System.out.println(GREEN + "\nExiting application. Goodbye!" + RESET);
                    running = false;
                    break;
                default:
                    System.out.println(RED + "Invalid option. Please choose 1-9." + RESET);
                    break;
            }
        }

        DatabaseConnection.closeConnection();
        scanner.close();
    }

    private static void printMenu(TransactionManager tm) {
        System.out.println("\n" + CYAN + "--- MENU ---" + RESET);
        System.out.println("1. Insert Student");
        System.out.println("2. Update Student");
        System.out.println("3. Delete Student");
        System.out.println("4. Display All Students");
        System.out.println(BLUE + "5. Rollback Last Operation (Undo)  " + YELLOW + "[History: " + tm.getHistoryStackSize() + "]" + RESET);
        System.out.println(BLUE + "6. Redo Last Operation             " + YELLOW + "[Redo: " + tm.getRedoStackSize() + "]" + RESET);
        System.out.println(BLUE + "7. Rollback All Operations" + RESET);
        System.out.println("8. View Transaction Logs");
        System.out.println("9. Exit");
    }

    private static void handleInsert(Scanner scanner, StudentRepository repository, TransactionManager tm) {
        System.out.println(GREEN + "\n--- Insert Student ---" + RESET);
        System.out.print("Enter Student ID: ");
        String id = scanner.nextLine().trim();
        if (id.isEmpty()) {
            System.out.println(RED + "Error: ID cannot be empty." + RESET);
            return;
        }

        // Check if student already exists to prevent SQLite Constraint Exception
        if (repository.findStudentById(id) != null) {
            System.out.println(RED + "Error: A student with ID " + id + " already exists." + RESET);
            return;
        }

        System.out.print("Enter Name: ");
        String name = scanner.nextLine().trim();
        System.out.print("Enter Email: ");
        String email = scanner.nextLine().trim();
        System.out.print("Enter Department: ");
        String department = scanner.nextLine().trim();

        if (name.isEmpty() || email.isEmpty() || department.isEmpty()) {
            System.out.println(RED + "Error: All fields are required." + RESET);
            return;
        }

        Student student = new Student(id, name, email, department);
        Command command = new InsertStudentCommand(repository, student);
        if (tm.executeCommand(command)) {
            System.out.println(GREEN + "Student inserted successfully." + RESET);
        } else {
            System.out.println(RED + "Failed to insert student." + RESET);
        }
    }

    private static void handleUpdate(Scanner scanner, StudentRepository repository, TransactionManager tm) {
        System.out.println(GREEN + "\n--- Update Student ---" + RESET);
        System.out.print("Enter Student ID to update: ");
        String id = scanner.nextLine().trim();
        if (id.isEmpty()) {
            System.out.println(RED + "Error: ID cannot be empty." + RESET);
            return;
        }

        Student existing = repository.findStudentById(id);
        if (existing == null) {
            System.out.println(RED + "Error: Student not found with ID: " + id + RESET);
            return;
        }

        System.out.println("Current Details: " + existing);
        System.out.print("Enter new Name (leave empty to keep current): ");
        String name = scanner.nextLine().trim();
        if (name.isEmpty()) name = existing.getName();

        System.out.print("Enter new Email (leave empty to keep current): ");
        String email = scanner.nextLine().trim();
        if (email.isEmpty()) email = existing.getEmail();

        System.out.print("Enter new Department (leave empty to keep current): ");
        String department = scanner.nextLine().trim();
        if (department.isEmpty()) department = existing.getDepartment();

        Student updated = new Student(id, name, email, department);
        Command command = new UpdateStudentCommand(repository, updated);
        if (tm.executeCommand(command)) {
            System.out.println(GREEN + "Student updated successfully." + RESET);
        } else {
            System.out.println(RED + "Failed to update student." + RESET);
        }
    }

    private static void handleDelete(Scanner scanner, StudentRepository repository, TransactionManager tm) {
        System.out.println(GREEN + "\n--- Delete Student ---" + RESET);
        System.out.print("Enter Student ID to delete: ");
        String id = scanner.nextLine().trim();
        if (id.isEmpty()) {
            System.out.println(RED + "Error: ID cannot be empty." + RESET);
            return;
        }

        Student existing = repository.findStudentById(id);
        if (existing == null) {
            System.out.println(RED + "Error: Student not found with ID: " + id + RESET);
            return;
        }

        Command command = new DeleteStudentCommand(repository, id);
        if (tm.executeCommand(command)) {
            System.out.println(GREEN + "Student deleted successfully." + RESET);
        } else {
            System.out.println(RED + "Failed to delete student." + RESET);
        }
    }

    private static void displayAllStudents(StudentRepository repository) {
        System.out.println(GREEN + "\n--- Student Records ---" + RESET);
        List<Student> students = repository.getAllStudents();
        if (students.isEmpty()) {
            System.out.println("No student records found in the database.");
            return;
        }

        // Print header
        System.out.println("+------------+----------------------+--------------------------------+----------------------+");
        System.out.printf("| %-10s | %-20s | %-30s | %-20s |\n", "ID", "Name", "Email", "Department");
        System.out.println("+------------+----------------------+--------------------------------+----------------------+");
        for (Student s : students) {
            System.out.printf("| %-10s | %-20s | %-30s | %-20s |\n",
                    s.getId(), s.getName(), s.getEmail(), s.getDepartment());
        }
        System.out.println("+------------+----------------------+--------------------------------+----------------------+");
    }

    private static void displayLogs(TransactionManager tm) {
        System.out.println(GREEN + "\n--- Transaction History & Logs ---" + RESET);
        List<TransactionLog> logs = tm.getLogs();
        if (logs.isEmpty()) {
            System.out.println("No transactions have been logged yet.");
            return;
        }

        for (TransactionLog log : logs) {
            String logString = log.toString();
            // Highlight status in console color
            if (logString.contains("SUCCESS")) {
                System.out.println(GREEN + logString + RESET);
            } else if (logString.contains("FAILED")) {
                System.out.println(RED + logString + RESET);
            } else if (logString.contains("UNDONE")) {
                System.out.println(YELLOW + logString + RESET);
            } else if (logString.contains("REDONE")) {
                System.out.println(CYAN + logString + RESET);
            } else {
                System.out.println(logString);
            }
        }
    }
}
