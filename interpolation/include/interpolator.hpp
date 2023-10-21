#include "eigen3/Eigen/Dense"
#include <list>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <vector>

class Interpolator {
public:
  enum class InterpolationType { OneVar, TwoVar };
  Interpolator(std::vector<double> x, std::vector<double> fx);                         // Single variable constructor
  Interpolator(std::vector<double> x, std::vector<double> y, std::vector<double> fxy); // Two variables constructor
  std::string interpolate();

private:
  InterpolationType interpType;
  std::vector<double> X;
  std::vector<double> Y;
  std::vector<double> F;
  std::string newtonDividedDifference();
  std::string leastSquares();
  int numSample;
};