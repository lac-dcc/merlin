#include <stdio.h>

int main() {
  for (int i = 0; i <= 10; i++) {
    for (int j = 0; j <= 10; j++) {
      for (int k = 0; k <= 10; k++) {
        if (i + j - k % 10 == 0) {
          return 1;
        }
      }
    }
  }

  return 0;
}