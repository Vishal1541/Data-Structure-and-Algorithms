/****
	*	ADSA ASSIGNMENT - 1
	*	WRITTEN BY
	*	VISHAL ANAND
	*	B16040
	*	CSE
	*/

/*ip
7
5.5 2.3 9.0213 1.02 6.6589 3.14526 5.24111
*/
#include "sorting.cpp"
int NO_OF_ELEMENTS;

template<typename T>
void copyArray(T& source, T& destination){
	for(int i=0; i<NO_OF_ELEMENTS; i++)	destination[i] = source[i];
}

//Input of elements from the user
void input(auto& arr, auto& inp){									
	for(int i=0; i<NO_OF_ELEMENTS; i++){
		cin>>inp;
		arr.insert(i,inp);
	}
}

void sortIt(auto& sort_type, auto& arr, int startIndex, int endIndex, int key){
	switch(key){
		case 0: sort_type.insertionSort(arr,startIndex,endIndex);break;
		case 1: sort_type.bubbleSort(arr,startIndex,endIndex);break;
		case 2: sort_type.rankSort(arr,startIndex,endIndex);break;
		case 3: sort_type.selectionSort(arr,startIndex,endIndex);break;
		case 4: sort_type.mergeSort(arr,startIndex,endIndex);break;
		case 5: sort_type.quickSort(arr,startIndex,endIndex);break;
		case 6: sort_type.heapSort(arr,startIndex,endIndex);break;
	}
}
void printSortingType(int key){
	switch(key){
		case 0:cout<<"insertionSort: ";break;
		case 1:cout<<"bubbleSort: ";break;
		case 2:cout<<"rankSort: ";break;
		case 3:cout<<"selectionSort: ";break;
		case 4:cout<<"mergeSort: ";break;
		case 5:cout<<"quickSort: ";break;
		case 6:cout<<"heapSort: ";break;
	}
}
//Printing the copyArray
void printArray(auto& temp){
	for(int i=0; i<NO_OF_ELEMENTS; i++)	cout<<temp[i]<<" ";
	cout<<endl;
}

int main(){
	int SERIAL_NO,startIndex,endIndex;
	double inpNo;
	char inpCh;
	cout<<"Select serial no of the datatype to be used:\n\t1.int/floating points\t\t2.character\n";
	cin>>SERIAL_NO;
	cout<<"Enter the no of the elements:\t";
	cin>>NO_OF_ELEMENTS;

	//Int / Floating points type
	if(SERIAL_NO==1){
		LinearList<double> arr(NO_OF_ELEMENTS),temp(NO_OF_ELEMENTS);
		Sort<double> S;
		cout<<"Enter the elements: ";
		input(arr,inpNo);
		cout<<"Enter start and end index:\n";
		cin>>startIndex>>endIndex;
		for(int i=0; i<7; i++){
			copyArray(arr,temp);
			sortIt(S,temp,startIndex,endIndex,i);
			printSortingType(i);
			printArray(temp);
		}
	}

	//Character type
	else{
		LinearList<char> arr(NO_OF_ELEMENTS),temp(NO_OF_ELEMENTS);
		Sort<char> S;
		cout<<"Enter the elements: ";
		input(arr,inpCh);
		cout<<"Enter start and end index:\n";
		cin>>startIndex>>endIndex;
		for(int i=0; i<7; i++){
			copyArray(arr,temp);
			sortIt(S,temp,startIndex,endIndex,i);
			printSortingType(i);
			printArray(temp);
		}
	}
	return 0;
}
