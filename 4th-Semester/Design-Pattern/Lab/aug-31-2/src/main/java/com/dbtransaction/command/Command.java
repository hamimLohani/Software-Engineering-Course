package com.dbtransaction.command;

/**
 * Command interface in the Command Pattern.
 */
public interface Command {
    /**
     * Executes the database operation.
     * @return true if successful, false otherwise.
     */
    boolean execute();

    /**
     * Reverts the database operation.
     * @return true if successful, false otherwise.
     */
    boolean undo();

    /**
     * Returns a human-readable description of this command.
     */
    String getDescription();
}
