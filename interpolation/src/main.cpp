#include <iostream>
#include "PolynomialInterpolation.hpp"

using namespace std;

int main() {
  int N, numVar;
  long xi, yi, zi, wi;
  vector<vector<double>> matrix(15, vector<double>(15));
  vector<double> X(15);

  cin >> N;

  for(int i = 0; i < N; i++) {
    cin >> xi >> yi;
    X[i] = xi;
    matrix[i][0] = yi;
  }

  cout << "F(x) = " << NewtonInterpolation(X, matrix, N) << '\n';

}
