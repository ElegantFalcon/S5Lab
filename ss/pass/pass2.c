#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Open necessary files
    FILE *inpF = fopen("intermediate.txt", "r");   // Intermediate file from Pass 1
    FILE *optab = fopen("optab.txt", "r");         // Opcode table
    FILE *symtab = fopen("symtab.txt", "r");       // Symbol table
    FILE *objF = fopen("object.txt", "w");         // Object code output file
    FILE *outF = fopen("finaloutput.txt", "w");    // Human-readable output file
    
    // Declare variables to store parts of each line
    char label[10], opcode[10], operand[10], loc[10];
    char code[10], symbol[10];
    int prevaddr, finaddr, length, start;

    // Determine the program length by reading until the END statement
    fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        prevaddr = atoi(loc);                      // Store the last location address
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }
    finaddr = atoi(loc);                           // Final address of the program

    // Reset and reopen intermediate file to start actual assembly
    fclose(inpF);
    inpF = fopen("output.txt", "r");
    fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);

    // If the program has a START directive, initialize start address
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(outF, "%s %10s%10s%10s\t%s\n", loc, label, opcode, operand, "**");
        fprintf(objF, "H^%s^%06d^%06X\n", label, atoi(operand), finaddr - atoi(operand));
        fprintf(objF, "T^%06d^%X", atoi(operand), prevaddr - atoi(operand));
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }

    // Main loop: Process each line from intermediate file until END
    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            // Handle BYTE directive, typically a constant value
            fprintf(outF, "%s%10s%10s%10s\t", loc, label, opcode, operand);
            fprintf(objF, "^");
            length = strlen(operand) - 3;         // Exclude the quotes in C'Z' or X'F1'
            for (int i = 2; i < length + 2; i++) {  // Write as hexadecimal
                fprintf(outF, "%X", operand[i]);
                fprintf(objF, "%X", operand[i]);
            }
            fprintf(outF, "\n");

        } else if (strcmp(opcode, "WORD") == 0) {
            // Handle WORD directive, stores a 3-byte integer
            fprintf(outF, "%s%10s%10s%10s\t%06d\n", loc, label, opcode, operand, atoi(operand));
            fprintf(objF, "^%06d", atoi(operand));

        } else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0) {
            // Handle RESB and RESW, which reserve memory but do not generate object code
            fprintf(outF, "%s%10s%10s%10s\n", loc, label, opcode, operand);

        } else {
            // For regular opcodes, look up machine code and operand address
            fprintf(outF, "%s%10s%10s%10s\t", loc, label, opcode, operand);

            // Look up the machine code for the opcode in optab.txt
            rewind(optab);
            fscanf(optab, "%s%s", symbol, code);
            while (strcmp(symbol, opcode) != 0) {
                fscanf(optab, "%s%s", symbol, code);
            }
            fprintf(outF, "%s", code);
            fprintf(objF, "^%s", code);

            // Look up the operand address in symtab.txt
            rewind(symtab);
            fscanf(symtab, "%s%s", symbol, code);
            while (strcmp(symbol, operand) != 0) {
                fscanf(symtab, "%s%s", symbol, code);
            }
            fprintf(outF, "%s\n", code);
            fprintf(objF, "%s", code);
        }

        // Read the next line in the intermediate file
        fscanf(inpF, "%s%s%s%s", loc, label, opcode, operand);
    }

    // Write the last line and the end record to object file
    fprintf(outF, "%s%10s%10s%10s\n", loc, label, opcode, operand);
    fprintf(objF, "\nE^%06d\n", start);

    // Close all open files
    fclose(inpF);
    fclose(optab);
    fclose(symtab);
    fclose(objF);
    fclose(outF);

    return 0;
}
