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

void alocaMatriz(int**& A, int n, int m) {
    A = new int*[n];
    for(int i = 0; i < n; i++) {
        A[i] = new int [m];
    }
}
void preencheMatriz(int** A, int n, int m) {
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
void deletaMatriz(int**& A, int n, int m) {
    for(int i = 0; i < n; i ++) {
        delete[] A[i];
    }
    delete[] A;
}
int main() { 
    int** A; int** B; int** C;
    alocaMatriz(A, 3, 3);
    alocaMatriz(B, 3, 3);
    alocaMatriz(C, 3, 3);
    preencheMatriz(A, 3, 3);
    preencheMatriz(B, 3, 3);
    zeraMatriz(C, 3, 3);
    matrix_multiplication(A, B, C, 3, 3, 3, 3);
    deletaMatriz(A, 3, 3);
    deletaMatriz(B, 3, 3);
    deletaMatriz(C, 3, 3);

    int** D; int** E; int** F;
    alocaMatriz(D, 4, 2);
    alocaMatriz(E, 2, 3);
    alocaMatriz(F, 4, 3);
    preencheMatriz(D, 4, 2);
    preencheMatriz(E, 2, 3);
    zeraMatriz(F, 4, 3);
    matrix_multiplication(D, E, F, 4, 2, 2, 3);
    deletaMatriz(D, 4, 2);
    deletaMatriz(E, 2, 3);
    deletaMatriz(F, 4, 3);

    int** G; int** H; int** I;
    alocaMatriz(G, 7, 8);
    alocaMatriz(H, 8, 3);
    alocaMatriz(I, 7, 3);
    preencheMatriz(G, 7, 8);
    preencheMatriz(H, 8, 3);
    zeraMatriz(I, 7, 3);
    matrix_multiplication(G, H, I, 7, 8, 8, 3);
    deletaMatriz(G, 7, 8);
    deletaMatriz(H, 8, 3);
    deletaMatriz(I, 7, 3);

    int** J; int** K; int** L;
    alocaMatriz(J, 13, 11);
    alocaMatriz(K, 11, 12);
    alocaMatriz(L, 13, 12);
    preencheMatriz(J, 13, 11);
    preencheMatriz(K, 11, 12);
    zeraMatriz(L, 13, 12);
    matrix_multiplication(J, K, L, 13, 11, 11, 12);
    deletaMatriz(J, 13, 11);
    deletaMatriz(K, 11, 12);
    deletaMatriz(L, 13, 12);

    int** M; int** N; int** O;
    alocaMatriz(M, 5, 16);
    alocaMatriz(N, 16, 3);
    alocaMatriz(O, 5, 3);
    preencheMatriz(M, 5, 16);
    preencheMatriz(N, 16, 3);
    zeraMatriz(O, 5, 3);
    matrix_multiplication(M, N, O, 5, 16, 16, 3);
    deletaMatriz(M, 5, 16);
    deletaMatriz(N, 16, 3);
    deletaMatriz(O, 5, 3);
    return 0; 
}