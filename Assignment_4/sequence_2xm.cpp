//VISHAL ANAND
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string X,Y;
int m,n,delta = 2, alpha[100][100];
char dna[4] = {'A','T','C','G'};

int Space_Efficient_Alignment(vector<vector<int> > &A){
	for(int i=0; i<=m; i++)	A[i][0] = i*delta;
	for(int j=1; j<=n; j++){
		A[0][1] = j*delta;
		for(int i=1; i<=m; i++){
			A[i][1] = min(alpha[X[i-1]][Y[j-1]]+A[i-1][0],
							min(delta+A[i-1][1],
							delta+A[i][0]));
		}
		for(int i=0; i<=m; i++)	A[i][0] = A[i][1];
	}
	return A[m][1];
		return 0;
}

char Mod(int a){
	return (a>0?a:-a);
}

int main(){
	cin>>X>>Y;
	m = X.length();
	n = Y.length();
	vector<vector<int> > arr(m+1,vector<int>(2));
	// for(char a='A'; a<='Z'; a++){
	// 	for(char b='A'; b<='Z'; b++){
	// 		alpha[a][b] = Mod(a-b);
	// 	}
	// }
	for(int i=0; i<dna[i]; i++){
		for(int j=0; j<dna[j]; j++){
			if(dna[i]==dna[j])	alpha[dna[i]][dna[j]] = 0;
			if( (dna[i]=='A' && dna[j]=='T') || (dna[j]=='A' && dna[i]=='T')
				|| (dna[i]=='G' && dna[j]=='C') || (dna[j]=='C' && dna[i]=='G') )
				alpha[dna[i]][dna[j]] = 1;
			else if((dna[i]=='A' && dna[j]=='A') || (dna[j]=='T' && dna[i]=='T')
				|| (dna[i]=='C' && dna[j]=='C') || (dna[j]=='G' && dna[i]=='G'))
				alpha[dna[i]][dna[j]] = 0;
			else
				alpha[dna[i]][dna[j]] = 2;
		}
	}
	int minCost = Space_Efficient_Alignment(arr);
	cout<<minCost<<endl;

	return 0;
}