#include "AVL.hpp"
#include <limits>
//using namespace cs202;
using namespace std;

int main()
{
	int c;
	AVL<int,int> b;
	int k;
	int v;
	cout<<"0.Exit"<<endl<<"1. Insert a Node into a AVL"<<endl<<"2.Remove a Node"<<endl<<"3.Search a Key"<<endl;
	cout<<"4.Print Pre-Order"<<endl<<"5.Print Post Order"<<endl<<"6.Print in order"<<endl;
	cout<<"7. Minimum Key "<<endl<<"8. Maximum Key "<<endl<<"9.Get successor";
	cout<<endl<<"10.Get predessor"<<endl<<"11.Height"<<endl<<"12.Size"<<endl;
	while(true)
	{
		cout<<endl<<"Enter choice : ";
		cin>>c;
		switch(c)
		{
			case 0:
				return 0;
				break;

			case 1:
				cout<<"Enter key"<<endl;
				cin>>k;
				cout<<"Enter value"<<endl;
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
				break;

			case 5:
				b.print_post_order();
				break;

			case 6:
				b.print();
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
				if(b.successor(k) != -1)
					cout<<b.successor(k)<<endl;
				else
					cout<<"No successor"<<endl;
				break;

			case 10:
				cout<<"Enter the key"<<endl;
				cin>>k;
				if(b.predecessor(k) != -1)
					cout<<b.predecessor(k)<<endl;
				else
					cout<<"No predecessor"<<endl;
				break;

			case 11:
				cout<<b.getHeight()<<endl;
				break;

			case 12:
				cout<<b.size()<<endl;
				break;
			default:
				cout <<"Enter right choice"<<endl;
				break;
		}
	}
}
