#include "interpolator.hpp"
#define ZERO 1e-15
#define MAX_LEAST_SQR_ITERATIONS 30

Interpolator::Interpolator(std::vector<double> x, std::vector<double> fx) {
  this->interpType = InterpolationType::OneVar;
  this->X = x;
  this->F = fx;
  this->numSample = x.size();
}

Interpolator::Interpolator(std::vector<double> x, std::vector<double> y,
                           std::vector<double> fxy) {
  this->interpType = InterpolationType::TwoVar;
  this->X = x;
  this->Y = y;
  this->F = fxy;
  this->numSample = x.size();
}

std::string Interpolator::interpolate() {
  if (this->interpType == InterpolationType::OneVar)
    return this->newtonDividedDifference();
  else
    return this->linearLeastSquares();
}

std::string Interpolator::newtonDividedDifference() {
  std::vector<std::vector<double>> table(this->numSample,
                                         std::vector<double>(this->numSample));
  for (int i = 0; i < this->numSample; i++) {
    table[i][0] = this->F[i];
  }

	// Bulding divided difference table
  for (int j = 1; j < this->numSample; j++) {
    for (int i = 0; i < this->numSample - j; i++) {
      table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (this->X[i + j] - this->X[i]);
    }
  }

	if(table[this->numSample-1][this->numSample-1] != 0)
		return "Couldn't find a solution! Try again with more sample points.";

	std::stringstream formula;	
	for (int i = 0; i < this->numSample; i++) {
    if (!table[0][i])
      continue;

    if (i > 0) {
			(table[0][i] > 0) ? formula << " + " : formula << " - ";
		}
    formula << abs(table[0][i]);

    for (int j = 0; j < i; j++) {
      formula << "*(x";
      (X[j] >= 0) ? formula << "-" << X[j] : formula << "+" << -X[j];
      formula << ")";
    }
  }
	
	std::string command = "python3 reduce.py \"" + formula.str() + "\"";
	std::ostringstream result_stream;
	FILE* pipe = popen(command.c_str(), "r");
	if (!pipe) {
			throw std::runtime_error("Erro ao executar o comando Python");
	}

	char buffer[128];
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
			result_stream << buffer;
	}
	pclose(pipe);
  
  std::string result = result_stream.str();
  if (!result.empty() && result[result.length() - 1] == '\n') {
        result.erase(result.length() - 1);
  }
	return "F(x) = " +  result;
}

std::string Interpolator::linearLeastSquares() {
	Eigen::MatrixXd A(this->numSample, this->numSample);
  Eigen::VectorXd b(this->numSample);
  Eigen::VectorXd answer;

	for (int i = 0; i < this->numSample; i++) {
    A(i, 0) = 1;
    A(i, 1) = this->X[i];
    A(i, 2) = this->Y[i];
    b(i) = this->F[i];
  }

	  double error = INT_MAX;
  std::list<int> monomials;

  std::queue<std::list<int>> work_queue;
  work_queue.emplace();
	int iterationsCounter = MAX_LEAST_SQR_ITERATIONS;
	
  while (error > ZERO && work_queue.size() != 0 && iterationsCounter--) {
    std::list<int> cols = work_queue.front();
    work_queue.pop();
    Eigen::MatrixXd construction_matrix = Eigen::MatrixXd::Zero(this->numSample, cols.size() + 1);
    construction_matrix.col(0) = A.col(0);

    int i = 1;
    for (auto col : cols) {
      construction_matrix.col(i) = construction_matrix.col(i - 1).array() * A.col(col).array();
      i++;
    }

    Eigen::MatrixXd sub_matrix = construction_matrix.block(0, 0, construction_matrix.rows(), cols.size() + 1);
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(sub_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    answer = svd.solve(b);
    error = (b - (sub_matrix * answer)).norm() / b.norm();

    if (error > ZERO) {
      cols.push_back(1);
      work_queue.push(cols);
      cols.pop_back();
      cols.push_back(2);
      work_queue.push(cols);
    } else if (error <= ZERO) {
      monomials = cols;
    } 
  }

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
  std::stringstream result;
  monomials_str.push_front("1");
  result << "F(x, y) = ";
  for (int i = 0; i < answer.size(); i++) {
    std::string term = monomials_str.front();
    monomials_str.pop_front();
    if (abs(answer(i)) <= 1e-5)
      continue;
    result << answer(i) << "*" << term << " + ";
  }

  std::string interpolated_function = result.str();
  interpolated_function.pop_back();
  interpolated_function.pop_back();
  return interpolated_function;
}