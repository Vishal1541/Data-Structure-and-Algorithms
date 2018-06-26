#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP


template<class Key, class Value>
class doublyNode{
public:
	Key key;
	Value value;
	doublyNode<Key,Value> *next,*prv;
	doublyNode<Key,Value>(Key k, Value v):
		key(k),value(v),prv(NULL),next(NULL){}
	// {
	// 	key = k;
	// 	value = v;
	// 	next = NULL;
	// 	prv = NULL;
	// }
};

template<class Key, class Value>
class DoublyLinkedList{

	private:
		doublyNode<Key,Value> *front,*back;

	public:
		DoublyLinkedList():
			front(NULL), back(NULL){}
		// {
		// 	front = NULL;
		// 	back = NULL;
		// }
		~DoublyLinkedList(){
			front = NULL;
			back = NULL;	
		}
		doublyNode<Key,Value>* addToHead(Key key, Value value){
			doublyNode<Key, Value> *temp = new doublyNode<Key,Value>(key, value);
			if(front==NULL && back==NULL){
				front = back = temp;
			}
			else{
				temp->next = front;
				front->prv = temp;
				front = temp;
				// front->prv = NULL;
			}
			return temp;
		}
		void moveToHead(doublyNode<Key, Value> *node){
			if(node==front)	return;
			if(node==back){
				back = back->prv;
				back->next = NULL;
				// node->prv = NULL;
			}
			else{
				node->prv->next = node->next;
				node->next->prv = node->prv;
				// node->prv = node->next = NULL;
			}
			node->next = front;
			node->prv = NULL;
			front->prv = node;
			front = node;
			// front->prv = node;
			// front = node;
			// front->prv = NULL;
		}
		void removeBackPage(){
			if(back==NULL)	return;
			if(back==front){
				// delete back;
				back = front = NULL;
			}
			else{
				doublyNode<Key,Value> *temp = back;
				back = back->prv;
				back->next = NULL;
				temp->prv = NULL;
				// delete temp;
			}
		}
		doublyNode<Key, Value>* getBack(){
			return back;
		}
		// bool isEmpty(){
		// 	return back==NULL;
		// }
};

#endif
