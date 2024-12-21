#ifndef T9_PRIV_H_
#define T9_PRIV_H_

typedef struct T9 {
    char* word;
    struct T9* branch[9];
} T9;

// Allocates a new T9 instance with empty internal dictionary.
T9* InitializeEmptyT9();

// Allocates a new T9 instance and initializes its dictionary to include all
// words in the given file.
T9* InitializeFromFileT9(const char* filename);

// Add the given word to the internal T9 dictionary.
void AddWordToT9(T9* dict, const char* word);

// Identify a word which is specified by the given sequence of T9 commands.
char* PredictT9(T9* dict, const char* nums);

// Destroys the given T9 implementation, and frees all associated memory.
void DestroyT9(T9* dict);

#endif  // T9_PRIV_H_
