# Wordle Game

## Overview

This project is a command-line implementation of the popular word-guessing game, Wordle. The game allows players to guess a five-letter word within six tries, providing feedback on the accuracy of each guess.

## Acknowledgments

Zakariye Abdilahi

## Features

- **Command-Line Interface**: A simple, text-based version of Wordle.
- **User Input Handling**: Prompts users for guesses and validates input.
- **Feedback System**: Provides color-coded hints for each guess:
  - Green: Correct letter in the correct position.
  - Yellow: Correct letter in the wrong position.
  - No color: Incorrect letter.
- **Random Word Selection**: Selects a target word from a hard-coded dictionary.

## How to Play

1. The game randomly selects a five-letter target word.
2. You have six attempts to guess the word.
3. After each guess, the game provides feedback:
   - Letters in the correct position are highlighted in green.
   - Letters in the word but in the wrong position are highlighted in yellow.
   - Letters not in the word remain unhighlighted.
4. The game ends when you guess the word correctly or after six incorrect guesses.

## Implementation Details

### Functions

- **get_guess(int turn, char *guess)**: Prompts the user for a guess and stores it in the provided buffer.
- **check_guess(const char *guess, const char *target, char result[])**: Compares the guess with the target word and fills the result array with feedback.
- **print_report(const char *guess, const char result[])**: Prints the guess with appropriate color-coding based on the feedback.
- **play_game(const char *target)**: Manages the game loop, calling the necessary functions to play a full game of Wordle.

### Dictionary

The target words are selected from a hard-coded dictionary of five-letter words.

## Getting Started

### Prerequisites

- C Compiler (e.g., GCC)

### Compiling the Program

To compile the program, run the following command in your terminal:
```sh
gcc wordle.c -o wordle




