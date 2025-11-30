#include <stdio.h>
#include <stdlib.h>

int main() {
    int size, n, head, dir;
    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 = right, 0 = left): ");
    scanf("%d", &dir);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (req[j] > req[j + 1]) {
                int t = req[j];
                req[j] = req[j + 1];
                req[j + 1] = t;
            }

    // Find split position
    int pos = 0;
    while (pos < n && req[pos] < head)
        pos++;

    int total = 0;

    if (dir == 1) {  
        // Move RIGHT first
        total += abs(req[n - 1] - head);             // go from head to highest request
        total += abs(req[n - 1] - req[0]);           // reverse and go from highest to lowest
    } 
    else {  
        // Move LEFT first
        total += abs(head - req[0]);                 // go from head to lowest request
        total += abs(req[n - 1] - req[0]);           // reverse and go till highest
    }

    printf("Total Head Movement = %d\n", total);
    return 0;
}
