#include <stdio.h>
#include <stdbool.h>

#define MAX_ITEMS 10
#define MAX_TRANSACTIONS 20
#define MAX_ITEMSETS 100

int transactions[MAX_TRANSACTIONS][MAX_ITEMS];
int transactionCount[MAX_TRANSACTIONS];

int numTransactions;
int numItems;
int minSupport;

bool containsItemset(int transaction[], int tCount, int itemset[], int itemsetSize) {
    for (int i = 0; i < itemsetSize; i++) {
        bool found = false;
        for (int j = 0; j < tCount; j++) {
            if (transaction[j] == itemset[i]) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int getSupport(int itemset[], int itemsetSize) {
    int count = 0;
    for (int i = 0; i < numTransactions; i++) {
        if (containsItemset(
                transactions[i],
                transactionCount[i],
                itemset,
                itemsetSize)) {
            count++;
        }
    }
    return count;
}

void printItemset(int itemset[], int size, int support) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%d", itemset[i]);
        if (i != size - 1)
            printf(", ");
    }
    printf("}  Support Count = %d\n", support);
}

bool canJoin(int a[], int b[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool exists(int itemsets[][MAX_ITEMS], int count, int itemset[], int size) {
    for (int i = 0; i < count; i++) {
        bool same = true;
        for (int j = 0; j < size; j++) {
            if (itemsets[i][j] != itemset[j]) {
                same = false;
                break;
            }
        }
        if (same)
            return true;
    }
    return false;
}

int generateCandidates(int previous[][MAX_ITEMS], int previousCount, int previousSize, int candidates[][MAX_ITEMS]) {
    int candidateCount = 0;
    for (int i = 0; i < previousCount; i++) {
        for (int j = i + 1; j < previousCount; j++) {
            if (!canJoin(previous[i], previous[j], previousSize)) continue;

            int candidate[MAX_ITEMS];
            for (int k = 0; k < previousSize; k++)
                candidate[k] = previous[i][k];

            candidate[previousSize] = previous[j][previousSize - 1];

            if (!exists(candidates, candidateCount, candidate, previousSize + 1)) {
                for (int k = 0; k < previousSize + 1; k++)
                    candidates[candidateCount][k] = candidate[k];
                candidateCount++;
            }
        }
    }
    return candidateCount;
}

int main() {
    numTransactions = 9;
    numItems = 5;
    minSupport = 2;

    int defaultTransactions[9][5] = {
        {1, 2, 5},
        {2, 4},
        {2, 3},
        {1, 2, 4},
        {1, 3},
        {2, 3},
        {1, 3},
        {1, 2, 3, 5},
        {1, 2, 3}
    };
    int defaultCounts[9] = {3, 2, 2, 3, 2, 2, 2, 4, 3};

    for (int i = 0; i < numTransactions; i++) {
        transactionCount[i] = defaultCounts[i];
        for (int j = 0; j < transactionCount[i]; j++) {
            transactions[i][j] = defaultTransactions[i][j];
        }
    }

    printf("\n=== Database Transactions ===\n");
    for (int i = 0; i < numTransactions; i++) {
        printf("T%d: {", i + 1);
        for (int j = 0; j < transactionCount[i]; j++) {
            printf("%d", transactions[i][j]);
            if (j != transactionCount[i] - 1) printf(", ");
        }
        printf("}\n");
    }
    printf("Minimum Support Count: %d\n", minSupport);

    int previous[MAX_ITEMSETS][MAX_ITEMS];
    int candidates[MAX_ITEMSETS][MAX_ITEMS];
    int current[MAX_ITEMSETS][MAX_ITEMS];

    int previousCount = 0;
    int previousSize = 1;

    printf("\n========== L1 ==========\n");

    for (int item = 1; item <= numItems; item++) {
        int itemset[1] = {item};
        int support = getSupport(itemset, 1);
        if (support >= minSupport) {
            previous[previousCount][0] = item;
            printf("{%d}  Support Count = %d\n", item, support);
            previousCount++;
        }
    }
    int k = 2;
    while (previousCount > 0) {
        int candidateCount = generateCandidates(previous, previousCount, previousSize, candidates);
        if (candidateCount == 0) break;

        printf("\n========== C%d ==========\n", k);
        for (int i = 0; i < candidateCount; i++) {
            printf("{");
            for (int j = 0; j < k; j++) {
                printf("%d", candidates[i][j]);
                if (j != k - 1)
                    printf(", ");
            }
            printf("}\n");
        }
        int currentCount = 0;
        printf("\n========== L%d ==========\n", k);
        for (int i = 0; i < candidateCount; i++) {
            int support = getSupport(candidates[i], k);
            if (support >= minSupport) {
                for (int j = 0; j < k; j++) {
                    current[currentCount][j] =
                        candidates[i][j];
                }
                printf("{");
                for (int j = 0; j < k; j++) {
                    printf("%d", candidates[i][j]);
                    if (j != k - 1)
                        printf(", ");
                }
                printf("}  Support Count = %d\n", support);
                currentCount++;
            }
        }

        if (currentCount == 0) break;

        for (int i = 0; i < currentCount; i++) {
            for (int j = 0; j < k; j++) {
                previous[i][j] = current[i][j];
            }
        }
        previousCount = currentCount;
        previousSize = k;
        k++;
    }

    printf("\n========== Apriori Finished ==========\n");
    return 0;
}