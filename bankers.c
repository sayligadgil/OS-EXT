#include <stdio.h>

int main() {
    int n, m;
    
    printf("Number of Processes and Resources:\n");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int finish[n], seq[n], count = 0;

    printf("\nALLOCATION MATRIX (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nMAX MATRIX (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nAVAILABLE RESOURCES (%d):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate need matrix
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    while (count < n) {
        int found = 0;

        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int ok = 1;

                for (int j = 0; j < m; j++) {
                    if (need[p][j] > avail[j]) {
                        ok = 0;
                        break;
                    }
                }

                if (ok) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[p][j];

                    seq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in SAFE STATE.\n");
            return 0;
        }
    }

    printf("\nSAFE SEQUENCE: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", seq[i]);

    printf("\n");
    return 0;
}
