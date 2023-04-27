int foo(int n) {
  if (n % 2 == 0) {
    return 0;
  }
  for (int i = 3; i * i < n; i += 2) {
    if (n % i == 0) {
    }
  }
  return 1;
}