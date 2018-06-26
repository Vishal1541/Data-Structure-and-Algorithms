#include <iostream>
#include "ChainedMap.hpp"
#include "DoubleHashMap.hpp"
#include "OpenMap.hpp"

using namespace std;

int main(){
	cs202::OpenMap<int,int> c(100);
	c.put(2,10);
	c[2] = 5;
	c[5] = 11;
	c.remove(5);
	cout<<c[5]<<endl;
	cout<<c.getSize()<<endl;
	// cs202::OpenMap<int,int> d(c);

	// cout<<d.get(2)<<endl;
	// cout<<d.getSize()<<endl;

	// cs202::DoubleHashMap<string,string> o;
	// o.put("AS","sad");
	// o["AS"] = "asss";
	// o["GFG"] = "2";
	// o.remove("AS");
	// cout<<o["AS"]<<endl;
	// cout<<o.getSize()<<endl;
	// cs202::DoubleHashMap<string,string> p(o);
	// // // p.put(2,10);
	// // // p[2] = 5;
	// // // p[5] = 11;
	// // // p.remove(5);
	// cout<<p["GFG"]<<endl;
	// cout<<p.getSize()<<endl;

	return 0;
}