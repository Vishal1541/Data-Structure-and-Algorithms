//VISHAL ANAND
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string X,Y,X_="",Y_="";
int m,n,delta = 2;
int alpha[100][100];


int Alignment(vector<vector<int> > &A){
	for(int i=0; i<=m; i++)	A[i][0] = i*delta;
	for(int i=0; i<=n; i++)	A[0][i] = i*delta;
	for(int j=1; j<=n; j++)
		for(int i=1; i<=m; i++)
			A[i][j] = min(alpha[X[i-1]][Y[j-1]]+A[i-1][j-1],
							min(delta+A[i-1][j],
							delta+A[i][j-1]));
	return A[m][n];
}

void Backtrack(vector<vector<int> > &A, int i, int j){
	if(i==0 && j==0)	return;
	bool inside = false;
	if(i>0 && j>0)
		if(A[i][j]==A[i-1][j-1]+alpha[X[i-1]][Y[j-1]]){
			inside = true;
			X_ = X[i-1]+X_;
			Y_ = Y[j-1]+Y_;
			Backtrack(A,i-1,j-1);
		}
	if(j>0 && !inside)
		if(A[i][j]==delta+A[i][j-1]){
			inside = true;
			X_ = "_"+X_;
			Y_ = Y[j-1]+Y_;
			Backtrack(A,i,j-1);
		}
	if(i>0 && !inside){
		X_ = X[i-1]+X_;
		Y_ = "_"+Y_;
		Backtrack(A,i-1,j);		
	}
}

char Mod(int a){
	return (a>0?a:-a);
}

int main(){
	cin>>X>>Y;
	m = X.length();
	n = Y.length();
	vector<vector<int> > arr(m+1,vector<int>(n+1));
	for(char a='A'; a<='Z'; a++){
		for(char b='A'; b<='Z'; b++){
			alpha[a][b] = Mod(a-b);
		}
	}
	int minCost = Alignment(arr);
	Backtrack(arr,m,n);
	cout<<minCost<<endl;
	cout<<X_<<endl<<Y_<<endl;

	return 0;
}