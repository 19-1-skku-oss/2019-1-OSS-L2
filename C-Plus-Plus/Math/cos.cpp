/* cos func */
#include <iostream>
using namespace std;

const double PI = 3.14159265

double cos(double x) {
	if (x < 0) x = -x;
	if (x > 360) x -= int(x / 360) * 360;
	x *= PI / 180.0;
	double res = 0;
	double term = 1;
	int k = 0;
	while (res + term != res) {
		res += term;
		k += 2;
		term *= -x * x / k / (k - 1);
	}
	return res;
}

int main() {
	double c = cos(1231);
	cout << "cos(1231) = " << c << endl;

	return 0;
}
