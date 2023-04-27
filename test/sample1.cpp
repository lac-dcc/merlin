int is_prime_1(int n) {
  for (int i = 2; i < n - 1; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}