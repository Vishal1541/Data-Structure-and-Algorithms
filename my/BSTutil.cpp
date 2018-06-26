#include "BSTree.hpp"
#include <iostream>
using namespace std;
//using namespace cs202;

int main()
{
	int c;
	BSTree<int,int> b;
	int k;
	int v;
	cout<<"0.Exit"<<endl<<"1.Insert node"<<endl<<"2.Remove node"<<endl<<"3.Search key"<<endl<<"4.Print pre-order";
	cout<<endl<<"5.Print post-order"<<endl<<"6.Print in in-order"<<endl<<"7.Minimum key"<<endl<<"8.Maximum Key"<<endl;
	cout<<"9.Successor"<<endl<<"10.Predecessor"<<"11.Height"<<endl;
		
	while(true)
	{	
		cout<<endl<<"Enter your choice : ";
		cin>>c;
		switch(c)
		{
			case 1:
				cout<<"Enter Key"<<endl;
				cin>>k;
				cout<<"Enter Value"<<endl;
				cin>>v;
				b.put(k,v);
				break;

			case 2:
				cout<<"Enter the key to be removed"<<endl;
				cin>>k;
				if(b.has(k))
				{
					b.remove(k);
				}

				else
					cout<<"Key not present"<<endl;
				break;

			case 3:
				cout<<"Enter the key to be searched"<<endl;
				cin>>k;
				if(b.has(k))
				{
					cout<<b.get(k)<<endl;
				}

				else
					cout<<"Key not present"<<endl;
				break;


			case 4:
				b.print_pre_order();
				cout<<endl;
				break;

			case 5:
				b.print_post_order();
				cout<<endl;
				break;

			case 6:
				b.print_in_order();
				cout<<endl;
				break;

			case 7:
				cout<<b.minimum()<<endl;
				break;

			case 8:
				cout<<b.maximum()<<endl;
				break;

			case 9:
				cout<<"Enter the key"<<endl;
				cin>>k;
				if(b.successor(k) != 9999+k)
					cout<<b.successor(k)<<endl;
				else
					cout<<"No successor"<<endl;
				break;

			case 10:
				cout<<"Enter the key"<<endl;
				cin>>k;
				if(b.predecessor(k) != k-9999)
					cout<<b.predecessor(k)<<endl;
				else
					cout<<"No predecessor"<<endl;
				break;
			case 11:
				cout<<b.getHeight()<<endl;
				break;


			case 0:
				return 0;
				break;

			default:
				cout <<"Enter right choice"<<endl;
				break;
		}
	}
}
