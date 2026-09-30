#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0)
    {
        // fork() failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        // Parent process
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID registered: %d\n", pid);

        // Wait for the child process to finish
        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        printf("Child process has finished.\n");
    }
    else
    {
        // Child process
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        // Replace child process with the 'clear' command
        if (execlp("clear", "clear", (char *)NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}