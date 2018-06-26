#include <iostream>
#include "LRU.hpp"

using namespace std;

int main(){
	LRUCache<int,int> cache(2);
		cache.put(1,10);
		cache.put(5,12);
	  cout << cache.get(5) << endl;
	  cout << cache.get(1) << endl;
	  cout << cache.get(10) << endl;
		cache.put(6,14);
	  cout << cache.get(5) << endl;


	return 0;
}