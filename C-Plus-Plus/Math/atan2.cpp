/* atan2 func */

#include <iostream>
#include <cmath>

#define PI 3.14159265
using namespace std;

int main(int argc, char** argv){
	double a, b,result;
	a = -10.0; b = 10.0;
	result = atan2 (b,a)*180.0 / PI;
	cout<<"The arc tangent for a="<<a<<" b="<<b<<" is "<<result<<" degrees.\n"<<endl;
	return 0;	
}
