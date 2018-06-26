#include <bits/stdc++.h>
#include "List.hpp"

// using namespace std;

int main(){
	list<int> l;
	std::cout<<l.length()<<l.empty()<<std::endl;
	int val=12;
	l.append(val);
	val=34;
	l.append(val);
	val=11;
	l.append(val);
	std::cout<<l.length()<<l.empty()<<std::endl;
	val=45;
	l.cons(val);
	std::cout<<l.length()<<l.empty()<<std::endl;
	l.remove(val);
	std::cout<<l.length()<<l.empty()<<std::endl;
	val=11;
	l.remove(val);
	std::cout<<l.length()<<l.empty()<<l.get_head()<<std::endl;
	list<int> l2(l);
	std::cout<<l2.length()<<l2.empty()<<l2.get_head()<<std::endl;

	return 0;
}