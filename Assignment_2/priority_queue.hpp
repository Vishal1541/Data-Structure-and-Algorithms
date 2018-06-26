/**
 *
 * CS202 - Data Structures and Algorithms
 * Assignment 2
 *
 * @author: Priyansh Saxena
 */ 

#ifndef PQ_HPP
#define PQ_HPP 1
  
#include "seqLinearList.cpp"

/*
 * This class must implement a max-heap.
 *
 * The underlying container to be used for storing the elements
 * of heap must be seqLinearList from the previous assignment.
 * 
 */
template<class T>
class priority_queue {
    
  LinearList<T> container;
  unsigned int size;
    
  public:

  /*
   * Default contructor.
   * Should construct an empty priority_queue.
   * Size of the created priority_queue should be zero.
   */
   priority_queue();

  /*
   * Copy constructor.
   * Creates a new priority_queue which is a copy of the provided priority_queue.
   */
   priority_queue(const priority_queue<T>& x);

   /*
    * Destructor.
    * Frees all the memory acquired by the priority_queue.
    */
    ~priority_queue();

   /*
    * Returns the number of elements in the priority_queue.
    */
    inline int length();

   /*
    * Returns a boolean indicating whether the priority_queue is empty.
    */
    inline bool empty();

   /*
    * Gets the top-element of the priority-queue.
    */
    T top();

   /*
    * Inserts a new element in the priority_queue.
    */
    void push(const T& val);

   /*
    * Removes the top-element from the priority_queue.
    */
    void pop();

    void decrease();



    /***********************************
     *
     **     Bonus Marks Question      **
     *
     **********************************/
   /*
    * Exchanges the contents of the container adaptor by those of x, 
    * swapping both the underlying container value 
    * and their comparison function using the corresponding swap non-member functions (unqualified).
    * 
    */
    void swap (priority_queue& x); // noexcept;
     
};


#endif

template<class T>
void Swap(LinearList<T>& A, int i, int j){
  T temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int left(int i){
  return 2*i;
}

int right(int i){
  return 2*i+1;
}

template<class T>
void buildMaxHeap(LinearList<T>& A){
  int len = A.length();
  int i = len/2-1;
  int l,r,largest,index_change;
  while(i>=0){
    l = left(i+1);
    r = right(i+1);
    index_change = i;
    T largest = A[i];
    if(l<=A.length()) if(A[l-1]>largest)  {largest = A[l-1]; index_change = l-1;}
    if(r<=A.length()) if(A[r-1]>largest)  {largest = A[r-1]; index_change = r-1;}
    if(i != index_change){
      Swap(A,index_change,i);
    }
    else{
      break;
    }
    i=(i-1)/2;
  }
}

template<class T>
void Heapify(LinearList<T>& A, int index){
  int l = left(index+1);
  int r = right(index+1);
  int index_change = index;
  T largest = A[index];
  if(l<=A.length()) if(A[l-1]>largest)  {largest = A[l-1]; index_change = l-1;}
  if(r<=A.length()) if(A[r-1]>largest)  {largest = A[r-1]; index_change = r-1;}
  if(index != index_change){
    Swap(A,index_change,index);
    Heapify(A, index_change);
  }
}

template<class T>
priority_queue<T> :: priority_queue(){
  size = 0;
}

template<class T>
priority_queue<T> :: priority_queue(const priority_queue<T>& x){
  // size = x.length();
  // priority_queue<T> temp;
  // T t;
  // int len = x.length();
  // for(int i=0; i<len; i++){
  //   t = x.top();
  //   container.insert(i,t);
  //   temp.push(t);
  //   x.pop();
  // }
  // for(int i=0; i<len; i++){
  //   t = temp.top();
  //   x.push(t);
  //   temp.pop();
  // }
  T in;
  for(int i=0; i<x.size; i++){
    in = x.container.returnListElement(i);
    container.insert(i,in);
  }
}

template<class T>
priority_queue<T> :: ~priority_queue(){
  // ~container;
  size = 0;
}

template<class T>
inline int priority_queue<T> :: length(){
  return size;
}

template<class T>
inline bool priority_queue<T> :: empty(){
  return !(size>0);
}

template<class T>
T priority_queue<T> :: top(){
  return container[0];
}

template<class T>
void priority_queue<T> :: push(const T& val){
  T in = val;
  container.insertLast(in);
  size++;
  buildMaxHeap(container);
  // Heapify(container,0);
}

template<class T>
void priority_queue<T> :: pop(){
  T popped = container[0];
  // container.deleteElement(0,popped);
  container[0] = container[container.length()-1];
  size--;
  // buildMaxHeap(container);
  Heapify(container,0);
}

template<class T>
void priority_queue<T> :: decrease(){
  container[0]--;
  Heapify(container,0);
}

template<class T>
void priority_queue<T> :: swap (priority_queue& x){
  priority_queue<T> temp1;
  T t,dlt;
  int len = x.length();
  for(int i=0; i<len; i++){
    t = x.top();
    temp1.push(t);
    x.pop();
  }

  len = size;
  for(int i=0; i<len; i++){
    t = container[i];
    x.push(t);
  }

  for(int i=0; i<len; i++){
    container.deleteElement(i,dlt);
  }

  len = temp1.length();
  for(int i=0; i<len; i++){
    t = temp1.top();
    container.insert(i,t);
    temp1.pop();
  }
}