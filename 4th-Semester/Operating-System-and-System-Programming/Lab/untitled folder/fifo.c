#include <stdio.h>

int main() {
    int reference[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(reference) / sizeof(reference[0]);
    int f = 3;
    int frames[10];
    int pageFaults = 0;
    int pointer = 0;

    printf("Number of frames: %d\n", f);
    printf("Reference string: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", reference[i]);
    }
    printf("\n");

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (int i = 0; i < n; i++) {
        int page = reference[i];
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[pointer] = page;
            pointer = (pointer + 1) % f;
            pageFaults++;

            printf("%d\t", page);

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tPage Fault\n");
        } else {
            printf("%d\t", page);

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frames[j]);
            }

            printf("\tHit\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits   = %d\n", n - pageFaults);

    return 0;
}