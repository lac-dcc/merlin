#include <iostream>
#include <random>
using namespace std;


int main() {
	double x, y, z;
	double N;
	cin >> N;
	cout << 2 << endl;
	cout << N << endl;
	for(int i = 0; i < N; i++) {
		x = rand() % 100;
		y = rand() % 100;
		cout << x << " " << y << " "<< y*y << endl;
		// z = rand() % 1000;
		// cin >> x >> y >> z;
		// cout << "F("<< x <<  ", "<< y << ", "<< z << ") = " <<  x*y + 2*x*z - 7*z*y << endl;
	}
  return 0;
}