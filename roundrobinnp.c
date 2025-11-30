#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rem[n], ct[n], wt[n], tat[n];

    for(int i=0;i<n;i++){
        printf("AT & BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rem[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while(completed < n){
        int flag = 0;
        for(int i=0;i<n;i++){
            if(rem[i] > 0 && at[i] <= time){
                flag = 1;

                if(rem[i] > tq){
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }
        if(!flag) time++;
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
    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nThroughput = %.4f processes/unit time", throughput);
}
