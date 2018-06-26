#include <bits/stdc++.h>
#include "priority_queue.hpp"
#define ll long long int

ll N,M,in,popped,ans=0;
priority_queue<ll> p,q;

int main(){
	std::cin>>N>>M;
	for(int i=0; i<N; i++){
		std::cin>>in;
		p.push(in);
	}
	for(int i=0; i<M; i++){
		popped = p.top();
		ans += popped;
		// p.pop();
		// p.push(popped-1);
		p.decrease();
	}
	std::cout<<ans<<std::endl;
	// p.swap(q);


	return 0;
}