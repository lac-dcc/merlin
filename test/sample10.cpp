int main() {
  int i, j, l, n, m, sum, fat, fat2;
  n = 10;
  m = 15;
  l = 0;
  fat = 1;
  fat2 = 1;
  for (j = 1; j <= n; j++) {
    for (i = l; i <= j; i++) {
      fat *= i;
    }
    for (i = 1; i <= m; i++) {
      fat2 *= i;
    }
    sum += fat + fat2;
  }
  return sum;
}
