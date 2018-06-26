/**
 *
 * CS202 - Data Structures and Algorithms
 * Assignment 2
 *
 * @author: Priyansh Saxena
 */ 

#ifndef LIST_HPP
#define LIST_HPP 1

template<class T>
struct node{
  T value;
  struct node *next;
};

  	
template<class T>
class list {
    
    node<T> *head;
    unsigned int len;
    
  public:

  /*
   * Default contructor.
   * Should construct an empty list.
   * Size of the created list should be zero.
   */
   list();

  /*
   * Copy constructor.
   * Creates a new list which is a copy of the provided list.
   */
   list(const list<T> & x);

   /*
    * Destructor.
    * Frees all the memory acquired by the list.
    */
    ~list();

   /*
    * Returns the length of the list.
    */
    inline int length();

   /*
    * Returns a boolean indicating whether the list is empty.
    */
    inline bool empty();

   /*
    * adds value at the end of the list.
    */
    void append(const T& value);

   /*
    * Appends the given list x at the end of the current list.
    */
    void append(list<T>& x);

   /*
    * Adds a value to the front of the list.
    */
    void cons(const T& value);

   /*
    * Removes the first occurence of the value from list.
    */
    void remove(const T & x);
     
   /*
    * Returns head of list
    */ 
    T get_head();
     
};

#endif

template<class T>
list<T>::list(){
  head = NULL;
  len = 0;
}

template<class T>
list<T>::list(const list<T> & x){
  node<T> *nextHead = x.head;
  head = NULL;
  node<T> *nextTemp = head; 
  while(nextHead!=NULL){
    if(head==NULL){
      head = new node<T>; 
      nextTemp = head;
    }
    else{
      nextTemp = nextTemp->next;
    }
    nextTemp->value = nextHead->value;
    nextHead = nextHead->next;
    nextTemp->next = new node<T>;
  }
  delete nextTemp->next;
  nextTemp->next = NULL;
  len = x.len;
}

template<class T>
list<T>::~list(){
  delete head;
  len = 0;
}

template<class T>
inline int list<T>::length(){
  return len;
}

template<class T>
inline bool list<T>::empty(){
  return !(len>0);
}

template<class T>
void list<T>::append(const T& value){
  node<T> *temp = head;
  if(temp==NULL){
    temp = new node<T>;
    temp->value = value;
    temp->next = NULL;
    head = temp;
  }
  else{
    while(temp->next!=NULL) temp = temp->next;
    temp->next = new node<T>;
    temp = temp->next;
    temp->value = value;
    temp->next = NULL;
  }
  temp = NULL;
  len++;
}

template<class T>
void list<T>::append(list<T>& x){
  node<T> *temp = head;
  if(temp==NULL){
    temp = x;
  }
  else{
    while(temp->next != NULL) temp = temp->next;
    temp->next = x;
  }
  len += x.length();
  x = NULL;
}

template<class T>
void list<T>::cons(const T& value){
  node<T> *temp = new node<T>;
  temp->value = value;
  temp->next = head;
  head = temp;
  len++;
}

template<class T>
void list<T>::remove(const T & x){
  node<T> *front = head;
  node<T> *prv = NULL;
  while(front->value != x){
    if(prv==NULL){
      prv = head;
    }
    else{
      prv = prv->next;
    }
    front = front->next;
  }
  if(prv==NULL){
    head = front->next;
  }
  else{
    prv->next = front->next;
  }
  front->next = NULL;
  delete front;
  len--;
}

template<class T>
T list<T>::get_head(){
  return head->value;
}
