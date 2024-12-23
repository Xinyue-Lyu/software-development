/*Xinyue Lyu
  2/15/2024 
  This file are used to implement functions for build T9 trie and predict word
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t9_lib.h"
#include "t9_priv.h"

// Allocates a new T9 instance with empty internal dictionary.
T9* InitializeEmptyT9() {
    T9* tNode = (T9*)malloc(sizeof(T9));
    tNode->word = NULL;
    for (int i = 0; i < 9; i++) {
        tNode->branch[i] = NULL;
    }
  return tNode;
}

// Allocates a new T9 instance and initializes its dictionary to include all
// words in the given file.
T9* InitializeFromFileT9(const char* filename) {
    if (!filename || strncmp(filename, "", 1)==0) {
        fprintf(stderr, "Error: Invalid filename.\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file '%s'.\n", filename);
        return NULL;
    }

    T9* dict = InitializeEmptyT9();
    char word[50];
    while (fgets(word, 50, file) != NULL) {
        if (strlen(word) > 0 && word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        if (strlen(word) > 0 && strlen(word) <= 50) {
            AddWordToT9(dict, word);
        }
    }
    fclose(file);
    return dict;
}

// Add the given word to the internal T9 dictionary.
void AddWordToT9(T9* dict, const char* word) {
    if (word == NULL || strncmp(word, "", 1)==0 || !dict) {
        exit(0);
    }
    T9 *curr = dict;
    int length = strlen(word);

    // iterate the dict based on the length of word
    for (int i =0; i < length; i++) {
        int currLet = 0;

        // translate letter to number
        if (word[i] == 'a' || word[i] == 'b'|| word[i] == 'c') {
            currLet = 2;
        } else if (word[i] == 'd' || word[i] == 'e' || word[i] == 'f') {
            currLet = 3;
        } else if (word[i] == 'g' || word[i] == 'h' || word[i] == 'i') {
            currLet = 4;
        } else if (word[i] == 'j' || word[i] == 'k' || word[i] == 'l') {
            currLet = 5;
        } else if (word[i] == 'm' || word[i] == 'n' || word[i] == 'o') {
            currLet = 6;
        } else if (word[i] == 'p' || word[i] == 'q' || word[i] == 'r' ||
                   word[i] == 's') {
            currLet = 7;
        } else if (word[i] == 't' || word[i] == 'u' || word[i] == 'v') {
            currLet = 8;
        } else if (word[i] == 'w' || word[i] == 'x' || word[i] == 'y' ||
                   word[i] == 'z') {
            currLet = 9;
        } else {
            currLet = -1;
        }

        // check if current letter is valid
        if (currLet == -1) {
            fprintf(stderr, "invalid letter: %s %c\n", word, word[i]);
            exit(1);
        }
        // check if there are enough node for the word
        if (curr->branch[currLet-2] == NULL) {
            curr->branch[currLet-2] = InitializeEmptyT9();
        }
        curr = curr->branch[currLet-2];
    }

    // add word
    while (curr->word != NULL) {
        if (curr->branch[8] == NULL) {
            curr->branch[8] = InitializeEmptyT9();
        }
        curr = curr->branch[8];
    }
    curr->word = malloc(length + 1);
    strncpy(curr->word, word, length + 1);
}

// Identify a word which is specified by the given sequence of T9 commands.
char* PredictT9(T9* dict, const char* nums) {
    if (!dict || !nums) {
        return NULL;
    }

    T9 *curr = dict;
    int length = strlen(nums);
    // Loop through each character in the T9 commands
    for (int i = 0; i < length; i++) {
        int curNum = 0;
        if (nums[i] == '#') {
            // # should not be the first letter
            if (i == 0) {
                return NULL;
            }
            curNum = 1;
            curr = curr->branch[8];
        } else {
            curNum = nums[i] - '0';
            if (curNum < 2 || curr->branch[curNum-2]==NULL) {
                return NULL;
            } else {
                curr = curr->branch[curNum-2];
            }
        }
    }
    return curr->word;
}

// Destroys the given T9 implementation, and frees all associated memory.
void DestroyT9(T9* dict) {
    if (dict != NULL) {
        for (int i = 0; i < 9; i++) {
            DestroyT9(dict->branch[i]);
        }
        free(dict->word);
        free(dict);
    }
}