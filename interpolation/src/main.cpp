#include "interpolator.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  int numInterp, numPoints;
  cin >> numInterp;
  cin >> numPoints;
  cin.ignore();
  vector<vector<string>> interpVars(numInterp);
  vector<vector<double>> xValues(numInterp); // X variables
  vector<vector<double>> yValues(numInterp); // Y variable
  vector<vector<double>> fValues(numInterp); // F(x)/F(x,y)

  for (int i = 0; i < numInterp; i++) {
    string varNames;
    getline(cin, varNames);
    varNames = varNames.substr(varNames.find(':') + 1, varNames.length());

    if (varNames.size() <= 0)
      continue;

    stringstream varStream(varNames);
    string name;
    while (varStream >> name) {
      interpVars[i].push_back(name);
    }
  }

  for (int i = 0; i < numPoints; i++) {
    for (int j = 0; j < numInterp; j++) {
      double xi, yi, zi;
      switch (interpVars[j].size()) {
      case 1:
        cin >> xi >> zi;
        xValues[j].push_back(xi);
        fValues[j].push_back(zi);
        break;
      case 2:
        cin >> xi >> yi >> zi;
        xValues[j].push_back(xi);
        yValues[j].push_back(yi);
        fValues[j].push_back(zi);
        break;
      default:
        break;
      }
    }
  }

  for (int i = 0; i < numInterp; i++) {
    int numVars = interpVars[i].size();
    if (numVars == 1) {
      Interpolator interp(xValues[i], fValues[i]);
      cout << "x: " << interpVars[i][0] << endl;
      cout << interp.interpolate() << endl << endl;
    } else if (numVars == 2) {
      Interpolator interp(xValues[i], yValues[i], fValues[i]);
      cout << "x: " << interpVars[i][0] << endl;
      cout << "y: " << interpVars[i][1] << endl;
      cout << interp.interpolate() << endl << endl;
    }
  }

  return 0;
}
