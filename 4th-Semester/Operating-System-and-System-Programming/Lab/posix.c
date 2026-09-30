#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHM_NAME "/my_shared_memory"

typedef struct {
    int flag;
    char message[1024];
} SharedMemory;

int main(void)
{
    int shm_fd;
    SharedMemory *shared_mem;
    pid_t pid;

    /* Create shared memory object */
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    /* Allocate sufficient memory for SharedMemory */
    if (ftruncate(shm_fd, sizeof(SharedMemory)) == -1)
    {
        perror("ftruncate");
        close(shm_fd);
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    /* Map shared memory into address space */
    shared_mem = mmap(
        NULL,
        sizeof(SharedMemory),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        shm_fd,
        0
    );

    if (shared_mem == MAP_FAILED)
    {
        perror("mmap");
        close(shm_fd);
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    /* Initialize synchronization flag */
    shared_mem->flag = 0;
    shared_mem->message[0] = '\0';

    /* Create child process */
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        munmap(shared_mem, sizeof(SharedMemory));
        close(shm_fd);
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        /* ---------------- Parent Process ---------------- */

        char input[1024];

        printf("Parent: Enter a message: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            munmap(shared_mem, sizeof(SharedMemory));
            close(shm_fd);
            shm_unlink(SHM_NAME);
            exit(EXIT_FAILURE);
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = '\0';

        /* Write message into shared memory */
        strncpy(shared_mem->message, input, sizeof(shared_mem->message) - 1);
        shared_mem->message[sizeof(shared_mem->message) - 1] = '\0';

        /* Notify child that message is ready */
        shared_mem->flag = 1;

        printf("Parent: Message written to shared memory.\n");

        /* Wait for child to process the message */
        if (wait(NULL) == -1)
        {
            perror("wait");
            munmap(shared_mem, sizeof(SharedMemory));
            close(shm_fd);
            shm_unlink(SHM_NAME);
            exit(EXIT_FAILURE);
        }

        /* Child has written its reply */
        if (shared_mem->flag == 2)
        {
            printf("Parent: Child reply: %s\n", shared_mem->message);
        }

        /* Release resources */
        if (munmap(shared_mem, sizeof(SharedMemory)) == -1)
        {
            perror("munmap");
        }

        if (close(shm_fd) == -1)
        {
            perror("close");
        }

        if (shm_unlink(SHM_NAME) == -1)
        {
            perror("shm_unlink");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* ---------------- Child Process ---------------- */

        /* Wait until parent writes the message */
        while (shared_mem->flag != 1)
        {
            usleep(1000);
        }

        /* Read and display parent's message */
        printf("Child: Received message: %s\n", shared_mem->message);

        /* Write reply into shared memory */
        strcpy(shared_mem->message, "Hello from the Child!");

        /* Notify parent that reply is ready */
        shared_mem->flag = 2;

        /* Release child resources */
        if (munmap(shared_mem, sizeof(SharedMemory)) == -1)
        {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        if (close(shm_fd) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    return 0;
}