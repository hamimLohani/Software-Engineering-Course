#include <stdio.h>
#define N 5

int main() {
    int M;
    int room = 4;
    int chopstick[N] = {1, 1, 1, 1, 1};

    scanf("%d", &M);
    for (int event = 0; event < M; event++) {
        int philosopher;
        scanf("%d", &philosopher);

        if (philosopher < 0 || philosopher >= M) {
            printf("Philosopher %d is INVALID (Out of Range).\n", philosopher);
            continue;
        }

        int left  = philosopher;
        int right = (philosopher + 1) % N;

        if (room == 0) {
            printf("Philosopher %d is BLOCKED (Room Full).\n", philosopher);
            continue;
        }
        room--;

        if (chopstick[left] == 0) {
            printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", philosopher);
            room++; 
            continue;
        }
        chopstick[left]--;

        if (chopstick[right] == 0) {
            printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", philosopher);
            chopstick[left]++; 
            room++;       
            continue;
        }
        chopstick[right]--;

        printf("Philosopher %d is EATING.\n", philosopher);
    }

    return 0;
}
