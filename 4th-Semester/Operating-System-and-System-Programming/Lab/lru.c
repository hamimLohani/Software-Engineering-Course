#include <stdio.h>

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = 12;

    int frames[3] = {-1, -1, -1};
    int lastUsed[3] = {0, 0, 0};

    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check whether page is already present
        for (int j = 0; j < 3; j++) {
            if (frames[j] == page) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        // Page fault
        if (!found) {
            pageFaults++;

            int position = -1;

            // Find empty frame
            for (int j = 0; j < 3; j++) {
                if (frames[j] == -1) {
                    position = j;
                    break;
                }
            }

            // If no empty frame, find least recently used
            if (position == -1) {
                position = 0;

                for (int j = 1; j < 3; j++) {
                    if (lastUsed[j] < lastUsed[position]) {
                        position = j;
                    }
                }
            }

            frames[position] = page;
            lastUsed[position] = i;
        }
    }

    printf("LRU Page Faults = %d\n", pageFaults);

    return 0;
}