#include <stdio.h>
//fcfs
typedef struct process {
  int pid; 
  int burst_time; 
  int waiting_time;
  int turnaround_time;
} Process;

void calculate_waiting_time(Process processes[], int n) {
  processes[0].waiting_time = 0; 
  for (int i = 1; i < n; i++) {
    processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time;
  }
}

void calculate_turnaround_time(Process processes[], int n) {
  for (int i = 0; i < n; i++) {
    processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
  }
}

void calculate_average_times(Process processes[], int n) {
  float total_waiting_time = 0, total_turnaround_time = 0;
  for (int i = 0; i < n; i++) {
    total_waiting_time += processes[i].waiting_time;
    total_turnaround_time += processes[i].turnaround_time;
  }
  printf("Average waiting time: %.2f\n", total_waiting_time / n);
  printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  Process processes[10];
  printf("Enter process ID and burst time for each process:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &processes[i].pid, &processes[i].burst_time);
  }

  calculate_waiting_time(processes, n);
  calculate_turnaround_time(processes, n);

  printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
  }

  calculate_average_times(processes, n);

  return 0;
}