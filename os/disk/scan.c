#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 100

int calculateTotalSeekTime(int *requests, int numRequests)
{
    int totalSeekTime = 0;
    int currentTrack = 0;
    int direction = 1;

    for (int i = 0; i < numRequests; i++)
    {
        while (currentTrack >= 0 && currentTrack <= 199)
        {
            if (requests[i] == currentTrack)
            {
                totalSeekTime += abs(currentTrack - requests[i]);
                requests[i] = -1;
                break;
            }
            currentTrack += direction;
            totalSeekTime++;
        }

        if (currentTrack == 200)
        {
            direction = -1;
            currentTrack = 199;
        }
        else if (currentTrack == -1)
        {
            direction = 1;
            currentTrack = 0;
        }
    }

    return totalSeekTime;
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests;

    // Input number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    // Input disk requests
    printf("Enter the disk requests (track numbers):\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Calculate and print total seek time
    int totalSeekTime = calculateTotalSeekTime(requests, numRequests);
    printf("Total seek time using SCAN: %d\n", totalSeekTime);

    return 0;
}