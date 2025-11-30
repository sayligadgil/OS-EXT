#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, total = 0, min, pos;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n], done[n];
    for (i = 0; i < n; i++) done[i] = 0;

    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (i = 0; i < n; i++) {
        min = 9999; pos = -1;
        for (j = 0; j < n; j++) {
            if (!done[j] && abs(req[j] - head) < min) {
                min = abs(req[j] - head);
                pos = j;
            }
        }
        total += abs(req[pos] - head);
        head = req[pos];
        done[pos] = 1;
    }

    printf("Total Head Movement = %d\n", total);
    return 0;
}
