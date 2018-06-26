//VISHAL ANAND
//B16040

#include <iostream>
#include "UndirectedGraph.hpp"

using namespace std;
int l,b,ans = 0;

bool isValid(int i, int j){
	return (i>=1 && i<=l && j>=1 && j<=b);
}

void work(int& i){
	cout<<i<<" ";
}

int main(){
	char mode,inp, vert = 0;
	cin>>l>>b>>mode;
	int bin[l+1][b+1];
	for(int i=1; i<=l; i++){
		for(int j=1; j<=b; j++){
			cin>>inp;
			if(inp=='b')	bin[i][j] = ++vert;
			else	bin[i][j] = 0;
		}
	}
	int visited[vert+1];
	for(int i=0; i<=vert; i++)	visited[i] = 0;
	UndirectedGraph graph(vert,mode);
	for(int i=1; i<=l; i++){
		for(int j=1; j<=b; j++){
			if(bin[i][j]!=0){
				if(isValid(i-1,j))	graph.add(bin[i][j],bin[i-1][j]);
				if(isValid(i,j+1))	graph.add(bin[i][j],bin[i][j+1]);
				if(isValid(i+1,j))	graph.add(bin[i][j],bin[i+1][j]);
				if(isValid(i,j-1))	graph.add(bin[i][j],bin[i][j-1]);
			}
		}
	}
	for(int i=1; i<=vert; i++)
		if(!visited[i]){
			graph.dfs(work,i,visited);
			ans++;
		}
	cout<<"\nans = "<<ans<<endl;

	return 0;
}