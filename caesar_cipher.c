#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char process_char(char ch, int key, int choice);

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    int key, choice;
    char ch;

    printf("--- Caesar Cipher Pro (Encrypt/Decrypt) ---\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Choose an option (1 or 2): ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Invalid choice! Exiting...\n");
        return 1;
    }

    printf("Enter Input Filename: ");
    scanf("%s", inputFilename);

    printf("Enter Output Filename: ");
    scanf("%s", outputFilename);

    printf("Enter Shift Key (0-25): ");
    scanf("%d", &key);
    key = key % 26;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Error: Could not create output file.\n");
        fclose(inputFile);
        return 1;
    }

    printf("\nProcessing file...\n");

    while ((ch = fgetc(inputFile)) != EOF) {
    
        fputc(process_char(ch, key, choice), outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Success! Result saved in: %s\n", outputFilename);
    return 0;
}


char process_char(char ch, int key, int choice) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        
        if (choice == 1) {
            // Encryption: (x + n) % 26
            return (ch - base + key) % 26 + base;
        } else {
            return (ch - base - key + 26) % 26 + base;
        }
    }
    return ch;
}