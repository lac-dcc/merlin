#include <stdio.h>
#include <stdlib.h>
int main(int agrc, char** argv) {
  int fat, fat2, n, m;
  int sum = 0;
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  fat = 1;
  fat2 = 1;
  for (int j = 1; j <= n; j++) {
    for (int i = 1; i <= j; i++) {
      fat *= i;
    }
    for (int i = 1; i <= m; i++) {
      fat2 *= i;
    }
    sum += fat + fat2;
  }
  printf("%d", sum);
  return 0;
}