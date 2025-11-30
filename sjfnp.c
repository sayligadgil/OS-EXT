#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], wt[n], tat[n], done[n];

    for(int i=0;i<n;i++){
        printf("AT & BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        done[i] = 0;
    }

    int time = 0, completed = 0;

    while(completed < n){
        int idx = -1, minBT = 9999;

        for(int i=0;i<n;i++){
            if(!done[i] && at[i] <= time && bt[i] < minBT){
                minBT = bt[i];
                idx = i;
            }
        }

        if(idx == -1){
            time++;
            continue;
        }

        time += bt[idx];
        ct[idx] = time;
        done[idx] = 1;
        completed++;
    }

    float totalWT = 0, totalTAT = 0;

    for(int i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    int totalTime = time;
    float throughput = (float)n / totalTime;

    printf("\nP\tAT\tBT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printf("\nP%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], wt[i], tat[i]);

    printf("\n\nAverage WT = %.2f", totalWT/n);
    printf(" \nAverage TAT = %.2f", totalTAT/n);
    printf("\nThroughput = %.4f processes/unit time", throughput);
}
