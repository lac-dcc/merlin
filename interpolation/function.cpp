#include <iostream>
#include <random>
using namespace std;


int main() {
	int x, y, z;
	int N;
	cin >> N;
	for(int i = 0; i < N; i++) {
		// x = rand() % 1000;
		// y = rand() % 1000;
		// z = rand() % 1000;
		cin >> x >> y >> z;
		cout << "F("<< x <<  ", "<< y << ", "<< z << ") = " <<  x*y + 2*x*z - 7*z*y << endl;
	}
  return 0;
}