#include "PolynomialInterpolation.hpp"
#include <sstream>
#include <iostream>
using namespace std;

/*
Function to calculate divided differences.
x: vector of x values
table: Table used to store the divided differences, table[*][0] must be initialized with the y values 
n: number of pairs (x, y)
*/
void DividedDifferenceTable(std::vector<double>& x, std::vector<std::vector<double>>& table, int n) {
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < n - j; i++) {
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
    }
  }
}

string NewtonInterpolation(std::vector<double>& x, std::vector<std::vector<double>>& table, int n) {
    stringstream formula;
    DividedDifferenceTable(x, table, n);
    for(int i = 0; i < n; i ++) {
        if(!table[0][i]) 
            continue;
        if(i && table[0][i] > 0) 
            formula << "+";
        formula << table[0][i];
        for(int j = 0; j < i; j++) {
            formula << "*(x";
            (x[j] >= 0) ? formula << "-" << x[j] : formula << "+" << -x[j];
            formula << ")";
        }
    }
    return formula.str();
}

double calculateDeterminant(const std::vector<std::vector<double>>& matrix, int size) {
    if (size == 1) {
        return matrix[0][0];
    } else if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    } else {
        double determinant = 0.0;
        for (int col = 0; col < size; col++) {
            std::vector<std::vector<double>> subMatrix(size - 1, std::vector<double>(size - 1));
            for (int i = 1; i < size; i++) {
                int subCol = 0;
                for (int j = 0; j < size; j++) {
                    if (j != col) {
                        subMatrix[i - 1][subCol++] = matrix[i][j];
                    }
                }
            }
            determinant += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * calculateDeterminant(subMatrix, size-1);
        }
        return determinant;
    }
}