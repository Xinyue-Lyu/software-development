/*
    Xinyue (Leah) Lyu
    CSE374 HW3
    1/29/2024
    This file implements a custom version of the Unix `wc` command.
    It processes files to count lines, words, and characters, with options
    for specific counts (-l, -w, -c).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500

// Function prototypes
void processFile(const char *fname, int *tLines, int prLines, int prWords, int prChars);
void printUsage(const char *progName);

int main(int argc, char* argv[]) { 
    if (argc < 2) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Variables to track total counts
    int tLines = 0;
    int prLines = 0, prWords = 0, prChars = 0;
    int optionIndex = 1;

    // Check for options (-l, -w, -c)
    if (argv[1][0] == '-') {
        if (strcmp(argv[1], "-l") == 0) {
            prLines = 1;
        } else if (strcmp(argv[1], "-w") == 0) {
            prWords = 1;
        } else if (strcmp(argv[1], "-c") == 0) {
            prChars = 1;
        } else {
            fprintf(stderr, "Invalid option: %s\n", argv[1]);
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
        optionIndex++; // Skip option argument
    }

    // Process each file
    int filesProcessed = 0;
    for (int i = optionIndex; i < argc; i++) {
        processFile(argv[i], &tLines, prLines, prWords, prChars);
        filesProcessed++;
    }

    // Handle case where no valid files were processed
    if (filesProcessed == 0) {
        fprintf(stderr, "No valid files processed.\n");
        exit(EXIT_FAILURE);
    }

    // Print total lines if no specific option is selected
    if (!prLines && !prWords && !prChars) {
        printf("Total Lines = %d\n", tLines);
    }

    return EXIT_SUCCESS;
}

// Prints usage instructions
void printUsage(const char *progName) {
    fprintf(stderr, "Usage: %s [-l | -w | -c] <file1> [file2 ...]\n", progName);
}

// Processes a single file and prints counts based on options
void processFile(const char *fname, int *tLines, int prLines, int prWords, int prChars) {
    FILE *file = fopen(fname, "r");
    if (!file) {
        fprintf(stderr, "%s will not open. Skipping.\n", fname);
        return;
    }

    int lineCount = 0, wordCount = 0, charCount = 0;
    char buffer[MAXLINE];

    // Read the file line by line
    while (fgets(buffer, MAXLINE, file)) {
        lineCount++;
        charCount += strlen(buffer);

        if (prWords || !prLines && !prChars) { // Count words only if needed
            char *token = strtok(buffer, " \t\n");
            while (token) {
                wordCount++;
                token = strtok(NULL, " \t\n");
            }
        }
    }

    fclose(file);

    // Update total line count
    *tLines += lineCount;

    // Print results based on options
    if (prLines) {
        printf("%d\n", lineCount);
    } else if (prWords) {
        printf("%d\n", wordCount);
    } else if (prChars) {
        printf("%d\n", charCount);
    } else {
        printf("%d %d %d %s\n", lineCount, wordCount, charCount, fname);
    }
}
