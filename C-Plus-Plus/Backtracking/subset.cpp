#include <iostream>
#include <vector>

using namespace std;

vector<int> find_match_case(int match,vector<int> arr){
	int nelement = 0;	//number of subset element
	//cout<<"i am here"<<endl;
	vector< <vector<int> > total_subset;
	for(int i=0; i < (1 << (arr.size())); i++){
		vector<int> subset;
		for(int j=0;j<arr.size();j++){
			if (i & (1<<j))
				subset.push_back(arr[j]);
		}
		int check=0;
		for(int k=0;k<arr.size();k++){
			check+=subset[k];
		}
		if(check==match)
			total_subset.push_back(subset);
	}
	return total_subset;
}
int main(int argc,char** argv){
	int N=5,S=0;
	vector<int> arr{-7,-3,-2,5,8};
	vector<int> result;
	result = find_match_case(0,arr);
	for(int i=0;i<result.size();i++){
		cout<<"num of"<< i<<" element case"<<endl;
		for (int j=0;j<result[i].size();j++){
			cout<<result[i][j]<<" ";
		cout<<endl;
		}
	}
}


