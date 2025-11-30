#include <stdio.h>

int findOPT(int pages[], int frames[], int n, int f, int index) {
    int pos = -1, farthest = index, i, j, k;
    for (i = 0; i < f; i++) {
        int found = 0;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                found = 1;
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (!found)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames[10], pages[30];
    int n, f, i, j, pageFaults = 0, pos;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < f) {
                frames[i] = pages[i];
            } else {
                pos = findOPT(pages, frames, n, f, i + 1);
                frames[pos] = pages[i];
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
