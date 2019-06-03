#include <iostream>
using namespace std;
long int labs(long int input)
{
	if (input >= 0)
		return input;
	else
		return -input;
}

int main()
{
	long int input;
	cin >> input;
	cout << labs(input) << endl;

	return 0;
}
