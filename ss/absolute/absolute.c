#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input, *output;
char record[100];

int read_header_record()
{
    char program_name[10], verify_name[10];
    fscanf(input, "%s", record);

    // verify program name
    printf("Enter the program name : ");
    scanf("%s", verify_name);

    int i = 2;
    while (record[i] != '^')
    {
        program_name[i - 2] = record[i];
        i++;
    }
    program_name[i - 2] = '\0';

    if (strcmp(program_name, verify_name) != 0)
    {
        printf("Invalid program name \n");
        exit(0);
    }

    else
    {
        printf("Program name : %s \n", program_name);
        fscanf(input, "%s", record);
    }
}

int main()
{
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    read_header_record();

    while (record[0] != 'E')
    {
        int i = 2, starting_address;
        char addrress[10];

        while (record[i] != '^')
        {
            addrress[i - 2] = record[i];
            i++;
        }

        printf("Starting address : %s\n", addrress);
        starting_address = atoi(addrress);

        i += 4;
        while (i < strlen(record) - 1)
        {
            if (record[i] != '^')
            {
                printf("%06d\t%c%c\n", starting_address, record[i], record[i + 1]);
                fprintf(output, "%06d\t%c%c\n", starting_address, record[i], record[i + 1]);
                starting_address++;
                i += 2;
            }
            else
            {
                i++;
            }
        }
        fprintf(output, "\n");
        printf("\n");
        fscanf(input, "%s", record);
    }
    fclose(input);
    fclose(output);
}
