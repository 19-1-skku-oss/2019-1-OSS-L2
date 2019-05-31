/* cos func */
#include <iostream>
#include <cmath>

#define PI 3.14159265
using namespace std;

int main(int argc, char** argv){
	double param, result;
	param = 60.0;
	result = cos( (param)*PI/180.0);
	cout<<"The cosine of "<<param<<" is "<< result<<" degrees.\n"<<endl;
	return 0;	
}
