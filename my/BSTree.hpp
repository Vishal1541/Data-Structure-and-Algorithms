#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include <bits/stdc++.h>
#include "Dictionary.hpp"
using namespace std;
template <class Key,class Value>
class Node{
public:
	Key key;
	Value value;
	Node<Key,Value> *left,*right,*parent;
	Node()
	{
		key=-1;
		value=-1;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
	Node(Key k,Value v)
	{
		key=k;
		value=v;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
};
template<class Key, class Value>
class BSTree: public Dictionary<Key,Value>{
protected:
	Node<Key,Value>* root;
public:
	BSTree()
	{
		root=NULL;
	}
	Node<Key,Value> * search(Node<Key,Value> *root, const Key & key)
	{
		if(root==NULL)
			return NULL;
		else if((root->key)>key)
			return search(root->left,key);
		else if((root->key)<key)
			return search(root->right,key);
		else if((root->key)==key)
			return root;

	}
	void inorder(Node<Key,Value> *root)
	{
		if(root==NULL)
			return;
		inorder(root->left);
		cout<<root->key<<" ";
		inorder(root->right);
	}
	void preorder(Node<Key,Value> *root)
	{
		if(root==NULL)
			return;
		cout<<root->key<<" ";
		preorder(root->left);
		preorder(root->right);
	}
	void postorder(Node<Key,Value> *root)
	{
		if(root==NULL)
			return;
		postorder(root->left);

		postorder(root->right);
		cout<<root->key<<" ";
	}
	int height(Node<Key,Value> *root)
	{
	     if(root==NULL)
	     	return 0;
	     return (max((height(root->left)),(height(root->right))) +1);
	}
	virtual int getHeight()
	{
		return height(this->root)-1;
	}
	int getsize(Node<Key,Value> *root)
	{
		int lftsize,rhtsize;
		if(root=NULL)
			return 0;
		lftsize=getsize(root->left);
		rhtsize=getsize(root->right);
		return lftsize+rhtsize+1;

	}
	virtual int size()
	{
		return getsize(this->root);
	}
	virtual void print()
	{
		this->print_in_order();
	}
	virtual void print_in_order()
	{
		inorder(root);
	}
	virtual void print_pre_order()
	{
		preorder(root);
	}
	virtual void print_post_order()
	{
		postorder(root);
	}
	virtual Key minimum()
	{
		Node <Key,Value> *temp;
		temp=this->root;
		while(temp->left!=NULL)
		{
			temp=temp->left;
		}
		return temp->key;
	}
	virtual Key maximum()
	{
		Node <Key,Value> *temp;
		temp=this->root;
		while(temp->right!=NULL)
		{
			temp=temp->right;
		}
		return temp->key;
	}
	virtual Key successor(const Key& key)
	{
		Node<Key,Value> *ptr1, *ptr2=search(this->root,key);
		if(ptr2->right!=NULL)
		{
			ptr2=ptr2->right;
			while(ptr2->left!=NULL)
				ptr2=ptr2->left;
			return ptr2->key;
		}
		else if(ptr2->left!=NULL)
		{
			ptr1=ptr2;
			while(ptr1->parent->left!=ptr1)
				ptr1=ptr1->parent;
			if(ptr1!=NULL)
				return ptr1->parent->key;
			if(ptr1==NULL)
				return -1;
		}
		else 
			return -1;


	}
	virtual Key predecessor(const Key& key)
	{
		Node<Key,Value> *ptr1, *ptr2=search(this->root,key);
		if(ptr2->left!=NULL)
		{
			ptr2=ptr2->left;
			while(ptr2->right!=NULL)
				ptr2=ptr2->right;
			return ptr2->key;
		}
		else if(ptr2->right!=NULL)
		{
			ptr1=ptr2;
			while(ptr1->parent->right!=ptr1)
				ptr1=ptr1->parent;
			if(ptr1!=NULL)
				return ptr1->parent->key;
			if(ptr1==NULL)
				return -1;
		}
		else 
			return -1;

	}
	bool has (const Key& key)
	{
		Node<Key,Value> *temp=search(root,key);
		if (temp==NULL)
		{
			return false;
		}
		else 
			return true;
	}
	Value get(const Key& key)
	{
		Node<Key,Value> *p=search(root,key);
		return p->value;
	}
	virtual Node<Key,Value> * putrecur(Node<Key,Value> *root, Key key, Value value)
	{
		Node<Key,Value> *ptr;
		if(root==NULL)
		{
			ptr=new Node<Key,Value>;
			ptr->key=key;
			ptr->value=value;
			ptr->left=NULL;
			ptr->right=NULL;
			ptr->parent=NULL;
			root=ptr;
			return root;
		}
		if(root->key<key)
		{
			ptr=putrecur(root->right,key,value);
			ptr->parent=root;
			root->right=ptr;
		}
		else if(root->key>key)
		{
			ptr=putrecur(root->left,key,value);
			ptr->parent=root;
			root->left=ptr;
		}

	}
	void put(const Key& key, const Value& value)
	{
	   
	    this->root=putrecur(this->root,key,value);
	}
	virtual Node<Key,Value> * deleteNode(Node<Key,Value> *root,Key key)
	{
		if(root==NULL)
			return root;
		// If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
		if(key< root->key)
		{
			root->left=deleteNode(root->left,key);
		}
		// If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
		else if(key> root->key)
		{
			root->right=deleteNode(root->right,key);


		}
		// if key is same as root's key, then This is the node
    // to be deleted
		else 
		{
			// node with only one child or no child
			if(root->left==NULL)
			{
				Node<Key,Value> *temp= root->right;
				delete root;
				return temp;   
			}
			else if(root->right==NULL)
			{
				Node<Key,Value> *temp= root->left;
				delete root;
				return temp;

			}
			// node with two children: Get the inorder successor (smallest
        // in the right subtree)
			Node<Key,Value> *temp, *ptr;
			ptr=root->right;
			//inorder successor
			while(ptr->left!=NULL)
			{
				ptr=ptr->left;
			}
			temp=ptr;
			root->key=temp->key;
			root->right=deleteNode(root->right,temp->key);
		}
		return root;
	}
	void remove(const Key& key)
	{
		this->root=deleteNode(this->root,key);


	}
	void inorder1(Node<Key,Value> *root,void (*fun)(const Key& key, const Value& value))
	{
		if(root==NULL)
			return;
		inorder1(root->left,fun);
		fun(root->key,root->value);
		inorder1(root->right,fun);
	}

	virtual void in_order(void (*fun)(const Key& key, const Value& value))
  	{
  		inorder1(root,fun);

  	}
  	void preorder1(Node<Key,Value> *root,void (*fun)(const Key& key, const Value& value))
	{
		if(root==NULL)
			return;
		fun(root->key,root->value);
		preorder1(root->left,fun);
		preorder1(root->right,fun);
	}

	virtual void pre_order(void (*fun)(const Key& key, const Value& value))
  	{
  		preorder1(root,fun);

  	}
  	void postorder1(Node<Key,Value> *root,void (*fun)(const Key& key, const Value& value))
	{
		if(root==NULL)
			return;
		postorder1(root->left,fun);
	    postorder1(root->right,fun);
	    fun(root->key,root->value);
	}

	virtual void post_order(void (*fun)(const Key& key, const Value& value))
  	{
  		postorder1(root,fun);

  	}
};
#endif