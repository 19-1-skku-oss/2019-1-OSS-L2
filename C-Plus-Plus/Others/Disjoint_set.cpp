#include <iostream>
using namespace std;
int Find_Set(int *parent,int x);
void Union_set(int *parent, int x, int y);
int main()
{
	int n, m;
	cin >> n >> m; // m = number of operations , n = number of sets
	int *parent = new int[n + 1];
	for (int i = 0; i <= n; i++)
		parent[i] = i;
	for (int i = 0; i < m; i++) 
	{
		int input, a, b;
		cin >> input >> a >> b;
		if (input == 1) // input==1 ==> Find_set
		{
			if (Find_Set(parent,b) == Find_Set(parent,a))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;

		}
		else // input==0 ==> Union_set
		{
			Union_set(parent,a, b);

		}


	}
	delete[]parent;
	return 0;
}
int Find_Set(int *parent,int x)
{
	while (parent[x] != x)
	{
		x = parent[x];
	}
	return x;
}
void Union_set(int *parent, int x, int y)
{
	x = Find_Set(parent,x);
	y = Find_Set(parent,y);
	if (x != y)
	{
		parent[y] = x;
	}
}

