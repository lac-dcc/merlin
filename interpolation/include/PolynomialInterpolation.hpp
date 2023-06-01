#include <string>
#include <vector>


//Calculates an interpolation for single-variable functions.
std::string NewtonInterpolation(std::vector<double>& x, std::vector<std::vector<double>>& table, int n);


double calculateDeterminant(const std::vector<std::vector<double>>& matrix, int);