#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int frames[MAX_FRAMES];
int counter[MAX_FRAMES];

void initialize()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
        counter[i] = 0;
    }
}

void displayFrames()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i] != -1)
        {
            printf("%d", frames[i]);
        }
        else
            printf("-");
    }
    printf("\n");
}

int findLRU()
{
    int max = counter[0];
    int lru_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++)
    {
        if (counter[i] > max)
        {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

void LRU(int pages[], int n)
{
    int page_faults = 0;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                printf("page %d is already there \n", page);
                break;
            }
        }

        if (!found)
        {
            int lru_frame = findLRU();
            printf("page %d loaded in frame %d \n", page, lru_frame);
            frames[lru_frame] = page;
            counter[lru_frame] = 0;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES; j++)
            counter[j]++;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == page)
            {
                counter[j] = 0;
                break;
            }
        }

        displayFrames();
    }
    printf("Total page faults : %d \n", page_faults);
}

int main()
{
    int pages[MAX_PAGES]; // Array to store pages

    // Example sequence of page references
    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    initialize();   // Initialize frames array
    LRU(pages, n); // Apply FIFO algorithm

    return 0;
}