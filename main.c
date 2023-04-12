#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int board[81] = {0};

int isDigitValid(int digit, int idx) {
  int col = (idx % 9);
  int row = (idx / 9);
  int box = (idx % 9 / 3) + 3 * (idx / 27);

  // row check
  for (int i = 1; i <= col; i++) {
    if (board[idx - i] == digit)
      return 0;
  }

  // column check
  for (int i = 1; i <= row; i++) {
    if (board[idx - (i * 9)] == digit)
      return 0;
  }

  // box check
  for (int i = 1; i < 81; i++) {
    if (i == idx)
      continue;
    int tbox = (i % 9 / 3) + 3 * (i / 27);
    if (tbox == box && board[i] == digit) {
      return 0;
    }
  }

  return digit;
}

void drawBoard() {
  printf("\e[1;1H\e[2J");
  printf("\n");
  for (int i = 0; i < 81; i++) {
    printf("%d", board[i]);
    if (i % 3 == 2) {
      printf(" ");
    }
    if (i % 9 == 8) {
      printf("\n");
    }
    if (i % 27 == 26) {
      printf("\n");
    }
  }
  printf("\n");
}

void shakeOptions(int options[]) {
  for (int i = 0; i < 8; i++) {
    if (options[i] == 0) {
      options[i] = options[i + 1];
      options[i + 1] = 0;
    }
  }
}

void intHandler(int dummy) {
  drawBoard();
  exit(0);
}

int main() {
  srand(time(NULL));
  signal(SIGINT, intHandler);

  for (int k = 0; k < 9; k++) {
    int options[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int optionsLength = 9;
    for (int i = 0; i < 9; i++) {
      int curIdx = i + (k * 9);
      int isValid = 0;
      int candidateIdx = 0;
      int candidate = 0;

      do {
        candidateIdx = rand() % optionsLength;
        candidate = options[candidateIdx];
        isValid = isDigitValid(candidate, curIdx);

        // need to restart row if it cant finish
        if (isValid == 0) {
          i = -1;
          optionsLength = 9;
          for (int j = 0; j < 9; j++)
            options[j] = j + 1;
          break;
        }
      } while (isValid == 0);

      if (isValid != 0) {
        options[candidateIdx] = 0;
        optionsLength--;
        shakeOptions(options);
        board[i + (k * 9)] = isValid;
      }
    }
  }

  drawBoard();

  return 0;
}
