#include <iostream>
#include <stdlib.h> 
using namespace std;

void printMatrix(int** M, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }
}

int matrix_multiplication(int** A, int** B, int** C, int a_row, int a_col, int b_row, int b_col) {
  if (a_col != b_row)
    return 0;
  for (int i = 0; i < a_row; i++) {
    for (int j = 0; j < a_col; j++) {
      for (int k = 0; k < b_col; k++) {
        C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return 1;
}

void alocateMatrixNxM(int**& A, int n, int m) {
    A = new int*[n];
    for(int i = 0; i < n; i++) {
        A[i] = new int [m];
    }
}
void fillMatrix(int** A, int n, int m) {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j++) {
            A[i][j] = rand()%1000;
        }
    }
}
void zeraMatriz(int** A, int n, int m) {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j++) {
            A[i][j] = 0;
        }
    }
}
void deleteMatrix(int**& A, int n, int m) {
    for(int i = 0; i < n; i ++) {
        delete[] A[i];
    }
    delete[] A;
}
int main() { 
    int** A; int** B; int** C;
    int rowsA, colsA, rowsB, colsB;
    cin >> rowsA >> colsA >> rowsB >> colsB;
    
    alocateMatrixNxM(A, rowsA, colsA);
    alocateMatrixNxM(B, rowsB, colsB);
    alocateMatrixNxM(C, rowsA, colsB);
    fillMatrix(A, rowsA, colsA);
    fillMatrix(B, rowsB, colsB);
    zeraMatriz(C, rowsA, colsB);
    matrix_multiplication(A, B, C, rowsA, colsA, rowsB, colsB);
    deleteMatrix(A, rowsA, colsA);
    deleteMatrix(B, rowsB, colsB);
    deleteMatrix(C, rowsA, colsB);

    return 0; 
}