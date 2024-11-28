#include <ctype.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float (*FloatDerivativeFunc)(float, float);
typedef void (*SortFunc)(int *, int);

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

void handleCommand(const char *command, int *useVariant,
                   FloatDerivativeFunc func1, FloatDerivativeFunc func2,
                   SortFunc sort1, SortFunc sort2) {
    if (strcmp(command, "0") == 0) {
        *useVariant = 3 - *useVariant;
        printf("Switched to library %d\n", *useVariant);
    } else if (command[0] == '1') {
        float A, deltaX;
        char *args = strdup(command + 2);
        char *token = strtok(args, " ");

        if (!token || !isNumber(token)) {
            printf("Invalid input for argument A\n");
            free(args);
            return;
        }
        A = atof(token);

        token = strtok(NULL, " ");
        if (!token || !isNumber(token)) {
            printf("Invalid input for argument deltaX\n");
            free(args);
            return;
        }
        deltaX = atof(token);

        float result = (*useVariant == 1 ? func1(A, deltaX) : func2(A, deltaX));
        printf("Result: %f\n", result);
        free(args);
    } else if (command[0] == '2') {
        char *args = strdup(command + 2);
        char *token = strtok(args, " ");
        int array[100], size = 0;

        while (token) {
            if (!isNumber(token)) {
                printf("Invalid input: all elements must be integers\n");
                free(args);
                return;
            }
            array[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (*useVariant == 1) {
            sort1(array, size);
        } else {
            sort2(array, size);
        }

        printf("Sorted array: ");
        for (int i = 0; i < size; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");
        free(args);
    } else {
        printf("Unknown command\n");
    }
}

int main() {
    printf("========================================\n");
    printf("  Dynamic Library Functionality Test\n");
    printf("========================================\n\n");

    void *libHandle1 = dlopen("./build/lib1.so", RTLD_LAZY);
    void *libHandle2 = dlopen("./build/lib2.so", RTLD_LAZY);

    if (!libHandle1 || !libHandle2) {
        fprintf(stderr, "\n[ERROR] Failed to load one or more libraries.\n");
        return 1;
    }

    printf("[INFO] Libraries loaded successfully.\n\n");

    FloatDerivativeFunc FloatDerivative1 =
        (FloatDerivativeFunc)dlsym(libHandle1, "FloatDerivative");
    SortFunc Sort1 = (SortFunc)dlsym(libHandle1, "BubbleSort");

    FloatDerivativeFunc FloatDerivative2 =
        (FloatDerivativeFunc)dlsym(libHandle2, "FloatDerivative");
    SortFunc Sort2 = (SortFunc)dlsym(libHandle2, "QuickSort");

    if (!FloatDerivative1 || !Sort1 || !FloatDerivative2 || !Sort2) {
        fprintf(
            stderr,
            "\n[ERROR] Failed to load one or more functions from libraries.\n");
        dlclose(libHandle1);
        dlclose(libHandle2);
        return 1;
    }

    printf("[INFO] Functions loaded successfully.\n\n");
    printf("========================================\n");
    printf("  Instructions:\n");
    printf("  0: Switch between libraries\n");
    printf("  1 <arg1> <arg2>: Calculate FloatDerivative\n");
    printf("  2 <arg1> <arg2> ...: Sort array\n");
    printf("========================================\n\n");

    int useVariant = 1;
    char command[256];

    while (1) {
        printf("\n[INPUT] Enter command (lib%d): ", useVariant);
        if (!fgets(command, sizeof(command), stdin)) {
            printf("\n[ERROR] Failed to read input. Exiting...\n");
            break;
        }

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        printf("\n[PROCESSING] Handling command...\n");
        handleCommand(command, &useVariant, FloatDerivative1, FloatDerivative2,
                      Sort1, Sort2);
    }

    printf("\n[INFO] Cleaning up resources...\n");
    dlclose(libHandle1);
    dlclose(libHandle2);
    printf("[INFO] Exiting program. Goodbye!\n");
    return 0;
}