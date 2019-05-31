/* atan func */
#include <iostream>
#include <cmath>

#define PI 3.14159265
using namespace std;

int main(int argc, char** argv){
	double param, result;
	param = 1.0;
	result = atan (param)*180.0/PI;
	cout<<"The arc tangent of "<<param<<" is "<< result<<" degrees.\n"<<endl;
	return 0;	
}
