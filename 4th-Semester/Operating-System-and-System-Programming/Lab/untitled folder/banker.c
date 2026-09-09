#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void checkBankers(int n, int m, int allocation[MAX_P][MAX_R], int max[MAX_P][MAX_R], int available[MAX_R], const char *testName) {
    int need[MAX_P][MAX_R];
    int work[MAX_R];
    int finish[MAX_P];
    int safeSequence[MAX_P];

    printf("=========================================\n");
    printf(" %s\n", testName);
    printf("=========================================\n");
    printf("Number of processes: %d\n", n);
    printf("Number of resources: %d\n", m);

    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("%d ", available[j]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < m; j++)
        work[j] = available[j];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i])
                continue;

            bool canFinish = true;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    canFinish = false;
                    break;
                }
            }
            if (canFinish) {
                for (int j = 0; j < m; j++) {
                    work[j] += allocation[i][j];
                }
                safeSequence[count] = i;
                finish[i] = 1;
                count++;
                found = true;
            }
        }
        if (!found)
            break;
    }
    if (count == n) {
        printf("\nResult: System is in SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i != n - 1)
                printf(" -> ");
        }
        printf("\n\n");
    } else {
        printf("\nResult: System is in UNSAFE state (Deadlock potential).\n");
        if (count > 0) {
            printf("Partial Execution Sequence (before getting stuck): ");
            for (int i = 0; i < count; i++) {
                printf("P%d", safeSequence[i]);
                if (i != count - 1)
                    printf(" -> ");
            }
            printf("\nUnfinished / Deadlocked Processes: ");
            for (int i = 0; i < n; i++) {
                if (!finish[i])
                    printf("P%d ", i);
            }
            printf("\n");
        } else {
            printf("No process could finish with available resources.\n");
        }
        printf("\n");
    }
}

int main() {
    // Example 1: SAFE State Example
    int n1 = 5, m1 = 3;
    int alloc1[MAX_P][MAX_R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int max1[MAX_P][MAX_R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int avail1[MAX_R] = {3, 3, 2};

    checkBankers(n1, m1, alloc1, max1, avail1, "EXAMPLE 1: SAFE STATE");

    // Example 2: UNSAFE State Example (Partial execution P1 -> P3 -> P4, then stuck)
    int n2 = 5, m2 = 3;
    int alloc2[MAX_P][MAX_R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int max2[MAX_P][MAX_R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    // Available resources set to {1, 2, 2}: allows P1, P3, P4 to execute, but then system gets stuck
    int avail2[MAX_R] = {1, 2, 2};

    checkBankers(n2, m2, alloc2, max2, avail2, "EXAMPLE 2: UNSAFE STATE WITH PARTIAL SEQUENCE");

    return 0;
}