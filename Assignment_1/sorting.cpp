/****
	*	ADSA ASSIGNMENT - 1
	*	WRITTEN BY
	*	VISHAL ANAND
	*	B16040
	*	CSE
	*/
#include "sorting.hpp"
#define __t template<class Item>

__t
void swap(LinearList<Item>& A, int i, int j){
	Item temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// O(n), O(n2)
__t
void Sort<Item>:: insertionSort(LinearList<Item>& A, int low, int high){
	for(int i=low+1; i<=high; i++){
		Item key = A[i];
		int j;
		for(j=i-1; j>=low; j--){
			if(A[j]>key)	A[j+1] = A[j];
			else 			break;
		}
		A[j+1] = key;
	}
}
// O(n2)
__t
void Sort<Item>:: bubbleSort(LinearList<Item>& A, int low, int high){
	int l=0, h=high-low;
	LinearList<Item> temp(high-low+1);
	for(int i=0; i<=high-low; i++)	temp[i] = A[i+low];
	for(int i=l; i<h; i++){
		for(int j=l+1; j<=h-i; j++){
			if(temp[j]<temp[j-1])		swap(temp,j,j-1);
		}
	}
	for(int i=0; i<=high-low; i++)	A[i+low] = temp[i];
}

// O(n2)
__t
void Sort<Item>:: rankSort(LinearList<Item>& A, int low, int high){
	int rankArr[high-low+1];
	Item *temp = new Item(A.length());
	for(int i=0; i<=high-low; i++)	rankArr[i] = 1;
	for(int i=1; i<=high-low; i++){
		for(int j=i-1; j>=0; j--){
			if(A[i+low]>A[j+low])	rankArr[i]++;
			else 					rankArr[j]++;
		}
	}
	for(int i=0; i<=high-low; i++)	temp[rankArr[i]-1+low] = A[i+low];
	for(int i=low; i<=high; i++)	A[i] = temp[i];
	//delete[] temp;
}

// O(n2)
__t
void Sort<Item>:: selectionSort(LinearList<Item>& A, int low, int high){
	Item min;
	int minIndex;
	for(int i=low; i<high; i++){
		min = A[i];
		minIndex = i;
		for(int j=i; j<=high; j++){
			if(A[j]<min){
				min = A[j];
				minIndex = j;
			}
		}
		swap(A,i,minIndex);
	}
}

//O(nlogn)
__t
void Sort<Item>:: mergeSort(LinearList<Item>& A, int low, int high){
	int mid = (low+high)/2;
	if(high>low){
		mergeSort(A,low,mid);
		mergeSort(A,mid+1,high);
		merge(A,low,high);
	}
}
__t
void merge(LinearList<Item>& A, int low, int high){
	Item *temp = new Item(high-low+1);
	int mid = (low+high)/2, lptr=low, rptr=mid+1, tempPtr=0;
	while(lptr<=mid && rptr<=high){
		if(A[lptr]<A[rptr])	temp[tempPtr++] = A[lptr++];
		else 				temp[tempPtr++] = A[rptr++];
	}
	for(int i=lptr; i<=mid; i++)	temp[tempPtr++] = A[i];
	for(int i=rptr; i<=high; i++)	temp[tempPtr++] = A[i];
	for(int i=0; i<=high-low; i++)	A[i+low] = temp[i];
	//delete[] temp;
}

// O(nlogn), O(n2)
__t
void Sort<Item>:: quickSort(LinearList<Item>& A, int low, int high){
	if(high>low){
		int pivotIndex = partition(A,low,high);
		quickSort(A,low,pivotIndex-1);
		quickSort(A,pivotIndex+1,high);
	}
}
__t
int partition(LinearList<Item>& A, int low, int high){
	int i=low, j=low;
	while(j<high)
		if(A[j++]<A[high])	swap(A,i++,j-1);
	swap(A,i,high);
	return i;
}

// O(n)->tight, O(nlogn)

int left(int i){
	return 2*i;
}

int right(int i){
	return 2*i+1;
}
int parent(int i){
	return i/2;
}
// O(n) , O(nlogn)
__t
void Sort<Item>:: heapSort(LinearList<Item>& A, int low, int high){
	int heapSize = high-low+1;
	int l=0, h=high-low;
	LinearList<Item> temp(high-low+1);
	for(int i=0; i<=high-low; i++)	temp[i] = A[i+low];
	buildHeap(temp,l,h,heapSize);
	for(int i=h; i>l; i--){
		swap(temp,l,i);
		heapSize--;
		Heapify(temp, l, heapSize);
	}
	for(int i=0; i<=high-low; i++)	A[i+low] = temp[i];
}
__t
void buildHeap(LinearList<Item>& A, int low, int high,int &heapSize){
	int length = high-low+1;
	for(int i=length/2-1; i>=low; i--)
		Heapify(A,i,heapSize);
}
__t
void Heapify(LinearList<Item>& A, int index, int &heapSize){
	int l = left(index+1);
	int r = right(index+1);
	int index_change = index;
	Item largest = A[index];
	if(l<=heapSize) if(A[l-1]>largest)	{largest = A[l-1]; index_change = l-1;}
	if(r<=heapSize) if(A[r-1]>largest)	{largest = A[r-1]; index_change = r-1;}
	if(index != index_change){
		swap(A,index_change,index);
		Heapify(A, index_change, heapSize);
	}
}
