void foo(int a, int b, int c, int d) {
  int i = 0;
  while (i < a) {
    for (int j = b; j < c; j++) {
      int k = 0;
      do {
        k++;
      } while (k < d);
    }
  }
}

int main() {
  return 0;
}