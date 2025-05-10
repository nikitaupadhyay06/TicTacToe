/*
Title: Tic-Tac-Toe
Author: Nikita Upadhyay
Summary: This program is a simulation of the **Tic-Tac-Toe** game. Players can
implement either two-player mode or player vs Computer (AI mode). The AI will
have basic strategic capabilities and attempt to win if by preventing you from
placing moves. The program will also allow customization of grid size and will
include score tracking across multiple rounds.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10  // Maximum grid size for the Tic-Tac-Toe board

/* Functions used for program */

// INITIALIZEBOARD: Function to initialize the game board with empty spaces
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int boardSize) {
  // Iterate through the board and set each cell to ' ' (empty space)
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      board[i][j] = ' ';
    }
  }
}

// PRINTBOARD: Function to print the current state of the board
void printBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
  // Iterate through each row and column, printing each cell of the board
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf(" %c ", board[i][j]);
      if (j < size - 1) printf("|");  // Print separator between columns
    }
    printf("\n");

    // Print a separator line between rows, except for the last row
    if (i < size - 1) {
      for (int k = 0; k <= size; k++) {
        printf("---");
      }
      printf("\n");
    }
  }
}

// PLAYERMOVE: Function which handles the player's inputs and determines if
// valid or not
int playerMove(char board[MAX_SIZE][MAX_SIZE], int size, char player) {
  int row, col;
  printf("Player %c, enter your move (row and column): ", player);
  scanf("%d %d", &row, &col);

  // Validate the move, ensuring the position is within bounds and unoccupied
  while (row < 1 || row > size || col < 1 || col > size ||
         board[row - 1][col - 1] != ' ') {
    printf("Invalid move. Try again: ");
    scanf("%d %d", &row, &col);
  }

  // Place the player's symbol on the board
  board[row - 1][col - 1] = player;
  return 1;
}

// CHECKWIN: Function to check if there is a winner
int checkWin(char board[MAX_SIZE][MAX_SIZE], int size) {
  int counter;

  // Check rows for a win
  for (int row = 0; row < size; row++) {
    counter = 0;
    for (int col = 0; col < size; col++) {
      if (board[row][col] == 'X') counter++;  // Player X
      if (board[row][col] == 'O') counter--;  // Player O
    }
    if (counter == size) return 1;   // Player X wins
    if (counter == -size) return 2;  // Player O (AI) wins
  }

  // Check columns for a win
  for (int col = 0; col < size; col++) {
    counter = 0;
    for (int row = 0; row < size; row++) {
      if (board[row][col] == 'X') counter++;
      if (board[row][col] == 'O') counter--;
    }
    if (counter == size) return 1;
    if (counter == -size) return 2;
  }

  // Check the decreasing diagonal for a win (top-left to bottom-right)
  counter = 0;
  for (int coor = 0; coor < size; coor++) {
    if (board[coor][coor] == 'X') counter++;
    if (board[coor][coor] == 'O') counter--;
  }
  if (counter == size) return 1;   // Player X wins
  if (counter == -size) return 2;  // Player O (AI) wins

  // Check the increasing diagonal for a win (bottom-left to top-right)
  counter = 0;
  for (int coor = 0; coor < size; coor++) {
    if (board[size - 1 - coor][coor] == 'X') counter++;
    if (board[size - 1 - coor][coor] == 'O') counter--;
  }
  if (counter == size) return 1;   // Player X wins
  if (counter == -size) return 2;  // Player O (AI) wins

  return 0;  // No winner yet
}

// CHECKDRAW: Function to check if the game is a draw (no more moves possible)
int checkDraw(char board[MAX_SIZE][MAX_SIZE], int size) {
  // Iterate through the board to check for any empty spaces
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (board[row][col] == ' ')
        return 0;  // Empty space found, game is not a draw
    }
  }
  return 1;  // No empty spaces, it's a draw
}

// AIMOVE: Function which randomly selects an empty cell for the AI's move
void aiMove(int size, char board[MAX_SIZE][MAX_SIZE]) {
  int row, col;
  srand(time(NULL));  // Seed the random number generator

  do {
    row = rand() % size;  // Random row
    col = rand() % size;  // Random column
    // Check if the selected cell is empty
    if (board[row][col] == ' ') {
      board[row][col] = 'O';  // Place AI marker
      break;
    }
  } while (1);  // Keep looping until an empty cell is found
}

/* Main program code */

int main(void) {
  int inputSize;
  int gameMode;
  int userScore = 0, cpuScore = 0;
  char playAgain;

  do {
    // Prompt user for the board size
    printf("Welcome to Tic-Tac-Toe! Enter board size (3 to 10): ");
    scanf("%d", &inputSize);

    // Check if the size is within valid bounds
    if (inputSize < 3 || inputSize > 10) {
      printf("Size is out of bounds. Try again.\n");
      continue;
    }

    // Create the board of the given size
    char board[inputSize][inputSize];
    initializeBoard(board, inputSize);

    // Prompt user to choose a game mode
    printf("Choose a game mode! 1 for single player, 2 for multiplayer: ");
    scanf("%d", &gameMode);

    int gameEnded = 0;
    printBoard(board, inputSize);

    while (!gameEnded) {
      if (gameMode == 1) {  // Single player mode
        // Player X's move
        playerMove(board, inputSize, 'X');
        printBoard(board, inputSize);

        // Check for win or draw after player's move
        if (checkWin(board, inputSize) == 1) {
          printf("Player won!\n");
          userScore++;
          gameEnded = 1;
        } else if (checkDraw(board, inputSize)) {
          printf("It's a draw!\n");
          gameEnded = 1;
        } else {
          // AI (Player O) makes a move
          aiMove(inputSize, board);
          printf("AI moved:\n");
          printBoard(board, inputSize);

          // Check for win or draw after AI's move
          if (checkWin(board, inputSize) == 2) {
            printf("AI won!\n");
            cpuScore++;
            gameEnded = 1;
          } else if (checkDraw(board, inputSize)) {
            printf("It's a draw!\n");
            gameEnded = 1;
          }
        }
      } else {  // Multiplayer mode
        // Player 1's move (Player X)
        playerMove(board, inputSize, 'X');
        printBoard(board, inputSize);

        // Check for win or draw after Player 1's move
        if (checkWin(board, inputSize) == 1) {
          printf("Player 1 won!\n");
          userScore++;
          gameEnded = 1;
        } else if (checkDraw(board, inputSize)) {
          printf("It's a draw!\n");
          gameEnded = 1;
        } else {
          // Player 2's move (Player O)
          playerMove(board, inputSize, 'O');
          printBoard(board, inputSize);

          // Check for win or draw after Player 2's move
          if (checkWin(board, inputSize) == 2) {
            printf("Player 2 won!\n");
            cpuScore++;
            gameEnded = 1;
          } else if (checkDraw(board, inputSize)) {
            printf("It's a draw!\n");
            gameEnded = 1;
          }
        }
      }
    }

    // Display the scores after the game ends
    printf("Player Score: %d, AI Score: %d\n", userScore, cpuScore);
    printf("Do you want to play again? (Y/N): ");
    scanf(" %c", &playAgain);  // Scan user's choice to play again
  } while (playAgain == 'Y' ||
           playAgain == 'y');  // Repeat the game if the user wants

  // Print final scores after exiting the game loop
}