#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

int main()
{
    int f[max], n, val, ch, b, start;

    for (int i = 0; i < max; i++)
    {
        f[i] = 0;
    }

    printf("Enter the number of blocks which are already allocated : \n");
    scanf("%d", &n);

    printf("Enter the blocks which are already allocated \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        f[val] = 1;
    }

a:

    printf("1.add file 2.exit \n");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:{
        printf("Enter the no of blocks to be allocated and starting address of block : \n");
        scanf("%d%d", &b, &start);

        if (f[start] == 1)
        {
            printf("Already allocated ... \n");
            goto a;
        }

        for (int i = start; i < (start + b); i++)
        {
            if (f[i] == 0)
            {
                f[i] = 1;
                printf("Block number %d ------> %d \n", i, f[i]);
            }
            else
            {
                b++;
            }
        }

        goto a;
        break;
    }
    case 2:{
        exit(0);
    }

    }
}