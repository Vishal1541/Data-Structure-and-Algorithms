//VISHAL ANAND
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

string X,Y,Xf="",Yf="";
int m,n,delta = 2, alpha[100][100];
vector<vector<int> > arr(1000000,vector<int>(2));
set<pair<int,int> > xy_store;
set<pair<int,int> > :: iterator itr;
char dna[4] = {'A','T','C','G'};

struct node{
	int i,j;
};

node g[1000000], ans[1000000];
int A[1000000][2], B[1000000][2], minCost = 0;
int edges = 0;

void Space_Efficient_Alignment(int xi, int xj, int yi, int yj){
	for(int i=0; i<=xj-xi+1; i++)	A[i][0] = i*delta;
	for(int j=1; j<=yj-yi+1; j++){
		A[0][1] = j*delta;
		for(int i=1; i<=xj-xi+1; i++){
			A[i][1] = min(alpha[X[i-1+(xi-1)]][Y[j-1+(yi-1)]]+A[i-1][0],
							min(delta+A[i-1][1],
							delta+A[i][0]));
		}
		for(int i=0; i<=xj-xi+1; i++)	A[i][0] = A[i][1];
	}
}

void Backward_Space_Efficient_Alignment(int xi, int xj, int yi, int yj){
	for(int i=xj-xi+1; i>=0; i--)	B[i][1] = (xj-xi+1-i)*delta;
	for(int j=yj-yi; j>=0; j--){
		B[xj-xi+1][0] = (yj-yi+1-j)*delta;
		for(int i=xj-xi; i>=0; i--){
			B[i][0] = min(alpha[X[i+(xi-1)]][Y[j+(yi-1)]]+B[i+1][1],
							min(delta+B[i+1][0],
							delta+B[i][1]));
		}
		for(int i=0; i<=xj-xi+1; i++)	B[i][1] = B[i][0];
	}
}

void Backtrack(int xi, int xj, int yi, int yj){
	int i = xj-xi+1;
	int j = yj-yi+1;
	if(i==0 && j==0)	return;
	bool inside = false;
	if(i>=1 && j>=1)
		if(A[i][j]==A[i-1][j-1]+alpha[X[i-1+xi-1]][Y[j-1+yi-1]]){
			// if(xi==1 && xj==2 && yi==1 && yj==2){
			// 	cout<<"yes";
			// 	cout<<xj-1<<yj-1<<"/";
			// }
			inside = true;
			g[edges].i = i+xi-1;
			g[edges++].j = j+yi-1;
			Backtrack(xi,xj-1,yi,yj-1);
		}
	if(j>=1 && !inside)
		if(A[i][j]==delta+A[i][j-1]){
			inside = true;
			g[edges].i = i+xi-1;
			g[edges++].j = j+yi-1;
			Backtrack(xi,xj,yi,yj-1);
		}
	if(i>=1 && !inside){
		if(A[i][j]==delta+A[i-1][j]){
			g[edges].i = i+xi-1;
			g[edges++].j = j+yi-1;
			Backtrack(xi,xj-1,yi,yj);
		}	
	}
}

void Alignment(int xi, int xj, int yi, int yj){
	for(int i=0; i<=xj-xi+1; i++)	A[i][0] = i*delta;
	for(int j=0; j<=yj-yi+1; j++)	A[0][j] = j*delta;
	for(int j=1; j<=yj-yi+1; j++)
		for(int i=1; i<=xj-xi+1; i++){
			A[i][j] = min(alpha[X[i-1+(xi-1)]][Y[j-1+yi-1]]+A[i-1][j-1],
							min(delta+A[i-1][j],
							delta+A[i][j-1]));
			// if(xi==1 && xj==2 && yi==1 && yj==2)
			// cout<<A[i][j]<<"__";
		}
	Backtrack(xi,xj,yi,yj);
	g[edges].i = xi;
	g[edges++].j = yi;
	g[edges].i = xj;
	g[edges++].j = yj;
}

void Divide_And_Conquer_Alignment(int xi, int xj, int yi, int yj){
	int m = xj-xi+1;
	int n = yj-yi+1;
	if(m<=2 || n<=2){
		Alignment(xi,xj,yi,yj);
		return;
	}
	Space_Efficient_Alignment(xi,xj,yi,(yi+yj)/2);
	Backward_Space_Efficient_Alignment(xi,xj,(yi+yj)/2+1,yj);
	int q=A[0][0]+B[0][0];
	int idx = xi-1;
	for(int i=0; i<=xj-xi+1; i++){
		if(A[i][1]+B[i][1]<q){
			q = A[i][1]+B[i][1];
			idx = i+xi-1; 
		}
	}
	g[edges].i = idx;
	g[edges++].j = (yi+yj)/2;
	// cout<<idx<<","<<g[edges-1].j<<"...";
	// g[edges++].c = q;
	Divide_And_Conquer_Alignment(xi,g[edges-1].i,yi,(yi+yj)/2);
	Divide_And_Conquer_Alignment(g[edges-1].i+1,xj,(yi+yj)/2+1,yj);
}

char Mod(int a){
	return (a>0?a:-a);
}

int main(){
	cin>>X>>Y;
	m = X.length();
	n = Y.length();
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
	Divide_And_Conquer_Alignment(1,m,1,n);
	xy_store.insert(make_pair(0,0));
	for(int i=0; i<edges; i++){
		xy_store.insert(make_pair(g[i].i,g[i].j));
	}
	edges = 0;
	for(itr = xy_store.begin(); itr!=xy_store.end(); itr++){
		ans[edges].i = itr->first;
		ans[edges++].j = itr->second;
	}
	for(int i=0; i<edges; i++)
		cout<<ans[i].i<<","<<ans[i].j<<"  ";
	for(int i=edges-1; i>0; i--){
		if(ans[i].i==ans[i-1].i+1 && ans[i].j==ans[i-1].j+1){
			Xf = X[ans[i].i-1]+Xf;
			Yf = Y[ans[i].j-1]+Yf;
			minCost += alpha[X[ans[i].i-1]][Y[ans[i].j-1]];
		}
		else if(ans[i].i==ans[i-1].i && ans[i].j==ans[i-1].j+1){
			Xf = "_"+Xf;
			Yf = Y[ans[i].j-1]+Yf;
			minCost += delta;
		}
		else{
			Xf = X[ans[i].i-1]+Xf;
			Yf = "_"+Yf;
			minCost += delta;
		}
	}
	cout<<endl<<Xf<<endl<<Yf<<endl<<minCost<<endl;
	#ifndef LOCAL_DEFINE
		cerr<<"\nTime elapsed: "<<1.0*clock()/CLOCKS_PER_SEC<<"s.\n";
	#endif
	return 0;
}