#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], ct[n];

    for(int i=0;i<n;i++){
        printf("AT & BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    ct[0] = at[0] + bt[0];
    for(int i=1; i<n; i++){
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    float totalWT = 0, totalTAT = 0;
    for(int i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        totalWT  += wt[i];
        totalTAT += tat[i];
    }

    int totalTime = ct[n-1];
    float throughput = (float)n / totalTime;

    printf("\nP\tAT\tBT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printf("\nP%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], wt[i], tat[i]);

    printf("\n\nAverage WT = %.2f", totalWT/n);
    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nThroughput = %.4f processes/unit time", throughput);
}
