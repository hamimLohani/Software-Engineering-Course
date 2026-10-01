#include <stdio.h>

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = 12;
    int frames[3] = {-1, -1, -1};
    int pointer = 0;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < 3; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found) {
            frames[pointer] = page;
            pointer = (pointer + 1) % 3;
            pageFaults++;
        }
    }

    printf("FIFO Page Faults = %d\n", pageFaults);

    return 0;
}