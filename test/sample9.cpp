void loop(int m, int n) {
  int a = (m + n) / 2;

  for (int i = 0; i < m; i += 4 * n) {
    int b = 0;
    int j;
    for (j = n * m; j >= 0; j -= 4 * n) {
      int c = a * 100;
      b += c * (j + i);
    }
  }
}

int main() {
  int n = 5 + 2;
  int m = 10;
  loop(m, n);

  return 0;
}