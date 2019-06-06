#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MST
{
private:
	vector<pair<int, pair<int, int>>> info;
	int Vnum=0;
	int Enum =0;
	int * parent_info;
	int * height_info;
	int total_weight=0;
public:
	MST(const char * fname)
	{
		//cout << Vnum << endl;
		int a, b, c;
		FILE * fp = fopen(fname, "r");
		fscanf(fp, "%d %d", &a, &b);		//weight , arg1, arg2
		Vnum = a;
		parent_info = new int[sizeof(int)*(Vnum+1)];
		height_info = new int[sizeof(int)*(Vnum+1)];
		for (int i = 1; i < Vnum+1; i++)
		{
			parent_info[i] = i;
			height_info[i] = 0;
		}
		while(!feof(fp))
		{
			fscanf(fp, "%d %d %d", &a, &b, &c);
			info.push_back(make_pair(c, make_pair(a, b)));
		}
		fclose(fp);
		sort(info.begin(), info.end());
		//cout << info[0].first << " " << info[0].second.first << " " << info[0].second.second << endl;
		//cout << info[1].first << " " << info[1].second.first << " " << info[1].second.second << endl;
		//cout << info[2].first << " " << info[2].second.first << " " << info[2].second.second << endl;
	}
	void union_set(pair<int, pair<int,int>> arg)
	{

		int root1 = find_set(arg.second.first);
		int root2 = find_set(arg.second.second);
		if (root1 == root2)
		{
			//cout << "Y they are in the same set" << endl;
			return;
		}
		else
		{
			//cout << "N they are in different set" << endl;
			int h1 = height_info[root1];
			int h2 = height_info[root2];
			if (h1 > h2)		//arg2�� 1�� �ռ�
			{
				parent_info[root2] = root1;
			}
			else if (h1 < h2)	//arg1�� 2�� �ռ�
			{
				parent_info[root1] = root2;
			}
			else				//arg2�� 1�� �ռ��ϰ� h++
			{
				parent_info[root2] = root1;
				height_info[root1] += 1;
			}
			total_weight += arg.first;
		}
	}
	int find_set(int arg)
	{
		int child = arg;
		int parent;
		while (1)
		{
			parent = parent_info[child];
			if (parent == child)		//root node
				break;
			child = parent;
		}
		return parent;
	}
	void Kruskal()
	{
		for(int i=0;i<info.size();i++)
		{
			union_set(info[i]);
			if (Enum == Vnum - 1)
				break;
		}
	}
	void write(const char * fname)
	{
		FILE * fp = fopen(fname, "w");
		fprintf(fp, "%d",total_weight);
		fclose(fp);
		//cout << total_weight << endl;
	}
};

int main(int argc, char ** argv)
{
	MST A(argv[1]);		//argv[1]
	A.Kruskal();
	A.write(argv[2]);	//argv[2]
	return 0;
}