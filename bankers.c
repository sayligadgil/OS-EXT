#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m], finish[n], seq[n], c = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j], finish[i] = 0;

    while (c < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int ok = 1;
                for (int j = 0; j < m; j++)
                    if (need[p][j] > avail[j]) ok = 0;
                if (ok) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[p][j];
                    seq[c++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found) { printf("UNSAFE"); return 0; }
    }

    printf("SAFE SEQUENCE: ");
    for (int i = 0; i < n; i++) printf("P%d ", seq[i]);
}
