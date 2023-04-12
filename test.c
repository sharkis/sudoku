#include <stdio.h>

// trying to determine 9x9 box

int main() {
  for (int i = 0; i < 81; i++) {
    printf("%d", (i % 9 / 3) + 3 * (i / 27));
    if (i % 9 == 8) {
      printf("\n");
    }
  }
  printf("\n");
  return 0;
}
