#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void startstatement(void) {
  printf("Tic Tac To\n");
  printf("X; User\n");
  printf("O; Computer OR User 2\n");
  printf("_; No Value\n");
  printf("By Rhys Grover (1346822) \n");
  printf("When entering row & col leave a space between them!\n");
}

// Set's Every Value in the board to _
void initializeBoard(int size, char board[size][size]) {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      board[row][col] = '_';
    }
  }
}

// Prints the Board
void printBoard(int size, char board[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

void playerMove(int size, char board[size][size], char marker) {
  int row, col;
  do {
    printf("Enter a row & col: ");
    scanf(" %d %d", &row, &col);
    if ((board[row - 1][col - 1] == '_') &&
        (row > 0 && row <= size && col > 0 && col <= size)) {
      break;
    } else {
      printf("Invalid slot\n");
    }
  } while (1);
  board[row - 1][col - 1] = marker;
}

// 0 for no win, 1 for user win, 2 for comp win
int winCheck(int size, char board[size][size]) {
  int row = 0, col = 0, ScoreCount = 0;

  // row checking
  for (row = 0; row < size; row++) {
    for (col = 0; col < size; col++) {
      if (board[row][col] == 'X') ScoreCount++;
      if (board[row][col] == 'O') ScoreCount--;
    }
    if (ScoreCount == size) return 1;
    if (ScoreCount == -size) return 2;
    ScoreCount = 0;
  }

  ScoreCount = 0;

  // Col Checking
  for (col = 0; col < size; col++) {
    for (row = 0; row < size; row++) {
      if (board[row][col] == 'X') ScoreCount++;
      if (board[row][col] == 'O') ScoreCount--;
    }
    if (ScoreCount == size) return 1;
    if (ScoreCount == -size) return 2;
    ScoreCount = 0;
  }

  ScoreCount = 0;

  // Diagnol Check (Top > Bot)
  for (int i = 0; i < size; i++) {
    if (board[i][i] == 'X') ScoreCount++;
    if (board[i][i] == 'O') ScoreCount--;
  }
  if (ScoreCount == size) return 1;
  if (ScoreCount == -size) return 2;

  ScoreCount = 0;

  // Diagnol Check (Bot > Top)
  for (int i = 0; i < size; i++) {
    if (board[size - 1 - i][i] == 'X') ScoreCount++;
    if (board[size - 1 - i][i] == 'O') ScoreCount--;
  }
  if (ScoreCount == size) return 1;
  if (ScoreCount == -size) return 2;

  // If no one has won then return 0
  return 0;
}

int iswinpossible(int size, char board[size][size], int *winrow, int *wincol) {
  int row = 0, col = 0, ScoreCount = 0;

  // The code inside this loop does the same thing but just check's what win is
  // possible in a order, it first checks if the computer can win. if it cant it
  // check if the user can win; If either of these values are true it uses
  // pointers to tell the comouter where to place it's next move

  {  // Section will win game for computer if possible
    // row checking
    for (row = 0; row < size; row++) {
      for (col = 0; col < size; col++) {
        if (board[row][col] == 'X') ScoreCount++;
        if (board[row][col] == 'O') ScoreCount--;
      }
      if (ScoreCount == -size + 1) {
        *winrow = row;
        for (int i = 0; i < size; i++) {
          if (board[row][i] == '_') *wincol = i;
        }
        return 1;
      }
      ScoreCount = 0;
    }

    ScoreCount = 0;

    // Col Checking
    for (col = 0; col < size; col++) {
      for (row = 0; row < size; row++) {
        if (board[row][col] == 'X') ScoreCount++;
        if (board[row][col] == 'O') ScoreCount--;
      }
      if (ScoreCount == -size + 1) {
        *wincol = col;
        for (int i = 0; i < size; i++) {
          if (board[i][col] == '_') *winrow = i;
        }
        return 1;
      }
      ScoreCount = 0;
    }

    ScoreCount = 0;

    // Diagnol Check (Top > Bot)
    for (int i = 0; i < size; i++) {
      if (board[i][i] == 'X') ScoreCount++;
      if (board[i][i] == 'O') ScoreCount--;
    }
    if (ScoreCount == -size + 1) {
      for (int i = 0; i < size; i++) {
        if (board[i][i] == '_') {
          *winrow = i;
          *wincol = i;
          return 1;
        }
      }
    }

    ScoreCount = 0;

    // Diagnol Check (Bot > Top)
    for (int i = 0; i < size; i++) {
      if (board[size - 1 - i][i] == 'X') ScoreCount++;
      if (board[size - 1 - i][i] == 'O') ScoreCount--;
    }
    if (ScoreCount == -size + 1) {
      for (int i = 0; i < size; i++) {
        if (board[size - 1 - i][i] == '_') {
          *winrow = (size - 1 - i);
          *wincol = i;
          return 1;
        }
      }
    }
  }

  {  // Section Will block User from winning if possible
    // row checking
    for (row = 0; row < size; row++) {
      for (col = 0; col < size; col++) {
        if (board[row][col] == 'X') ScoreCount++;
        if (board[row][col] == 'O') ScoreCount--;
      }
      if (ScoreCount == size - 1) {
        *winrow = row;
        for (int i = 0; i < size; i++) {
          if (board[row][i] == '_') *wincol = i;
        }
        return 1;
      }
      ScoreCount = 0;
    }

    ScoreCount = 0;

    // Col Checking
    for (col = 0; col < size; col++) {
      for (row = 0; row < size; row++) {
        if (board[row][col] == 'X') ScoreCount++;
        if (board[row][col] == 'O') ScoreCount--;
      }
      if (ScoreCount == size - 1) {
        *wincol = col;
        for (int i = 0; i < size; i++) {
          if (board[i][col] == '_') *winrow = i;
        }
        return 1;
      }
      ScoreCount = 0;
    }

    ScoreCount = 0;

    // Diagnol Check (Top > Bot)
    for (int i = 0; i < size; i++) {
      if (board[i][i] == 'X') ScoreCount++;
      if (board[i][i] == 'O') ScoreCount--;
    }
    if (ScoreCount == size - 1) {
      for (int i = 0; i < size; i++) {
        if (board[i][i] == '_') {
          *winrow = i;
          *wincol = i;
          return 1;
        }
      }
    }

    ScoreCount = 0;

    // Diagnol Check (Bot > Top)
    for (int i = 0; i < size; i++) {
      if (board[size - 1 - i][i] == 'X') ScoreCount++;
      if (board[size - 1 - i][i] == 'O') ScoreCount--;
    }
    if (ScoreCount == size - 1) {
      for (int i = 0; i < size; i++) {
        if (board[size - 1 - i][i] == '_') {
          *winrow = (size - 1 - i);
          *wincol = i;
          return 1;
        }
      }
    }
  }

  // If nither are possible return 0
  return 0;
}

// 0 for no draw, 1 for draw
int checkDraw(int size, char board[size][size]) {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (board[row][col] == '_') return 0;
    }
  }
  return 1;
}

// Ai Moving
void AiMove(int size, char board[size][size]) {
  int randoRow, randoCol, winrow, wincol;

  // Check for win for AI is possible if so take that route
  // If win for user is possible then block that, if neither go random
  if (1 == iswinpossible(size, board, &winrow, &wincol)) {
    board[winrow][wincol] = 'O';
    return;  // Very Important
  }

  // Random spot that is empty
  do {
    randoRow = rand() % size;
    randoCol = rand() % size;
    if (board[randoRow][randoCol] == '_') {
      break;
    }
  } while (1);
  board[randoRow][randoCol] = 'O';
}

int main(void) {
  startstatement();

  srand(time(NULL));
  // CPU score will be USER2 score in PVP
  int boardsize = 3, CPU_Score = 0, USER_Score = 0, Gamemode = 0;
  char playagain;

  printf("What Gamemode?\nPVP=0 OR PVE=1: ");
  scanf(" %d", &Gamemode);

  printf("Enter the size of the board (3-10): ");
  scanf(" %d", &boardsize);
  if (!(boardsize < 11 && boardsize > 2)) {
    printf("Please Enter A Valid Range");
    return 1;
  }
  char board[boardsize][boardsize];

  do {
    if (Gamemode) {
      // PVP
      printf("User SCORE: %d \nCPU SCORE: %d\n", USER_Score, CPU_Score);
      initializeBoard(boardsize, board);
      printBoard(boardsize, board);

      do {
        playerMove(boardsize, board, 'X');
        printBoard(boardsize, board);

        if (!((checkDraw(boardsize, board) == 0) &&
              (winCheck(boardsize, board) == 0)))
          break;

        AiMove(boardsize, board);
        printf("Computer Moved\n");
        printBoard(boardsize, board);

        if (!((checkDraw(boardsize, board) == 0) &&
              (winCheck(boardsize, board) == 0)))
          break;

      } while (1);

      if (checkDraw(boardsize, board) == 1) {
        printf("Draw!\n");
      }
      if (winCheck(boardsize, board) == 1) {
        printf("User 1 Won\n");
        USER_Score++;
      }
      if (winCheck(boardsize, board) == 2) {
        printf("CPU Won\n");
        CPU_Score++;
      }
      printf("Would you like to play again(y/n): ");
      scanf(" %c", &playagain);
      if (playagain == 'n' || playagain == 'N') {
        printf("FINAL SCORE\n");
        printf("User SCORE: %d \nCPU SCORE: %d\n", USER_Score, CPU_Score);
        return 0;
      }

    } else {
      // PVP
      printf("User SCORE: %d \nUser 2 SCORE: %d\n", USER_Score, CPU_Score);
      initializeBoard(boardsize, board);
      printBoard(boardsize, board);

      do {
        playerMove(boardsize, board, 'X');
        printBoard(boardsize, board);

        if (!((checkDraw(boardsize, board) == 0) &&
              (winCheck(boardsize, board) == 0)))
          break;

        playerMove(boardsize, board, 'O');
        printBoard(boardsize, board);

        if (!((checkDraw(boardsize, board) == 0) &&
              (winCheck(boardsize, board) == 0)))
          break;

      } while (1);

      if (checkDraw(boardsize, board) == 1) {
        printf("Draw!\n");
      }
      if (winCheck(boardsize, board) == 1) {
        printf("User 1 Won\n");
        USER_Score++;
      }
      if (winCheck(boardsize, board) == 2) {
        printf("User 2 Won\n");
        CPU_Score++;
      }
      printf("Would you like to play again(y/n): ");
      scanf(" %c", &playagain);
      if (playagain == 'n' || playagain == 'N') {
        printf("FINAL SCORE\n");
        printf("User SCORE: %d \nUser 2 SCORE: %d\n", USER_Score, CPU_Score);
        return 0;
      }
    }

  } while (1);
}
