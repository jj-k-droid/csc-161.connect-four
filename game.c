#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define INPUT_LENGTH 3

// cell states on the board. data type for the player and the board
enum cell_type {
  EMPTY,
  YELLOW,
  RED
};

// Constants to print in bold red text, bold yellow text, and to reset text style
#define START_RED "\033[1m\033[31m"
#define START_YELLOW "\033[1m\033[33m"
#define RESET_COLOR "\033[0m"

// outputs the board
void print_board(enum cell_type board[]) {
  // column names
  printf("  A   B   C   D   E   F   G\n");

  // goes through each row on the board
  for (int i = 0; i < BOARD_HEIGHT; i++) {

    // goes through each element in the row
    for (int j = 0; j < BOARD_WIDTH; j++) {
      printf("| ");

      // checks to see if the cell should be colored (depending on if it contains RED or YELLOW) or empty
      if (board[i * BOARD_WIDTH + j] == RED) {
        printf(START_RED "R " RESET_COLOR);
      } else if (board[i * BOARD_WIDTH + j] == YELLOW) {
        printf(START_YELLOW "Y " RESET_COLOR);
      } else {
        printf("  ");
      }
    }
    // prints at the end of each row
    printf("|\n");
  }
  printf("_____________________________\n");
}

// checks to see if the user's input is valid
bool is_valid_move(enum cell_type board[], int column) {
  bool is_valid = true;

  // checks if the column the user asked for is full
  if (board[column] != EMPTY) {
    is_valid = false;
  }

  return is_valid;
}

// collects and returns the user's move
int get_move(enum cell_type board[]) {
  int column;
  bool is_valid_input = false;

  do {
    char input[1];

    printf("\nEnter the letter of a column (A-G): ");

    // collects user input. first if checks to see if there is an error in collecting the user's input
    if (fgets(input, INPUT_LENGTH, stdin) == NULL) {
      fprintf(stderr, "Failed to read input from user.\n");
      exit(EXIT_FAILURE);
      // assigns the user's input char to a value from 0 to 7 (if the user's input is from A-G)
    } else if (input[0] == 'A' || input[0] == 'B' || input[0] == 'C' || input[0] == 'D' || input[0] == 'E' || input[0] == 'F' || input[0] == 'G') {
      switch (input[0]) {
        case 'A': {
          column = 0;
          break;
        }
        case 'B': {
          column = 1;
          break;
        }
        case 'C': {
          column = 2;
          break;
        }
        case 'D': {
          column = 3;
          break;
        }
        case 'E': {
          column = 4;
          break;
        }
        case 'F': {
          column = 5;
          break;
        }
        case 'G': {
          column = 6;
          break;
        }
      }
      // moves on to the next iteration (skips the rest of the code below as the user's input is invalid)
    } else {
      printf("Invalid input, try again.\n");
      continue;
    }

    // checks the board to see if the column the user requested is full or not.
    if (is_valid_move(board, column)) {
      is_valid_input = true;
    } else {
      printf("%c is full. Try again.\n", input[0]);
    }
  } while (!is_valid_input);

  return column;
}

// checks to see if the current player has won the game
bool check_win(enum cell_type board[]) {
  // checks all rows for series of cells with 4 in a row (that are not empty) and returns true if there's a match
  for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
    for (int j = 0; j < BOARD_WIDTH - 3; j++) {
      int a = board[i * BOARD_WIDTH + j];
      int b = board[i * BOARD_WIDTH + j + 1];
      int c = board[i * BOARD_WIDTH + j + 2];
      int d = board[i * BOARD_WIDTH + j + 3];
      if ((a == b) &&  (a == c) && (a == d) && ((a != EMPTY) && (b != EMPTY) && (c != EMPTY) && (d != EMPTY))) {
        return true;
      }
    }
  }

  // checks all columns for series of cells with 4 in a row (that are not empty) and returns true if there's a match
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = BOARD_HEIGHT - 1; j > BOARD_HEIGHT - 4; j--) {
      int e = board[j * BOARD_WIDTH + i];
      int f= board[(j - 1) * BOARD_WIDTH + i];
      int g = board[(j - 2) * BOARD_WIDTH + i];
      int h = board[(j - 3) * BOARD_WIDTH + i];
      if ((e == f) && (e == g) && (e == h) && ((e != EMPTY) && (f != EMPTY) && (g != EMPTY) && (h != EMPTY))) {
        return true;
      }
    }
  }

  // checks the left half of the board (from index 0 to 3) for four diagonal cells. returns true if there's a match
  for (int i = 0; i < BOARD_WIDTH - 3; i++) {
    for (int j = BOARD_HEIGHT - 1; j > BOARD_HEIGHT - 4; j--) {
      int a = board[j * BOARD_WIDTH + i];
      int b = board[(j - 1) * BOARD_WIDTH + i + 1];
      int c = board[(j - 2) * BOARD_WIDTH + i + 2];
      int d = board[(j - 3) * BOARD_WIDTH + i + 3];
      if ((a == b) &&  (a == c) && (a == d) && ((a != EMPTY) && (b != EMPTY)  && (c != EMPTY) && (d != EMPTY))) {
        return true;
      }
    }
  }

  // checks the right half of the board (from index 3 to 6) for four diagonal cells. returns true if there's a match
  for (int i = 3; i < BOARD_WIDTH; i ++) {
    for (int j = BOARD_HEIGHT - 1; j > BOARD_HEIGHT - 4; j--) {
      int e = board[j * BOARD_WIDTH + i];
      int f = board[(j - 1) * BOARD_WIDTH + i - 1];
      int g = board[(j - 2) * BOARD_WIDTH + i - 2];
      int h = board[(j - 3) * BOARD_WIDTH + i - 3];
      if ((e == f) && (e == g) && (e == h) && ((e != EMPTY) && (f != EMPTY) && (g != EMPTY) && (h != EMPTY))) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  // game variables
  enum cell_type player[] = {YELLOW, RED};
  enum cell_type board[BOARD_WIDTH * BOARD_HEIGHT] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                                                      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                                                      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                                                      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                                                      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                                                      EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
  int current_player = 0;
  int empty_cells = 42;

  // outputs "--------- CONNECT 4 ---------" with alternating yellow and red text (the dashes are white)
  printf("--------- \033[1m\033[31mC\033[1m\033[33mO\033[1m\033[31mN\033[1m\033[33mN\033[1m\033[31mE\033[1m\033[33mC\033[1m\033[31mT \033[1m\033[33m4 \033[0m---------\n");

  // outputs the initial game board
  print_board(board);

  do {
    bool is_win = false;

    // sets the cell at the column the user chose to the current player
    int column_choice = get_move(board);
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
      // looks for empty cells in the specified column and places a piece in the first empty cell
      if (board[i * BOARD_WIDTH + column_choice] == EMPTY) {
        board[i * BOARD_WIDTH + column_choice] = player[current_player];
        empty_cells--;
        break;
      }
    }

    // outputs the board after the player changes it
    print_board(board);

    // checks to see if the game has been won and outputs the player who won (or if it's a tie) if so and stops the loop
    is_win = check_win(board);
    if (is_win) {
      if (current_player == 0) {
        printf(START_YELLOW "Y" RESET_COLOR);
      } else {
        printf(START_RED "R" RESET_COLOR);
      }
      printf(" wins!\n");
      break;
    } else if (empty_cells == 0) {
      printf("It's a tie!\n");
    }

    // switches the current player
    current_player = (current_player == 0) ? 1 : 0;
  } while (empty_cells > 0); // game keeps running while there are still empty spaces on the board

  return 0;
}
