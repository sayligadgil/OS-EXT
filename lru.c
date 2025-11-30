#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames[10], pages[30], time[10];
    int n, f, i, j, pageFaults = 0, counter = 0, pos;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            if (i < f) {
                frames[i] = pages[i];
                time[i] = ++counter;
            } else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
                time[pos] = ++counter;
            }
            pageFaults++;
        }

        printf("Page %d -> ", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
