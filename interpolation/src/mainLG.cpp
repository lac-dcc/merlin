#include <iostream>
#include "PolynomialInterpolation.hpp"
using namespace std;



void fillRow2Var(long x, long y, vector<double>& M) {
    M[0] = 1;
    M[1] = x;
    M[2] = y;
    M[3] = x*y;
    M[4] = x*x;
    M[5] = y*y;
    M[6] = x*y*y;
    M[7] = x*x*y;
    M[8] = x*x*y*y;
}

void fillRow3Var(long x, long y, long z, vector<double>& M) {
    M[0] = 1;
    M[1] = x;
    M[2] = y;
    M[3] = z;
    M[4] = x*x;
    M[5] = x*y;
    M[6] = x*z;
    M[7] = y*y;
    M[8] = y*z;
    M[9] = z*z;
    M[10] = x*y*z;
    M[11] = x*y*y;
    M[12] = x*y*x;
    M[13] = x*z*z;
    M[14] = x*z*x;
}

int main() {
  int N, numVar;
  long xi, yi, zi, wi;

  // F(x,y) = a0 + a1x + a2y + a3xy + a4x² + a5y² + a6xy² + a7x²y + a8x²y² ...
  vector<vector<double>> matrix(15, vector<double>(15));
  vector<double> fi(15);
  
  cin >> numVar;
  cin >> N; 

  if(numVar == 2) {
    for(int i = 0; i< N; i++) {
      cin >> xi >> yi >> zi;
      fi[i] = zi;
      fillRow2Var(xi, yi, matrix[i]);
    }
  } else if(numVar == 3) {
    for(int i = 0; i< N; i++) {
      cin >> xi >> yi >> zi >> wi;
      fi[i] = wi;
      fillRow3Var(xi, yi, zi, matrix[i]);
    }
  } else {
    cout << "Invalid variable number\n";
  }
  // Determinant of original matrix
  double det = calculateDeterminant(matrix, N);
  
  /*
  M = Number of Interpolations
  (x, y) = pairs to interpolate
  z = F(x,y)
  */
  int M;
  long x, y, z, w;
  long xaux, yaux, zaux;
  double detj;

  cin >> M;
  for(int i = 0; i < M; i++) {
    if(numVar == 2) {
      cin >> x >> y;
      z = 0;
      for(int j = 0; j < N; j++) {
        xaux = matrix[j][1]; yaux = matrix[j][2];
        fillRow2Var(x, y, matrix[j]);
        detj = calculateDeterminant(matrix, N);
        z += detj * fi[j] / det;
        fillRow2Var(xaux, yaux, matrix[j]);
      }
      cout << "F(" << x << "," << y << ") = " << z << '\n';

    } else if(numVar == 3) {
      cin >> x >> y >> z;
      w = 0;
      for(int j = 0; j < N; j++) {
        xaux = matrix[j][1]; yaux = matrix[j][2]; zaux = matrix[j][3];
        fillRow3Var(x, y, z, matrix[j]);
        detj = calculateDeterminant(matrix, N);
        w += detj * fi[j] / det;
        fillRow3Var(xaux, yaux, zaux, matrix[j]);
      }
      cout << "F(" << x << "," << y << "," << z << ") = " << w << '\n';
    }
  }
 
  cout << "Finished\n";
  return 0;
}