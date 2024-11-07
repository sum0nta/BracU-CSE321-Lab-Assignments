#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char input[100];

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (1) {
        printf("Enter a string (-1 to stop): ");
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0'; 

        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);
    return 0;
}