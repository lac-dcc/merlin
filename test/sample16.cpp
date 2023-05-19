#include <stdio.h>

void foo(int* v, int index) {
  int value = v[index];
  int i;
  for (i = index; i != 0; --i) {
    v[i] = v[i - 1];
  }

  v[0] = value;
}