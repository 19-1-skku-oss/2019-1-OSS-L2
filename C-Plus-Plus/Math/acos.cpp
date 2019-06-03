/* acos func*/

#include <iostream>
#include <cmath>

#define PI 3.14159265
using namespace std;

int main(int argc, char** argv){
	double param, result;
	param = 0.5;
	result = acos (param)*180.0/PI;
	cout<<"The arc cosine of "<<param<<" is "<< result<<" degrees.\n"<<endl;
	return 0;	
}
