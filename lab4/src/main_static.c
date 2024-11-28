#include "lib1.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNumber(const char *str) {
    if (*str == '\0')
        return 0;
    while (*str) {
        if (!isdigit(*str) && *str != '-' && *str != '.')
            return 0;
        ++str;
    }
    return 1;
}

void handleCommand(const char *command) {
    if (command[0] == '1') {
        float A, deltaX;
        char *args = strdup(command + 2);
        char *token = strtok(args, " ");

        if (!token || !isNumber(token)) {
            printf("[ERROR] Invalid input for argument A\n");
            free(args);
            return;
        }
        A = atof(token);

        token = strtok(NULL, " ");
        if (!token || !isNumber(token)) {
            printf("[ERROR] Invalid input for argument deltaX\n");
            free(args);
            return;
        }
        deltaX = atof(token);

        float result = FloatDerivative(A, deltaX);
        printf("[RESULT] FloatDerivative(%f, %f) = %f\n", A, deltaX, result);
        free(args);
    } else if (command[0] == '2') {
        char *args = strdup(command + 2);
        char *token = strtok(args, " ");
        int array[100], size = 0;

        while (token) {
            if (!isNumber(token)) {
                printf(
                    "[ERROR] Invalid input: all elements must be integers\n");
                free(args);
                return;
            }
            array[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        BubbleSort(array, size);

        printf("[RESULT] Sorted array: ");
        for (int i = 0; i < size; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
        free(args);
    } else {
        printf("[ERROR] Unknown command\n");
    }
}

int main() {
    printf("========================================\n");
    printf("  Static Library Functionality Test\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("  Instructions:\n");
    printf("  1 <arg1> <arg2>: Calculate FloatDerivative\n");
    printf("  2 <arg1> <arg2> ...: Sort array\n");
    printf("========================================\n\n");

    char command[256];

    while (1) {
        printf("\n[INPUT] Enter command: ");
        if (!fgets(command, sizeof(command), stdin)) {
            printf("\n[ERROR] Failed to read input. Exiting...\n");
            break;
        }

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        printf("\n[PROCESSING] Handling command...\n");
        handleCommand(command);
    }

    printf("\n[INFO] Exiting program. Goodbye!\n");
    return 0;
}
