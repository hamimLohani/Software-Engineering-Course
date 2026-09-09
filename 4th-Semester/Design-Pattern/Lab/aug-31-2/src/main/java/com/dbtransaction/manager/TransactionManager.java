package com.dbtransaction.manager;

import com.dbtransaction.command.Command;
import com.dbtransaction.model.TransactionLog;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Invoker in the Command Pattern.
 * Manages execution, rollback (undo), redo, history, and logging.
 */
public class TransactionManager {
    private final Deque<Command> historyStack = new ArrayDeque<>();
    private final Deque<Command> redoStack = new ArrayDeque<>();
    private final List<TransactionLog> logs = new ArrayList<>();

    /**
     * Executes a command, adds to history, clears redo stack, and logs the operation.
     */
    public boolean executeCommand(Command command) {
        if (command == null) return false;

        String description = command.getDescription();
        String commandType = getCommandType(command);

        try {
            boolean success = command.execute();
            if (success) {
                historyStack.push(command);
                redoStack.clear(); // Clear redo stack on new action
                logs.add(new TransactionLog(commandType, description, "SUCCESS"));
                return true;
            } else {
                logs.add(new TransactionLog(commandType, description, "FAILED"));
                return false;
            }
        } catch (Exception e) {
            logs.add(new TransactionLog(commandType, description + " (Exception: " + e.getMessage() + ")", "FAILED"));
            System.err.println("[TransactionManager] Error executing command: " + e.getMessage());
            return false;
        }
    }

    /**
     * Rolls back the last successfully executed operation.
     */
    public boolean rollbackLast() {
        if (historyStack.isEmpty()) {
            System.out.println("[TransactionManager] No transactions to rollback.");
            return false;
        }

        Command command = historyStack.pop();
        String description = command.getDescription();
        String commandType = getCommandType(command);

        try {
            boolean success = command.undo();
            if (success) {
                redoStack.push(command);
                logs.add(new TransactionLog(commandType, "ROLLBACK: " + description, "UNDONE"));
                System.out.println("[TransactionManager] Rolled back: " + description);
                return true;
            } else {
                // If undo failed, restore to history stack
                historyStack.push(command);
                logs.add(new TransactionLog(commandType, "ROLLBACK FAILED: " + description, "FAILED"));
                System.err.println("[TransactionManager] Failed to rollback: " + description);
                return false;
            }
        } catch (Exception e) {
            historyStack.push(command);
            logs.add(new TransactionLog(commandType, "ROLLBACK EXCEPTION: " + description + " (" + e.getMessage() + ")", "FAILED"));
            System.err.println("[TransactionManager] Error rolling back command: " + e.getMessage());
            return false;
        }
    }

    /**
     * Re-executes the last undone operation.
     */
    public boolean redoLast() {
        if (redoStack.isEmpty()) {
            System.out.println("[TransactionManager] No transactions to redo.");
            return false;
        }

        Command command = redoStack.pop();
        String description = command.getDescription();
        String commandType = getCommandType(command);

        try {
            boolean success = command.execute();
            if (success) {
                historyStack.push(command);
                logs.add(new TransactionLog(commandType, "REDO: " + description, "REDONE"));
                System.out.println("[TransactionManager] Redone: " + description);
                return true;
            } else {
                redoStack.push(command);
                logs.add(new TransactionLog(commandType, "REDO FAILED: " + description, "FAILED"));
                System.err.println("[TransactionManager] Failed to redo: " + description);
                return false;
            }
        } catch (Exception e) {
            redoStack.push(command);
            logs.add(new TransactionLog(commandType, "REDO EXCEPTION: " + description + " (" + e.getMessage() + ")", "FAILED"));
            System.err.println("[TransactionManager] Error redoing command: " + e.getMessage());
            return false;
        }
    }

    /**
     * Rolls back all operations in the history in reverse order.
     */
    public void rollbackAll() {
        if (historyStack.isEmpty()) {
            System.out.println("[TransactionManager] No transactions to rollback.");
            return;
        }

        System.out.println("[TransactionManager] Initiating rollback of all operations...");
        int count = 0;
        while (!historyStack.isEmpty()) {
            if (rollbackLast()) {
                count++;
            } else {
                System.err.println("[TransactionManager] Rollback interrupted due to failure.");
                break;
            }
        }
        System.out.println("[TransactionManager] Successfully rolled back " + count + " operations.");
    }

    /**
     * Returns the full list of transaction logs.
     */
    public List<TransactionLog> getLogs() {
        return new ArrayList<>(logs);
    }

    public int getHistoryStackSize() {
        return historyStack.size();
    }

    public int getRedoStackSize() {
        return redoStack.size();
    }

    /**
     * Helper to extract short command type label.
     */
    private String getCommandType(Command command) {
        String className = command.getClass().getSimpleName();
        return className.replace("Command", "").toUpperCase();
    }
}
