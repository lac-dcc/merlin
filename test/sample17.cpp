#include <stdio.h>

void foo(int a, int b, int c) {
  int i = a + b;
  while (i > 0) {
    i--;
  }

  while (i > c) {
    i--;
  }
}