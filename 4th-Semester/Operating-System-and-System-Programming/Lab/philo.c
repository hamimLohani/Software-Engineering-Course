#include <stdio.h>
#include <stdlib.h>

#define N 5

int room = N - 1;
int chopstick[N] = {1, 1, 1, 1, 1};

void take_fork(int i)
{
    /* Check room semaphore */
    if (room == 0)
    {
        printf("Philosopher %d is BLOCKED (Room Full).\n", i);
        return;
    }

    /* Enter room */
    room--;

    /* Try to take left chopstick */
    if (chopstick[i] == 0)
    {
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    chopstick[i] = 0;

    /* Try to take right chopstick */
    if (chopstick[(i + 1) % N] == 0)
    {
        /*
         * Philosopher is now blocked while holding
         * the left chopstick.
         */
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", i);
        return;
    }

    chopstick[(i + 1) % N] = 0;

    printf("Philosopher %d is EATING.\n", i);
}

int main(void)
{
    int M;
    int philosopher;

    scanf("%d", &M);

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &philosopher);

        if (philosopher < 0 || philosopher >= N)
        {
            printf("Invalid Philosopher ID.\n");
            continue;
        }

        take_fork(philosopher);
    }

    return 0;
}