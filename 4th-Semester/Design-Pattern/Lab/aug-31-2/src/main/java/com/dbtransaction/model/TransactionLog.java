package com.dbtransaction.model;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * Model representing a logged database transaction/command.
 */
public class TransactionLog {
    private final LocalDateTime timestamp;
    private final String commandType;
    private final String details;
    private String status; // SUCCESS, UNDONE, REDONE, FAILED

    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSS");

    public TransactionLog(String commandType, String details, String status) {
        this.timestamp = LocalDateTime.now();
        this.commandType = commandType;
        this.details = details;
        this.status = status;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public String getCommandType() {
        return commandType;
    }

    public String getDetails() {
        return details;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return String.format("[%s] %-10s | Status: %-8s | Info: %s",
                timestamp.format(FORMATTER),
                commandType,
                status,
                details);
    }
}
