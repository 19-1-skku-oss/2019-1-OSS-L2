#include <iostream>
#include <queue>
using namespace std;

struct Position
{
	int x, y;
};

int main() {
	int M, N; //M: horizontal N:vertical

    cin >> M >> N;

		int **box = new int *[N];	
		for (int i = 0; i < N; i++)
		{
			box[i] = new int[M];
			for (int j = 0; j < M; j++)
				cin >> box[i][j];
		}

		int move_x[4] = { 0, -1, 1, 1 };	//the movement
		int move_y[4] = { 1, -1, -1, 1 };

		queue<Position> q, Istomato;
		Position tmp;

		int Day = 0;
		for (int i = 0; i < N; i++)	//Day0 1 insert to queue
		{
			for (int j = 0; j < M; j++)
			{
				if (box[i][j] == 1)
				{
					tmp.x = i;
					tmp.y = j;
					q.push(tmp);
				}
			}
		}

		while (!q.empty())
		{
			int t = q.size();	//t=1
			while (t > 0)
			{
				tmp = q.front(); q.pop();
				for (int i = 0; i < 4; i++)
				{
					tmp.x += move_x[i];	
					tmp.y += move_y[i];
					if (tmp.x >= 0 && tmp.x < N && tmp.y >= 0 && tmp.y < M && box[tmp.x][tmp.y] == 0)
					{
						box[tmp.x][tmp.y] = 1;
						q.push(tmp);
					}

				}
				t--;
			}
			Day++;
			

		}

		for (int i = 0; i < N; i++)	//check the tomato if it ripe
		{
			for (int j = 0; j < M; j++)
			{
				if (box[i][j] == 0)
				{
					tmp.x = i;
					tmp.y = j;
					Istomato.push(tmp);
				}
			}
		}

		if (!Istomato.empty())	//if there is the 0 in the box
			cout << "-1" << endl; 
		else
			cout << Day - 1 << endl;

    return 0;
}
