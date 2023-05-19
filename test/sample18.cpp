#include <stdio.h>

// NOT OK
int foo(int* b, int* e) {
  int sum = 0;
  while (b != e) {
    sum += *b;
  }
  return sum;
}

// OK
int foo(int* b, int* e, int* v) {
  int sum = 0;
  int B = *b;
  const int E = *e;
  while (B != E) {
    sum += v[B];
    B++;
  }
  return sum;
}