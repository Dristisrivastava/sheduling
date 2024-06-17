#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

void roundRobin(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    int remaining_time[n];
    for (int i = 0; i < n; i++)
        remaining_time[i] = bt[i];

    int time = 0; 
    while (1) {
        int done = 1; 
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    wt[i] = time - bt[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / (float)n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / (float)n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, burst_time, quantum);

    return 0;
}
