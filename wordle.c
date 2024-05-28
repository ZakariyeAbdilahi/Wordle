#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 6  // 5 characters + 1 for null terminator

void get_guess(const int turn, char *guess) {
    printf("Guess %d: ", turn);
    for (int i = 0; i < 5; ++i) {
        guess[i] = getchar(); // Get a character from the user

        // Stop taking input if a newline character is encountered
        if (guess[i] == '\n') {
            break;
        }
    }

    // Null-terminate the string
    guess[5] = '\0';

    // Clear the input buffer in case there are extra characters
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int check_guess(const char *guess, const char *target, char result[]) {
    int count = 0;

    for (int i = 0; i < 5; ++i) {
        if (guess[i] == target[i]) {
            result[i] = 'g'; // Matched exactly, marked as green
            count++;
        } else if (strchr(target, guess[i]) != NULL) {
            result[i] = 'y'; // Character in guess appears in target, marked as yellow
        } else {
            result[i] = 'x'; // No match, marked as red
        }
    }

    result[5] = '\0'; // Null-terminate the result string
    return count;
}


void print_report(const char *guess, const char result[]) {
    for (int i = 0; i < 5; ++i) {
        if (result[i] == 'g') {
            printf("\033[1;37;42m%c\033[0m", guess[i]); // Green background for exact match
        } else if (result[i] == 'y') {
            printf("\033[1;37;43m%c\033[0m", guess[i]); // Yellow background for partial match
        } else {
            printf("%c", guess[i]); // No match, print normally
        }
    }
    
    printf("\n");
}


void play_game(const char *target) {
    printf("Welcome to Wordle!\n");

    for (int turn = 1; turn <= 6; ++turn) {
        char guess[6];
        get_guess(turn, guess);

        char result[6];
        int matchedCount = check_guess(guess, target, result);

        print_report(guess, result);

        if (matchedCount == 5) {
            printf("Congratulations! You guessed the word correctly: %s\n", target);
            return; // End the game if the word is guessed
        }
    }

    printf("Game over! The correct word was: %s\n", target);
}

// int main() {
//     // Hard-coded dictionary
//     char *dictionary[] = {"hello", "slate", "apple", "grape", "pixel"};

//     // Set the seed for the random number generator
//     srand(time(NULL));

//     // Choose a random word from the dictionary
//     int randomIndex = rand() % (sizeof(dictionary) / sizeof(dictionary[0]));
//     const char *randomWord = dictionary[randomIndex];

//     // Play the game with the randomly chosen word
//     play_game(randomWord);

//     return 0;
// }


// Structure to represent a list of strings
typedef struct {
    char **words;
    size_t size;
} StringList;

// Function to initialize a StringList
StringList initialize_list(size_t initial_size) {
    StringList list;
    list.words = malloc(initial_size * sizeof(char *));
    list.size = 0;
    return list;
}

// Function to add a word to a StringList
void add_word(StringList *list, const char *word) {
    list->words = realloc(list->words, (list->size + 1) * sizeof(char *));
    list->words[list->size] = strdup(word);
    list->size++;
}

// Function to free the memory allocated for a StringList
void free_list(StringList *list) {
    for (size_t i = 0; i < list->size; ++i) {
        free(list->words[i]);
    }
    free(list->words);
}

int main() {
    // Open the file for reading
    FILE *file = fopen("words5.txt", "r");

    // Check if the file exists
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file 'words5.txt'\n");
        return 1;  // Exit with an error code
    }

    // Initialize a list of strings to hold the dictionary
    StringList dictionary = initialize_list(10);  // Starting with an initial size of 10

    // Read words from the file
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%5s\n", word) == 1) {
        add_word(&dictionary, word);
    }

    // Close the file
    fclose(file);

    // Set the seed for the random number generator
    srand(time(NULL));

    // Choose a random word from the dictionary
    int randomIndex = rand() % dictionary.size;
    const char *randomWord = dictionary.words[randomIndex];

    // Play the game with the randomly chosen word
    play_game(randomWord);

    // Free the memory allocated for the dictionary
    free_list(&dictionary);

    return 0;
}

