#include <stdio.h>

int main() {
    int frames[10], pages[30];
    int n, f, i, j, k, pageFaults = 0, next = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found, replace using FIFO
        if (!found) {
            frames[next] = pages[i];
            next = (next + 1) % f;
            pageFaults++;
        }

        // Print current frame status
        printf("Page %d -> ", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
