#include "PolynomialInterpolation.hpp"
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
using namespace std;
#define MAX_COLUMN 15
#define ZERO 1e-9

/*
Function to calculate divided differences.
x: vector of x values
table: Table used to store the divided differences, table[*][0] must be
initialized with the y values n: number of pairs (x, y)
*/

void DividedDifferenceTable(std::vector<double>& x, std::vector<std::vector<double>>& table, int n) {
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < n - j; i++) {
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
    }
  }
}

string NewtonInterpolation() {
  double xi, yi;
  int N;
  vector<vector<double>> table(MAX_COLUMN, vector<double>(MAX_COLUMN));
  vector<double> X(MAX_COLUMN);

  std::cin >> N;

  for (int i = 0; i < N; i++) {
    std::cin >> xi >> yi;
    X[i] = xi;
    table[i][0] = yi;
  }

  stringstream formula;
  DividedDifferenceTable(X, table, N);
  for (int i = 0; i < N; i++) {
    if (!table[0][i])
      continue;
    if (i && table[0][i] > 0)
      formula << "+";
    formula << table[0][i];

    for (int j = 0; j < i; j++) {
      formula << "*(x";
      (X[j] >= 0) ? formula << "-" << X[j] : formula << "+" << -X[j];
      formula << ")";
    }
  }

  fstream temp;
  stringstream result;
  std::string command = "python3 reduce.py \"" + formula.str() + "\" > temp.txt";

  system(command.c_str());
  temp.open("temp.txt");
  result << temp.rdbuf();
  system("rm temp.txt");
  return result.str();
}

std::string solve_2var() {
  long double xi, yi, zi;
  int N;
  std::cin >> N;

  Eigen::MatrixXd A(N, MAX_COLUMN);
  Eigen::VectorXd b(N);
  Eigen::VectorXd answer;

  for (int i = 0; i < N; i++) {
    cin >> xi >> yi >> zi;
    b(i) = zi;

    A(i, 0) = 1;

    A(i, 1) = xi;
    A(i, 2) = yi;
  }
  double error = INT_MAX;
  std::list<int> monomials;

  std::queue<std::list<int>> work_queue;
  work_queue.emplace();

  while (error > ZERO && work_queue.size() != 0) {
    Eigen::MatrixXd sub_matrix = Eigen::MatrixXd::Zero(N, MAX_COLUMN);
    sub_matrix.col(0) = A.col(0);

    std::list<int> cols = work_queue.front();
    work_queue.pop();

    int i = 1;
    for (auto col : cols) {
      sub_matrix.col(i) = sub_matrix.col(i - 1).array() * A.col(col).array();
      i++;
    }

    sub_matrix = sub_matrix.leftCols(cols.size() + 1);
    cout << sub_matrix << endl << endl;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(sub_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    answer = svd.solve(b);
    error = (b - sub_matrix * answer).norm() / b.norm();

    if (error > ZERO && cols.size() < MAX_COLUMN) {
      cols.push_back(1);
      work_queue.push(cols);
      cols.pop_back();
      cols.push_back(2);
      work_queue.push(cols);
    } else if (error <= ZERO) {
      monomials = cols;
    }
  }

  cout << "Error: " << error << endl;
  if (error > ZERO) {
    return "Couldn't find a good solution!\n";
  }

  std::list<std::string> monomials_str;
  std::string accul = "";
  for (int num : monomials) {
    if (num == 1) {
      accul += "x";
    } else if (num == 2) {
      accul += "y";
    }
    monomials_str.push_back(accul);
  }

  // Representing the function
  stringstream result;
  monomials_str.push_front("1");
  result << "F(x, y) = ";
  for (int i = 0; i < answer.size(); i++) {
    string term = monomials_str.front();
    monomials_str.pop_front();
    if (abs(answer(i)) <= ZERO)
      continue;
    result << answer(i) << "*" << term << " + ";
  }

  string interpolated_function = result.str();
  interpolated_function.pop_back();
  interpolated_function.pop_back();
  return interpolated_function;
}
