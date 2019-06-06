#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SMST
{
private:
	vector<pair<int, pair<int, int>>> Wkey_info;
	int ** Wdata;
	vector<int> Edge;
	vector <pair<int,pair<int, int>>> Edges;
	vector<pair<int, pair<int, int>>> waste;
	int Vnum=0;
	int Enum =0;
	int * parent_info;
	int * MST_parent_info;
	int * height_info;
	int total_weight=0;
	int TF=0;
	int mstW = 0;
public:
	SMST(const char * fname)
	{
		int a, b, c;
		FILE * fp = fopen(fname, "r");
		fscanf(fp, "%d %d", &a, &b);		//weight , arg1, arg2
		Vnum = a;
		parent_info = new int[sizeof(int)*(Vnum+1)];
		MST_parent_info = new int[sizeof(int)*(Vnum+1)];
		height_info = new int[sizeof(int)*(Vnum+1)];
		Wdata = new int *[sizeof(int*)*(Vnum+1)];
		for (int i = 0; i < Vnum+1; i++)
			Wdata[i] = new int[sizeof(int)*(Vnum+1)];
		for (int i = 1; i < Vnum+1; i++)
		{
			parent_info[i] = i;
			MST_parent_info[i] = i;
			height_info[i] = 0;
		}
		while(!feof(fp))
		{
			fscanf(fp, "%d %d %d", &a, &b, &c);
			Wkey_info.push_back(make_pair(c, make_pair(a, b)));
			Wdata[a][b] = c;
			Wdata[b][a] = c;
			
		}
		fclose(fp);
		sort(Wkey_info.begin(), Wkey_info.end());
		
	}
	void union_set(pair<int, pair<int,int>> arg)
	{
		
		int root1 = find_set(arg.second.first);		//first argv
		
		int root2 = find_set(arg.second.second);	//second argv
		if (root1 == root2)
		{
			waste.push_back(arg);
			return;
		}
		else
		{
			
			int h1 = height_info[root1];
			int h2 = height_info[root2];
			if (h1 > h2)		//merge arg2 to 1
			{
				parent_info[root2] = root1;
				
			}
			else if (h1 < h2)	//merge arg1 to 2
			{
				parent_info[root1] = root2;
			}
			else				//merge arg2 to 1 and height++
			{
				parent_info[root2] = root1;
				height_info[root1] += 1;
			}
			make_parent_child(arg.second.first, arg.second.second);
			
			total_weight += arg.first;
		}
	}
	void make_parent_child(int arg1, int arg2)
	{
		int p1 = MST_parent_info[arg1];
		int p2 = MST_parent_info[arg2];
		if (p1 == arg1 && p2==arg2)		//when both two does not have parent node
			MST_parent_info[arg2] = arg1;
		else if (p1 != arg1 && p2 == arg2)	//when arg1 has parent node
			MST_parent_info[arg2] = arg1;
		else if (p1 == arg1 && p2 != arg2)	//when arg2 has parent node
			MST_parent_info[arg1] = arg2;
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
		for(int i=0;i<Wkey_info.size();i++)
		{
			union_set(Wkey_info[i]);
			if (Enum == Vnum - 1)
				break;
		}
		mstW = total_weight;
	}
	void second_MST()
	{
		int arg1,arg2;
		int val;
		
		for (int i = 0; i < waste.size(); i++)
		{
			arg1 = waste[i].second.first;
			arg2 = waste[i].second.second;
			
			LCommonA(arg1, arg2);
			
			int max = *max_element(Edge.begin(), Edge.end());
			val = waste[i].first -  max;
			
			if (val>0)
				Edges.push_back(make_pair(val, make_pair(arg1, arg2)));
			Edge.clear();
		}
		sort(Edges.begin(), Edges.end());
		if (Edges.size() != 0)
			total_weight += Edges[0].first;

		//last 검증
		if (mstW < total_weight)
			TF = 1;
		else if (mstW >= total_weight)
			TF = 0;
		
	}
	
	void LCommonA(int arg1,int arg2)
	{
		
		int d1 = find_depth(arg1);
		int d2 = find_depth(arg2);
		int child,parent;
		int weight;
		if (d1 > d2)
		{
			int num = d1 - d2;
			child = arg1;
			for (int i = 0; i < num; i++)
			{
				parent = MST_parent_info[child];
				weight = Wdata[child][parent];
				
				Edge.push_back(weight);
				
				child = parent;
			}
			arg1 = child;
		}
		else if (d1 < d2)
		{
			int num = d2 - d1;
			child = arg2;
			for (int i = 0; i < num; i++)
			{
				parent = MST_parent_info[child];
				weight = Wdata[child][parent];
				Edge.push_back(weight);
				
				child = parent;
			}
			arg2 = child;
		}
		while (1)
		{
			
			if (arg1 == arg2)
				break;
			else
			{
				parent = MST_parent_info[arg1];
				weight = Wdata[arg1][parent];
				Edge.push_back(weight);
				
				arg1 = parent;
				parent = MST_parent_info[arg2];
				weight = Wdata[arg2][parent];
				Edge.push_back(weight);
				
				arg2 = parent;
			}
		}
		return;
	}
	int find_depth(int arg)
	{
		int child = arg;
		int parent;
		int depth=0;
		while (1)
		{
			parent = MST_parent_info[child];
			if (parent == child)		//root node
				break;
			child = parent;
			depth++;
		}
		return depth;
	}
	void write(const char * fname)
	{
		
		FILE * fp = fopen(fname, "w");
		if (TF==1)
			fprintf(fp, "%d",total_weight);
		else if(TF==0)
			fprintf(fp, "%d", -1);
		fclose(fp);
		
	}
};

int main(int argc, char ** argv)
{
	SMST A(argv[1]);		//argv[1]
	A.Kruskal();
	A.second_MST();
	A.write(argv[2]);	//argv[2]
	return 0;
}
