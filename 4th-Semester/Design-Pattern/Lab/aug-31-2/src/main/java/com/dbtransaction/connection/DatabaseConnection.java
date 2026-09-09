package com.dbtransaction.connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * Singleton database connection manager for SQLite.
 */
public class DatabaseConnection {
    private static Connection connection = null;
    private static final String DB_URL = "jdbc:sqlite:students.db";

    // Private constructor to prevent instantiation
    private DatabaseConnection() {}

    /**
     * Get the active database connection (Singleton).
     */
    public static synchronized Connection getConnection() {
        try {
            if (connection == null || connection.isClosed()) {
                // Connect to SQLite database
                connection = DriverManager.getConnection(DB_URL);
                System.out.println("[DatabaseConnection] Connected to SQLite database.");
                createTableIfNotExists();
            }
        } catch (SQLException e) {
            System.err.println("[DatabaseConnection] Error establishing database connection: " + e.getMessage());
        }
        return connection;
    }

    /**
     * Creates the student table if it does not already exist in the database.
     */
    private static void createTableIfNotExists() {
        String createTableSQL = "CREATE TABLE IF NOT EXISTS students (" +
                "id TEXT PRIMARY KEY, " +
                "name TEXT NOT NULL, " +
                "email TEXT NOT NULL, " +
                "department TEXT NOT NULL" +
                ");";
        try (Statement stmt = connection.createStatement()) {
            stmt.execute(createTableSQL);
            System.out.println("[DatabaseConnection] Verified/Created 'students' table.");
        } catch (SQLException e) {
            System.err.println("[DatabaseConnection] Error creating students table: " + e.getMessage());
        }
    }

    /**
     * Explicitly close the database connection.
     */
    public static synchronized void closeConnection() {
        if (connection != null) {
            try {
                if (!connection.isClosed()) {
                    connection.close();
                    System.out.println("[DatabaseConnection] SQLite database connection closed.");
                }
            } catch (SQLException e) {
                System.err.println("[DatabaseConnection] Error closing database connection: " + e.getMessage());
            } finally {
                connection = null;
            }
        }
    }
}
