#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortest = -1;
        int shortestIndex = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && (shortest == -1 || processes[i].remaining_time < shortest)) {
                shortest = processes[i].remaining_time;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
        } else {
            processes[shortestIndex].remaining_time--;
            currentTime++;

            if (processes[shortestIndex].remaining_time == 0) {
                completedProcesses++;
                processes[shortestIndex].turnaround_time = currentTime - processes[shortestIndex].waiting_time;
            }

            for (int i = 0; i < n; i++) {
                if (i != shortestIndex && processes[i].remaining_time > 0) {
                    processes[i].waiting_time++;
                }
            }
        }
    }
}

void displayTable(struct Process processes[], int n) {
    printf("\nProcess\tBurst Time\tTurnaround Time\tWaiting Time\n");

    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time,
               processes[i].turnaround_time, processes[i].waiting_time);

        totalTurnaroundTime += processes[i].turnaround_time;
        totalWaitingTime += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    calculateTimes(processes, n);
    displayTable(processes, n);

    return 0;
}
