#include <stdio.h>

void findWaitingTime(int processes[], int n, int at[], int bt[], int wt[])
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = at[i - 1] + bt[i - 1] + wt[i - 1] - at[i];
    }
}

void findTAT(int processes[], int n, int at[], int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }
}

void findavgtime(int processes[], int n, int at[], int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, at, bt, wt);
    findTAT(processes, n, at, bt, wt, tat);

    printf("Processes\t Arrival Time \t Burst Time \t Waiting Time \t Turnaround Time \n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d \n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    float avgwt = (float)total_wt / n;
    float avgtat = (float)total_tat / n;

    printf("Average waiting time : %f \n", avgwt);
    printf("Average turn around time : %f \n", avgtat);
}

int main()
{
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {3, 6, 4, 2};
    int arrival_time[] = {0, 1, 4, 6};

    findavgtime(processes,n,arrival_time,burst_time);
    return 0;
}
