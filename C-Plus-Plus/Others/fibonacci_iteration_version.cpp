#include <iostream>
#include<cstdio>
using namespace std;


int main()
{
	int fibo_size;
	cin >> fibo_size;
	long long int *fibo = new long long int[fibo_size + 1];
	fibo[0] = 0;
	fibo[1] = 1;
	cout << 1 << " th fibonacci number is " << fibo[1] << "\n";
	for (long long i = 2; i < fibo_size; i++)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 1];
		cout << i << " th fibonacci number is " << fibo[i] << "\n";
	}
	return 0;
}
