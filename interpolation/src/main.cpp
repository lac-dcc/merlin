#include <iostream>
#include "PolynomialInterpolation.hpp"

using namespace std;



// C*P
// pointsA[]
// pointsB[]

// points = vector<vector<int>>(counters);
// for( i : num_points) {
//     for (j : counters) {
//         points[j].push_back(i);
//     }
// }

int main() {
  int N, numVar;
  string result;

  std::cin >> numVar;

  switch(numVar) {
    case 0:
      result = "Complexity not influenced by a variable. O(1)";
      break;
    case 1:
      result = "F(x) = " + NewtonInterpolation();
      break;
    case 2:
      result = solve_2var();
      break;
    default:
      result = "Bad input or case not implemented.";
  }

  cout << result << '\n';

}
