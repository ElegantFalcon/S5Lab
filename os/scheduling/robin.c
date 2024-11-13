#include <stdio.h>

struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main()
{
    int n, i, current_time = 0, completed = 0;
    float avg_tat = 0.0, avg_wt = 0.0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];
    printf("Enter Process ID, Arrival Time, and Burst Time:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
    }

    int time_quantum;
    printf("Enter the time quantum : ");
    scanf("%d", &time_quantum);

    int remaining_burst_time[n];

    for (i = 0; i < n; i++)
    {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    while (completed < n)
    {
        int is_process_executed = 0;
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && remaining_burst_time[i] > 0)
            {
                is_process_executed = 1;
                if (remaining_burst_time[i] <= time_quantum)
                {
                    current_time += remaining_burst_time[i];
                    remaining_burst_time[i] = 0;
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                    avg_tat += processes[i].turnaround_time;
                    avg_wt += processes[i].waiting_time;

                    completed++;
                }

                else
                {
                    current_time += time_quantum;
                    remaining_burst_time[i] -= time_quantum;
                }
            }
        }
        if (is_process_executed == 0)
        {
            current_time++;
        }
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\n--- Round Robin Scheduling ---\n");
    printf("PID\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}