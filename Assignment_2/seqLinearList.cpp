/****
	*	ADSA ASSIGNMENT - 1
	*	WRITTEN BY
	*	VISHAL ANAND
	*	B16040
	*	CSE
	*/
#include "seqLinearList.hpp"
#define __t template<class Item>

__t
LinearList<Item>::  LinearList(){
	element = new Item[1000005];
	len = 0;
	MaxSize = 1000005;
}
__t
LinearList<Item>:: LinearList(const int& MaxListSize){
	element = new Item[MaxListSize];
	len = 0;
	MaxSize = MaxListSize;
}
__t
LinearList<Item>:: ~LinearList(){
	// delete[] element;
	// len = 0;
	// MaxSize = 0;
}
__t
Item& LinearList<Item>:: operator[](const int& i){
	return element[i];
}
__t
bool LinearList<Item>:: isEmpty(){
	return (len==0)?true:false;
}
__t
int LinearList<Item>:: length(){
	return len;
}
__t
int LinearList<Item>::  maxSize(){
	return MaxSize;
}
__t
Item LinearList<Item>:: returnListElement(const int k){
	return element[k];
}
__t
bool LinearList<Item>:: find(const int k, Item& x){
	return (element[k-1]==x);
}
__t
int LinearList<Item>:: search(Item& x){
	for(int i=0; i<len; i++)
		if(element[i]==x)	return i+1;
	return 0;
}
__t
void LinearList<Item>::  deleteElement(const int  k, Item& x){
	x = element[k];
	for(int i=k; i<len-1; i++)	element[i] = element[i+1];
	len--;
}
__t
void LinearList<Item>:: insert(const int  k, Item& x){
	if(len+1>MaxSize)	MaxSize = MaxSize*2+1;
	Item *temp = new Item[MaxSize];
	for(int i=0; i<k; i++)	temp[i] = element[i];
	temp[k] = x;
	for(int i=k+1; i<=len; i++)	temp[i] = element[i-1];
	delete[] element;
	element = new Item[MaxSize];
	for(int i=0; i<=len; i++)	element[i] = temp[i];
	delete[] temp;
	len++;
}
__t
void LinearList<Item>:: insertLast(Item& x){
	element[len] = x;
	len++;
}