#ifndef AVL_HPP
#define AVL_HPP 1
#include "BSTree.hpp"
template <class Key,class Value>
class AVL : public BSTree<Key, Value> {
  public:
    Node<Key,Value>  *leftrotate(Node<Key,Value>  * z)
    {
        Node<Key,Value>  * y;
        y=z->right;
        y->parent=z->parent;
        if(z->parent==NULL)
          {
              this->root=y;
          }
        else if(z->parent->left==z)
            z->parent->left=y;
        else
            z->parent->right=y;

        z->parent=y;
        z->right=y->left;
        if(y->left!=NULL)
            y->left->parent=z;
        y->left=z;
         return y;
   }

    Node<Key,Value>  * rightrotate(Node<Key,Value>  * z)
    {
        Node<Key,Value>  * y;
        y=z->left;
        y->parent=z->parent;
        if(z->parent==NULL)
        {
           this-> root=y;
        }
       else if(z->parent->left==z)
            z->parent->left=y;
        else
            z->parent->right=y;
        z->parent=y;
        z->left=y->right;
        if(y->right!=NULL)
            y->right->parent=z;
        y->right=z;
        return y;
     }


    int getbalance(Node<Key,Value>  * z)
    {

         BSTree<Key,Value> obj;
    	 //cout<<(obj.height(z->left))-(obj.height(z->right))<<endl;
       return (obj.height(z->left))-(obj.height(z->right));
    }

    Node<Key,Value> * doBalance(Node<Key,Value> *root)
    {
      int balance = getbalance(root);
        if (balance > 1 && getbalance(root->left) >= 0)
            { 
              return rightrotate(root);
            }

        if (balance > 1 && getbalance(root->left) < 0)
        {
            root->left =  leftrotate(root->left);
            
            return rightrotate(root);
        }

        if (balance < -1 && getbalance(root->right) <= 0)
        {
          
            return leftrotate(root);
        }

        if (balance < -1 && getbalance(root->right) > 0)
        {
            root->right = rightrotate(root->right);
            
            return leftrotate(root);
        }
        return root;
  }
  Node<Key,Value> * putrecur(Node<Key,Value> *root, Key key, Value value)
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
    root=doBalance(root);
    return root;
  }

  virtual void put(const Key& key, const Value& value)
  {
    this->root=putrecur(this->root,key,value);

               
  }
  Node<Key,Value> * deleteNode(Node<Key,Value> *root,Key key)
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
    root=doBalance(root);
    return root;
    

  }
  

    virtual void remove(const Key& key)//__________________________________________________________________________________________
  {
      this->root=deleteNode(this->root,key);
  }

  /*
   * Inherit as much functionality as possible from the BSTree class.
   * Then provide custom AVL Tree functionality on top of that.
   * The AVL Tree should make use of as many BST functions as possible.
   * Override only those methods which are extremely necessary.
   */
  /*
   * Apart from that, your code should have the following four functions:
   * getBalance(node) -> To get the balance at any given node;
   * doBalance(node) -> To fix the balance at the given node;
   * rightRotate(node) -> Perform a right rotation about the given node.
   * leftRotate(node) -> Perform a left rotation about the given node.
   *
   * The signature of these functions are not provided in order to provide you
   * some flexibility in how you implement the internals of your AVL Tree. But
   * make sure these functions are there.
   */

};
#endif /* ifndef AVL_HPP */
