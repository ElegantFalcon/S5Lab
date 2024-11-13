#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, totalseek, current;

    printf("Enter total numbre of requests : \n");
    scanf("&d", &num);
    int request[num];

    printf("Enter the starting position : \n");
    scanf("%d", &current);

    printf("Enter the disk requests :  \n");
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &request[i]);
    }

    for (int i = 0; i < num; i++)
    {
        totalseek += abs(current - request[i]);
        current = request[i];
    }

    printf("totala head : %d", &totalseek);
}