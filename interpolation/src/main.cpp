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
  vector<int> nestingDepth;
  vector<string> originLines(numInterp);
  vector<vector<double>> xValues(numInterp); // X variables
  vector<vector<double>> yValues(numInterp); // Y variable
  vector<vector<double>> zValues(numInterp); // Z variable
  vector<vector<double>> fValues(numInterp); // F(x)/F(x,y)/F(x,y,z)

  for (int i = 0; i < numInterp; i++) {
    string varNames;
    string expectedDepth;
    getline(cin, varNames);
    getline(cin, expectedDepth);
    originLines[i] = varNames;
    varNames = varNames.substr(varNames.find(':') + 1, varNames.length());
    expectedDepth = expectedDepth.substr(expectedDepth.find(':') + 1, expectedDepth.length());
    nestingDepth.push_back(stoi(expectedDepth));
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
      double xi, yi, zi, fi, trash;
      switch (interpVars[j].size()) {
      case 0:
        cin >> fi;
        fValues[j].push_back(fi);
        break;
      case 1:
        cin >> xi >> fi;
        xValues[j].push_back(xi);
        fValues[j].push_back(fi);
        break;
      case 2:
        cin >> xi >> yi >> fi;
        xValues[j].push_back(xi);
        yValues[j].push_back(yi);
        fValues[j].push_back(fi);
        break;
      case 3:
        cin >> xi >> yi >> zi >> fi;
        xValues[j].push_back(xi);
        yValues[j].push_back(yi);
        zValues[j].push_back(zi);
        fValues[j].push_back(fi);
        break;
      default:
        for(int i = 0; i < interpVars[j].size() + 1; i++) {
          cin >> trash;
        }
        break;
      }
    }
  }
  for (int i = 0; i < numInterp; i++) {
    int numVars = interpVars[i].size();
    if (numPoints <= numVars) {
      cout << "The number of input points must be greater than the number of variables.\n";
      return 0;
    }
    if (numVars == 0) {
      cout << originLines[i] << endl;
      cout << "Expected Nesting Depth: " << nestingDepth[i] << endl;
      cout << "This path runs in constant time. Constant Factor: " << fValues[i][0] << endl;
    } else if (numVars == 1) {
      Interpolator interp(xValues[i], fValues[i]);
      cout << originLines[i] << endl;
      cout << "x: " << interpVars[i][0] << endl;
      cout << "Expected Nesting Depth: " << nestingDepth[i] << endl;
      cout << interp.interpolate() << endl << endl;
    } else if (numVars == 2) {
      Interpolator interp(xValues[i], yValues[i], fValues[i]);
      cout << originLines[i] << endl;
      cout << "x: " << interpVars[i][0] << endl;
      cout << "y: " << interpVars[i][1] << endl;
      cout << "Expected Nesting Depth: " << nestingDepth[i] << endl;
      cout << interp.interpolate() << endl << endl;
    } else if (numVars == 3) {
      Interpolator interp(xValues[i], yValues[i], zValues[i], fValues[i]);
      cout << originLines[i] << endl;
      cout << "x: " << interpVars[i][0] << endl;
      cout << "y: " << interpVars[i][1] << endl;
      cout << "z: " << interpVars[i][2] << endl;
      cout << "Expected Nesting Depth: " << nestingDepth[i] << endl;
      cout << interp.interpolate() << endl << endl;
    } else {
      cout << originLines[i] << endl;
      cout << "At line This tool works with at most 3 variables.\n\n";
    }
  }

  return 0;
}
