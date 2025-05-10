#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10  // Maximum grid size

/*Functions used for program*/

// Function which sets up board with empty spaces
// Function uses 2 loops to print empty rows and collumns based on inputted size
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int boardSize) {
  for (int i = 0; i < boardSize; i++) {    // Iterates rows
    for (int j = 0; j < boardSize; j++) {  // Iterates collumns
      board[i][j] = ' ';                   // Prints blanks
    }
  }
}

// Function which displays the CURRENT state of the board
// Function uses 2 loops to constantly update the board after each move
void printBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {    // Iterates rows
    for (int j = 0; j < size; j++) {  // Iterates collumns
      printf(" %c ", board[i][j]);    // Prints value in each coordinate
                                      // according to what was inputted
      if (j < size - 1) printf("|");  // Print vertical seperators
    }
    printf("\n");
    if (i < size - 1) {
      for (int k = 0; k < size; k++) {
        printf("---");  // Print horizontal seperators
      }
      printf("\n");
    }
  }
}

// Function which takes a players move and makes sure it is in bounds
// Function will run the inputted value through while statement to determine
// if value is valid
int playerMove(char board[MAX_SIZE][MAX_SIZE], int size, char player) {
  int row, col;  // Coordinate place holders

  // Statement to ask player for move
  printf("Player %c, enter your move (row and column): ", player);
  scanf("%d %d", &row, &col);  // Stores input

  // While statement to determine if the input is within board bounds
  while (row < 1 || row > size || col < 1 || col > size ||
         board[row - 1][col - 1] != ' ') {
    printf("Invalid move. Try again: ");
    scanf("%d %d", &row, &col);
  }
  board[row - 1][col - 1] = player;  // Board is updated
  return 1;
}

// Function checks for a winning condition by evaluating rows, columns, and
// diagonals
// Functions goes through each coordinate adding it to a counter
// If the counter is equal to the size of the row/col, win is determined
int checkWin(char board[MAX_SIZE][MAX_SIZE], int size) {
  int row, col, coor;
  int counter;

  for (row = 0; row < size; row++) {  // Checks rows for win
    for (col = 0; col < size; col++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == size) return 1;  // Player wins
    if (counter == size) return 2;  // AI wins
    counter == 0;
  }

  for (col = 0; col < size; col++) {  // Checks columns for win
    for (row = 0; row < size; row++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == size) return 1;  // Player wins
    if (counter == size) return 2;  // AI wins
    counter == 0;
  }

  for (coor = 0; coor < size; coor++) {  // Checks decresing diagonal for win
    if (board[coor][coor] = 'X') counter++;
    if (board[coor][coor] = 'O') counter--;

    if (counter = size) return 1;
    if (counter = -size) return 2;
  }

  for (int coor = 0; coor < size;
       coor++) {  // Checks increasing diagonal for win
    if (board[size - 1 - coor][coor] == 'X') counter++;
    if (board[size - 1 - coor][coor] == 'O') counter--;
  }
  if (counter == size) return 1;
  if (counter == -size) return 2;

  return 0;  // No win
}

int checkDraw(char board[MAX_SIZE][MAX_SIZE], int size) {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (board[row][col] == '_')
        return 0;  // If there is a blank space, no draw
    }
  }
  return 1;  // No blank places, therefore draw
}

// Function determines where to play the next move according to what the board
// looks like Function
int positionMove(char board[MAX_SIZE][MAX_SIZE], int size, int winrow,
                 int wincol) {
  int row, col, coor;
  int counter;

  // Following statements will play a move if AI is about to win

  for (row = 0; row < size; row++) {  // Checks rows for win
    for (col = 0; col < size; col++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == -size + 1) {              // The AI is 1 away from winning
      winrow = row;                          // This row will win
      for (coor = 0; coor < size; coor++) {  // Find the empty coordinate
        if (board[row][coor] = '_') winrow = coor;
      }
      return 1;
    }
    counter = 0;
  }

  for (col = 0; col < size; col++) {  // Checks columns for win
    for (row = 0; row < size; row++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == -size + 1) {
      wincol = col;                          // This column will win
      for (coor = 0; coor < size; coor++) {  // Find the empty coordinate
        if (board[coor][col] = '_') wincol = coor;
      }
      return 1;
    }
    counter = 0;
  }

  for (coor = 0; coor < size; coor++) {  // Checks decresing diagonal for win
    if (board[coor][coor] = 'X') counter++;
    if (board[coor][coor] = 'O') counter--;
  }
  if (counter == -size + 1) {
    for (int coor = 0; coor < size; coor++) {
      if (board[coor][coor] == '_') {
        winrow = coor;
        wincol = coor;
        return 1;
      }
    }
  }

  for (coor = 0; coor < size; coor++) {  // Checks increasing diagonal for win
    if (board[size - 1 - coor][coor] == 'X') counter++;
    if (board[size - 1 - coor][coor] == 'O') counter--;
  }
  if (counter == -size + 1) {
    for (int i = 0; i < size; i++) {
      if (board[size - 1 - i][i] == '_') {
        winrow = (size - 1 - i);
        wincol = i;
        return 1;
      }
    }
  }

  // Following statements will play a move if player is about to win

  for (row = 0; row < size; row++) {  // Checks rows for win
    for (col = 0; col < size; col++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == size - 1) {  // The player is 1 away from winning
      winrow = row;             // This row will win
      for (coor = 0; coor < size; coor++) {  // Find the empty coordinate
        if (board[row][coor] = '_') winrow = coor;
      }
      return 1;
    }
    counter = 0;
  }

  for (col = 0; col < size; col++) {  // Checks columns for win
    for (row = 0; row < size; row++) {
      if (board[row][col] = 'X') counter++;
      if (board[row][col] = 'O') counter--;
    }
    if (counter == size - 1) {
      wincol = col;                          // This column will win
      for (coor = 0; coor < size; coor++) {  // Find the empty coordinate
        if (board[coor][col] = '_') wincol = coor;
      }
      return 1;
    }
    counter = 0;
  }

  for (coor = 0; coor < size; coor++) {  // Checks decresing diagonal for win
    if (board[coor][coor] = 'X') counter++;
    if (board[coor][coor] = 'O') counter--;
  }
  if (counter == size - 1) {
    for (int coor = 0; coor < size; coor++) {
      if (board[coor][coor] == '_') {
        winrow = coor;
        wincol = coor;
        return 1;
      }
    }
  }

  for (coor = 0; coor < size; coor++) {  // Checks increasing diagonal for win
    if (board[size - 1 - coor][coor] == 'X') counter++;
    if (board[size - 1 - coor][coor] == 'O') counter--;
  }
  if (counter == size - 1) {
    for (int i = 0; i < size; i++) {
      if (board[size - 1 - i][i] == '_') {
        winrow = (size - 1 - i);
        wincol = i;
        return 1;
      }
    }
  }
}

// Function determines what move the AI should make by running it through the
// positionMove function

void AiMove(char board[MAX_SIZE][MAX_SIZE], int size) {
  int randoRow, randoCol, winrow, wincol;

  // First check if the AI can win and make the move
  // Then check if the player can win and counter it
  if (1 == positionMove(board, size, winrow, wincol)) {
    board[winrow][wincol] = 'O';
    return;
  }

  // If countermove cannot be made, play a random move
  do {
    randoRow = rand() % size;  // Random row
    randoCol = rand() % size;  // Random column
    if (board[randoRow][randoCol] ==
        '_') {  // If spot is avaliable, place move there
      break;
    }
  } while (1);
  board[randoRow][randoCol] = 'O';
}

/*Main program code*/

int main(void) {
  int inputSize;
  int gameMode;
  int playerScore, aiScore;
  int userScore = 0, cpuScore = 0;
  char playAgain;

  printf(
      "Welcome to Tik-Tac-Toe! Ready to Play? \nEnter the desired game "
      "board "
      "size (3 to 10): ");
start:
  scanf("%d", &inputSize);
  if (inputSize < 3 || inputSize > 10) {  // If out of bounds
    printf("Size is out of bounds. Try again: ");
    goto start;
  }
  char board[inputSize][inputSize];

  printf("Choose a game mode! 1 for single player, 2 for multiplayer: ");
  scanf("%d", &gameMode);

  // Following code is for Player verses AI
  if (gameMode) {
    printf("Player Score: %d \nAI Score: %d\n", playerScore);
    initializeBoard(board, inputSize);
    printBoard(board, inputSize);

    do {
      playerMove(board, inputSize, 'X');  // Player move
      printBoard(board, inputSize);

      if (!((checkDraw(board, inputSize) == 0) &&
            (checkWin(board, inputSize) ==
             0)))  // If the player has a winning move (returning 1), break out
                   // of loop
        break;

      AiMove(board, inputSize);  // AI move
      printf("Computer Moved\n");
      printBoard(board, inputSize);

      if (!((checkDraw(board, inputSize) == 0) &&
            (checkWin(board, inputSize) ==
             0)))  // If the AI has a winning move (returning 2), break out of
                   // loop
        break;

    } while (1);  // Winning statements

    if (checkDraw(board, inputSize) == 1) {
      printf("Draw!\n");
    }
    if (checkWin(board, inputSize) == 1) {
      printf("Player Won!\n");
      userScore++;  // Add to users score
    }
    if (checkWin(board, inputSize) == 1) {
      printf("AI Won!\n");
      aiScore++;  // Add to AI score
    }
    printf("Do you want to play again? (Y/N): ");
    scanf(" %c ", &playAgain);
    if (playAgain == 'n' || playAgain == 'N') {
      printf("Final Score\n");
      printf("Player Score: %d \nAI Score: %d\n", userScore, cpuScore);
      return 0;
    }

  } else {
    // Following code is for Player verses Player
    printf("Player 1 Score: %d \nPlayer 2 Score: %d\n", userScore, aiScore);
    initializeBoard(board, inputSize);
    printBoard(board, inputSize);

    do {
      playerMove(board, inputSize, 'X');
      printBoard(board, inputSize);

      if (!((checkDraw(board, inputSize) == 0) &&
            (checkWin(board, inputSize) ==
             0)))  // If player 1 has a winning move, break out of loop
        break;

      playerMove(board, inputSize, 'O');
      printBoard(board, inputSize);

      if (!((checkDraw(board, inputSize) == 0) &&
            (checkWin(board, inputSize) == 0)))
        break;

    } while (1);  // Winning statements

    if (checkDraw(board, inputSize) == 1) {
      printf("Draw!\n");
    }
    if (checkWin(board, inputSize) == 1) {
      printf("Player 1 Won!\n");
      userScore++;
    }
    if (checkWin(board, inputSize) == 2) {
      printf("Player 2 Won!\n");
      aiScore++;
    }
    printf("Do you want to play again? (Y/N): ");
    scanf(" %c", &playAgain);
    if (playAgain == 'n' || playAgain == 'N') {
      printf("Final Score\n");
      printf("Player 1 Score: %d \nPlayer 2 Score: %d\n", playerScore, aiScore);
      return 0;
    }
  }
  while (1);
}
