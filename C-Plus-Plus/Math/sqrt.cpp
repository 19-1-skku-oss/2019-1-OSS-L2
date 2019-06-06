//Used The Babylonian Method Algorithm
#include <iostream>
using namespace std;

double SQRT(double, double);


double SQRT(double input, double x)
{
	for (int i = 0; i < 10; i++) { x = (x + (input / x)) / 2; }    // 이 한줄 땜에 주말내내 머리에 쥐남 ㅠㅠ

	return x;
}

void main()
{
	double input, x, result;

	cout << "Enter the count of sqrt: ";
	cin >> x;
	cout << "Enter the Value: ";
	cin >> input;
	result = SQRT(input, x);
	cout << "The result: " << result << endl;

}

