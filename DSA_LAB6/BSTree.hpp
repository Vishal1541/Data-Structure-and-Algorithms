#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "Dictionary.hpp"

template <class Key,class Value>
class Node
{
public:
	Key key;
	Value val;
	Node<Key, Value> *left,*right,*parent;
	int height = -1;
	Node(){
		left = right = NULL;
		height = 0;
	}
	Node(Key k, Value v){
		key = k;
		val = v;
		left = right = NULL;
		height = 0;
	}
};

int noOfElements = 0;

template <class Key,class Value>
class BSTree : public Dictionary<Key, Value> {
 public:
	Node<Key,Value> *root = NULL;
  /*
   * This method returns the current height of the binary search tree.
   */
  virtual int getHeight(){
  	if(!root) return 0;
  	return root->height;
  }
  /*
   * This method returns the total number of elements in the binary search tree.
   */
  virtual int size(){
  	return noOfElements;
  }
  /*
   * This method prints the key value pairs of the binary search tree, sorted by
   * their keys.
   */
  virtual void print(){
  	// in_orderUtil(root,print2(root->key,root->val));
  }
  /*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in in-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void in_order(void (*fun)(const Key& key, const Value& value)){
  	in_orderUtil(root,fun);
  }
  virtual void in_orderUtil(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value)){
  	if(node){
  		in_orderUtil(node->left, fun);
  		fun(node->key, node->val);
  		in_orderUtil(node->right, fun);
  	}
  }
/*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in pre-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void pre_order(void (*fun)(const Key& key, const Value& value)){
  	pre_orderUtil(root, fun);
  }
  virtual void pre_orderUtil(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value)){
  	if(node){
  		fun(node->key, node->val);
  		pre_orderUtil(node->left, fun);
  		pre_orderUtil(node->right, fun);
  	}
  }
/*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in post-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void post_order(void (*fun)(const Key& key, const Value& value)){
  	post_orderUtil(root, fun);
  }
  virtual void post_orderUtil(Node<Key, Value> *node, void (*fun)(const Key& key, const Value& value)){
  	if(node){
  		post_orderUtil(node->left, fun);
  		post_orderUtil(node->right, fun);
  		fun(node->key, node->val);
  	}
  }

  virtual void print2(const Key& key, const Value& value){
  	std::cout<<"Key = "<<key<<" Value = "<<value<<std::endl;
  }

  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in an in order traversal.
   */
  virtual void print_in_order(){
  	// in_orderUtil(root,print(root->key,root->val));
  }
  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in an pre order traversal.
   */
  virtual void print_pre_order(){
  	// in_orderUtil(root,print(root->key,root->val));
  }
  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in a post order traversal.
   */
  virtual void print_post_order(){
  	// in_orderUtil(root,print(root->key,root->val));
  }
  /*
   *This method returns the minimum element in the BST.
   */
  virtual Key minimun(){
  	Node<Key,Value> *temp = root;
  	while(temp->left)	temp = temp->left;
  	return temp->key;
  }
  /*
   * This method returns the maximum element in the BST.
   */
  virtual Key maximum(){
  	Node<Key,Value> *temp = root;
  	while(temp->right)	temp = temp->right;
  	return temp->key;
  }
  /*
   *This method returns the successor, i.e, the next larget element in the
   *BSTree, after Key.
   */
  virtual Key successor(const Key& key){
  	Node<Key,Value> *temp = root;
  	while(temp->key != key){
  		if(temp->key > key)	temp = temp->left;
  		else temp = temp->right;
  	}
  	if(!(temp->right))	return key;
  	temp = temp->right;
  	while(temp->left){
  		temp = temp->left;
  	}
  	return temp->key;
  }
  /*
   * This method returns the predessor, ie, the next smallest element in the
   * BSTree, after Key.
   */
  virtual Key predecessor(const Key& key){
  	Node<Key,Value> *temp = root;
  	while(temp->key != key){
  		if(temp->key > key)	temp = temp->left;
  		else temp = temp->right;
  	}
  	if(!(temp->left))	return key;
  	temp = temp->left;
  	while(temp->right){
  		temp = temp->right;
  	}
  	return temp->key;
  }
  	Node<Key,Value> *temp_srch = root;
  	Node<Key,Value>* searchByKey(const Key& key){
  		if(root==NULL)	return root;
  		while(temp_srch){
  			if(temp_srch->key == key)	return temp_srch;
  			if(temp_srch->key > key)	temp_srch = temp_srch->left;
  			else 	temp_srch = temp_srch->right;
  		}
  		return temp_srch;
  	}	
    /*
     * Function : has
     * Returns true if the dictionay contains the key
     * false otherwise. It is search operation
     */
	bool has(const Key& key){
		return searchByKey(key);
	}
	Node<Key,Value>* giveSuccessor(Node<Key,Value> *node){
		Node<Key,Value> *curr = node;
		while(curr->left)	curr = curr->left;
		return curr;
	}
    /*
     * Function : remove
     * Removes the given key and the corresponding value from the Dictionary if the key is in the dictionary.
     * Does nothing otherwise.
     */
	void remove(const Key& key){
		temp_srch = searchByKey(key);
		if(temp_srch){
			Node<Key,Value> *rot = removeUtil(temp_srch, key);
			noOfElements--;
		}
	}
	Node<Key,Value>* removeUtil(Node<Key,Value> *node,const Key& key){
		if(node==NULL)	return node;
		if(node->key > key)
			node->left = removeUtil(node->left,key);
		else if(node->key < key)
			node->right = removeUtil(node->right,key);
		else{
			Node<Key,Value> *temp;
			if(node->left==NULL){
				temp = node->right;
				return temp;
			}
			else if(node->right == NULL){
				temp = node->left;
				return temp;
			}
			temp = giveSuccessor(node->right);
			node->key = temp->key;
			node->right = removeUtil(node->right,temp->key);
		}
		return node;
	}
    /*
     * Function : get
     * Returns the value associated with the given key.
     * Raises an exception if the key does'nt exist in the dictionary.
     */
	Value get(const Key& key){
		Node<Key,Value> *temp = searchByKey(key);
		return temp->val;
	}
    /*
     * Function : put
     * If the key doesn't exist in the dictionary, then insert the given key and value in the dictionary.
     * Otherwise change the value associated with the key to the given value.
     */
	void put(const Key& key, const Value& value){
		Node<Key,Value> *temp = root;
		if(root==NULL){
			root = new Node<Key,Value>(key,value);
		}
		else{
			while(temp){
				if(temp->key>key){
					temp = temp->left;
				}
				else{
					temp = temp->right;
				}
			}
			if(temp->key>key){
				temp->left = new Node<Key,Value>(key,value);
			}
			else{
				temp->right = new Node<Key,Value>(key,value);
			}
		}
		noOfElements++;
	}
};

#endif /* ifndef BSTREE_HPP */