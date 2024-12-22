# software-development
**Project 1: Title:** Custom Word Count Implementation in C

**Project Description:**
Developed a custom command-line utility in C that replicates and extends the functionality of the `wc` (word count) command. This program processes text files and provides statistics on the number of lines, words, and characters. It supports multiple options for flexible output and handles edge cases to ensure robustness.

**Key Features:**
1. Command-line Interface:
   - Implemented options for displaying specific statistics:
      `-l`: Line count
      `-w`: Word count
      `-c`: Character count
   - Default behavior displays all statistics (lines, words, characters) for each file.

2. Multi-file Support:
   - Processes one or more input files.
   - Aggregates total line counts across multiple files.

3. Error Handling:
   - Detects and skips non-existent or inaccessible files with descriptive error messages.
   - Validates input arguments and provides usage instructions for invalid options or missing files.

4. Edge Case Handling:
   - Handles empty files and files with unusual content (e.g., lines exceeding typical buffer size, filenames with spaces).
   - Processes filenames passed as quoted strings (e.g., "file name with spaces").

5. Buffer Safety:
   - Ensures safe processing of file lines with a predefined buffer size, avoiding memory overflow issues.

**Summary Statement:**
Utilized C programming to develop a robust command-line tool replicating the `wc` command, showcasing skills in file I/O, string manipulation, and error handling. The project aimed to provide detailed file statistics while ensuring reliability and user-friendly features for processing multiple files. Designed and implemented features to handle edge cases, and validate user input.
____________________________________________________________________________
**Project2: T9 Predictive Text Trie Implementation**

**Description:**
Designed and implemented a T9 predictive text system in C, using a trie data structure to dynamically store words mapped to numeric key sequences. Developed a library (t9_lib.c) with robust functionality to build the trie, add words, and predict text sequences. Ensured efficiency, scalability, and memory correctness for handling large dictionaries.

**Key Features:**

1. Trie-Based Storage:
Efficiently organizes words using T9 numeric sequences, supporting rapid lookup and dynamic word addition.

2. Collision Handling:
Manages overlapping sequences using linked lists at trie nodes, enabling seamless traversal for multiple matching words.

3. Dynamic Word Addition:
Allows users to add new words to the trie, updating it in real-time without disrupting existing functionality.

4. Interactive Predictions:
Predicts words for given numeric sequences and supports "#" traversal for additional matches.

**Tools & Skills:**
C, dynamic memory management, data structures (trie, linked list), file I/O, Makefile, debugging with valgrind, unit testing.

**Achievements:**
Passed 30/33 test cases for functionality, memory safety, and edge cases.
Optimized performance and achieved no memory leaks or errors verified via valgrind.
Developed a demo program to showcase interactive predictions based on numeric T9 inputs.







