#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // Initialize the pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        // Parent process: Sender

        // Close unused read end
        close(pipefd[0]);

        const char *message = "Hello from the Parent via Pipe!";

        // Write message to pipe
        if (write(pipefd[1], message, 30) == -1)
        {
            perror("write");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        // Close write end
        close(pipefd[1]);

        // Wait for child to finish
        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        printf("Parent: Child process finished.\n");
    }
    else
    {
        // Child process: Receiver

        // Close unused write end
        close(pipefd[1]);

        // Read data from pipe
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (bytes_read == -1)
        {
            perror("read");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received string
        buffer[bytes_read] = '\0';

        printf("Child received: %s\n", buffer);

        // Close read end
        close(pipefd[0]);

        // Replace child process with the whoami command
        if (execlp("whoami", "whoami", (char *)NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}