#include <stdio.h>

int main() {

    int n = 5;  // Number of processes
    int m = 3;  // Number of resources

    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    int need[5][3];
    int finish[5] = {0};
    int safeSequence[5];

    // Calculate Need = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int count = 0;

    while (count < n) {

        int found = 0;

        for (int i = 0; i < n; i++) {

            if (finish[i] == 0) {

                int canRun = 1;

                // Check Need <= Available
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun) {

                    // Process finishes and releases resources
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;

                    found = 1;
                }
            }
        }

        // No process can finish
        if (found == 0) {
            printf("System is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\n");

    printf("Safe Sequence: ");

    for (int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);

        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}