#include "BSTree.hpp"

int main()
{
	BSTree<int,int> b;
	b.put(2,10);
	b.put(1,20);
	b.put(3,5);
	b.put(4,5);
	b.put(8,5);

	// cout<<b.get(1);
	// cout<<b.minimum();
	// cout<<b.maximum();
	b.print_post_order();
	b.remove(8);
	cout<<b.maximum();
	// cout<<b.minimum();
	b.print_post_order();
	// cout<<b.minimum();
	cout<<b.has(2);
	return 0;
}