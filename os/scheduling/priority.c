#include <stdio.h>

struct process {
    int id;     // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int pt;     // Priority
};

int main() {
    int n, i, j;
    int sum_tat = 0, sum_wt = 0;
    float avg_tat = 0.0, avg_wt = 0.0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct process processes[n], temp;
    
    // Input process details
    printf("\nEnter Process ID, Priority, Arrival Time, and Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d", &processes[i].id, &processes[i].pt, &processes[i].at, &processes[i].bt);
    }
    
    // Sort by Arrival Time (using Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    int current_time = 0;
    
    // Apply Priority Scheduling (non-preemptive)
    for (i = 0; i < n; i++) {
        int min = i;
        for (j = i + 1; j < n; j++) {
            // Compare based on priority (smaller priority value = higher priority)
            if (processes[j].at <= current_time && processes[j].pt < processes[min].pt) {
                min = j;
            }
        }
        
        // Swap the process with the minimum priority to position i
        temp = processes[i];
        processes[i] = processes[min];
        processes[min] = temp;
        
        // Update current time and calculate Completion Time
        if (current_time < processes[i].at) {
            current_time = processes[i].at;
        }
        current_time += processes[i].bt;
        processes[i].ct = current_time;
        
        // Calculate Turnaround Time and Waiting Time
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        
        // Accumulate TAT and WT for average calculation
        sum_tat += processes[i].tat;
        sum_wt += processes[i].wt;
    }
    
    // Calculate average TAT and WT
    avg_tat = (float)sum_tat / n;
    avg_wt = (float)sum_wt / n;
    
    // Display process details
    printf("\n------ PRIORITY SCHEDULING ------\n");
    printf("\nPID\tPriority\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", 
               processes[i].id, 
               processes[i].pt, 
               processes[i].at, 
               processes[i].bt, 
               processes[i].ct, 
               processes[i].tat, 
               processes[i].wt);
    }
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
