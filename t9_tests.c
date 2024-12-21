/*
 * Author: Xinyue Lyu
 * This file contains test cases for validating the T9 implementation.
 */

#include "t9_lib.h"
#include <string.h>
#include <stdio.h>
#include "safe_assert.h"

// Utility function to compare expected and actual strings.
void AssertReturnedStringEquals(char* expected, char* actual) {
    safe_assert(actual != NULL);
    safe_assert(strlen(actual) == strlen(expected));
    safe_assert(strcmp(actual, expected) == 0);
}

suite("T9") {
    // Test case: Empty trie initialization.
    test("Empty initialization") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);
        DestroyT9(dict);
    }

    // Test case: Adding words and predicting using an empty trie.
    test("PredictT9 works correctly with InitializeEmptyT9") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "2665#");
        AssertReturnedStringEquals("cool", word);

        DestroyT9(dict);
    }

    // Test case: Initializing from a valid dictionary file.
    test("InitializeFromFileT9 with non-null pointer") {
        const char* validFileName = "test_dictionary.txt";
        FILE* file = fopen(validFileName, "w");
        fprintf(file, "book\ncool\n");
        fclose(file);

        T9* dict = InitializeFromFileT9(validFileName);
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "2665#");
        AssertReturnedStringEquals("cool", word);

        DestroyT9(dict);
    }

    // Test case: Invalid dictionary content.
    test("InitializeFromFileT9 with invalid dict content") {
        const char* validFileName = "test_invalid_dict.txt";
        FILE* file = fopen(validFileName, "w");
        fprintf(file, "book\nyu77\n");
        fclose(file);

        T9* dict = InitializeFromFileT9(validFileName);
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "2665");
        char* w2 = PredictT9(dict, "1234");
        AssertReturnedStringEquals("book", word);
        safe_assert(w2 == NULL);

        DestroyT9(dict);
    }

    // Test case: Handling null file input.
    test("File is null") {
        T9* dict = InitializeFromFileT9(NULL);
        safe_assert(dict == NULL);
    }

    // Test case: Word contains uppercase letters.
    test("Word not lowercase") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "bOok");
        char* word = PredictT9(dict, "2665");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Adding an empty word.
    test("Empty word") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "");
        char* word = PredictT9(dict, "");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Duplicate word addition.
    test("Word already exists") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");
        AddWordToT9(dict, "book");

        char* word = PredictT9(dict, "2665##");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Word contains invalid symbols.
    test("Word with symbol *") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book*");
        char* word = PredictT9(dict, "2665*");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Words with similar prefixes.
    test("Similar words") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "word");
        AddWordToT9(dict, "wordd");

        char* word = PredictT9(dict, "9673");
        char* word2 = PredictT9(dict, "96733");

        AssertReturnedStringEquals("word", word);
        AssertReturnedStringEquals("wordd", word2);

        DestroyT9(dict);
    }

    // Test case: Predicting from an empty trie.
    test("List is empty") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "2665");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Input number is null.
    test("Number is null") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        char* word = PredictT9(dict, "");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Input contains invalid characters.
    test("Number contains invalid characters") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        char* word = PredictT9(dict, "266)");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Input sequence contains digits after '#'.
    test("Digit after #") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "bookkk");
        char* word = PredictT9(dict, "2665#5");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Input starts with '#'.
    test("Number starts with #") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        char* word = PredictT9(dict, "#2665");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Multiple '#' characters in the input.
    test("Number with multiple #") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");
        char* word = PredictT9(dict, "2665##");
        safe_assert(word == NULL);

        DestroyT9(dict);
    }

    // Test case: Input contains invalid characters like 0, *, or 1.
    test("Invalid input: 0, *, or 1") {
        T9* dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        char* word1 = PredictT9(dict, "2661");
        char* word2 = PredictT9(dict, "2660");
        char* word3 = PredictT9(dict, "266*");

        safe_assert(word1 == NULL);
        safe_assert(word2 == NULL);
        safe_assert(word3 == NULL);

        DestroyT9(dict);
    }
}
