#ifndef BSTREE_HPP
#define BSTREE_HPP 1
#include "Dictionary.hpp"
using namespace std;
template <class Key, class Value>
class BSTree : public Dictionary<Key, Value> {
  node<Key, Value> *root;
  int sizes;
  virtual int height(node<Key,Value>* n){
    if(!n)
      return -1;
    int r = height(n->right);
    int l = height(n->left);
    if(r>=l)
      return r+1;
    else
      return l+1;
  }
  virtual void func(Key k, Value v){
    cout<<k<<' ' <<v<<endl;
  }
  virtual void print_inorder(node<Key,Value>* n){
    if(n==NULL)
      return;
    print_inorder(n->left);
    func(n->key,n->value);
    print_inorder(n->right);
  }
  virtual void print_preorder(node<Key,Value>* n){
    if(n==NULL)
      return;
    func(n->key,n->value);
    print_preorder(n->left);
    print_preorder(n->right);
  }
  virtual void print_postorder(node<Key,Value>* n){
    if(n==NULL)
      return;
    print_postorder(n->left);
    print_postorder(n->right);
    func(n->key,n->value);
  }

  virtual void inorder(node<Key,Value>* n, void (*fun)(const Key& key, const Value& value)){
    if(n==NULL)
      return;
    inorder(n->left,fun);
    fun(n->key,n->value);
    inorder(n->right, fun);
  }
  virtual void preorder(node<Key,Value>* n, void (*fun)(const Key& key, const Value& value)){
    if(n==NULL)
      return;
    fun(n->key,n->value);
    preorder(n->left, fun);
    preorder(n->right, fun);
  }
  virtual void postorder(node<Key,Value>* n, void (*fun)(const Key& key, const Value& value)){
    if(n==NULL)
      return;
    postorder(n->left, fun);
    postorder(n->right, fun);
    fun(n->key,n->value);
  }
 public:
  BSTree(){
    sizes = 0;
    root = NULL;
  }
  /*
   * This method returns the current height of the binary search tree.
   */
  virtual int getHeight();
  /*
   * This method returns the total number of elements in the binary search tree.
   */
  virtual int size();
  /*
   * This method prints the key value pairs of the binary search tree, sorted by
   * their keys.
   */
  virtual void print();
  /*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in in-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void in_order(void (*fun)(const Key& key, const Value& value));
/*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in pre-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void pre_order(void (*fun)(const Key& key, const Value& value));
/*
   *This method takes as an argument a function func.
   *Then it traverses along the tree in post-order traversal, and calls func
   *with every key value pair in the BSTree.
   */
  virtual void post_order(void (*fun)(const Key& key, const Value& value));

  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in an in order traversal.
   */
  virtual void print_in_order();
  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in an pre order traversal.
   */
  virtual void print_pre_order();
  /*
   *This method print all the key value pairs of the binary search tree, as
   *observed in a post order traversal.
   */
  virtual void print_post_order();
  /*
   *This method returns the minimum element in the BST.
   */
  virtual Key minimum();
  /*
   * This method returns the maximum element in the BST.
   */
  virtual Key maximum();
  /*
   *This method returns the successor, i.e, the next larget element in the
   *BSTree, after Key.
   */
  virtual Key successor(const Key& key);
  /*
   * This method returns the predessor, ie, the next smallest element in the
   * BSTree, after Key.
   */
  virtual Key predecessor(const Key& key);
  void put(const Key& key, const Value& value);
  Value get(const Key& key);
  bool has(const Key& key);
  void remove(const Key& key);
  virtual node<Key,Value>* getNode(const Key& key);
};

template <class Key,class Value>
Value BSTree<Key,Value>::get(const Key& key){
    if(has(key)){
      node<Key,Value> *x = getNode(key);
      return x->value;
    }
    else{
      cout<<"Key isn't present in tree";
    }
}

template <class Key,class Value>
void BSTree<Key,Value>::remove(const Key& key){
    if(has(key)){
      node<Key,Value> *x = getNode(key); 
      if(x->left==NULL && x->right==NULL){
        node<Key,Value> *temp = root;
        node<Key,Value> *parent = NULL;
        while(temp!=NULL){
          if (x->key > temp->key)
          {
              parent = temp;
              temp = temp->right;
              if(temp->key == x->key){
                parent->right = NULL;
                break;
              }
          }
          else if (x->key < temp->key){         
              parent = temp;
              temp = temp->left;
              if(temp->key == x->key){
                parent->left = NULL;
                break;
              }
          }
        }
        sizes--;
        delete(x);
      }
      else if(x->right==NULL){
        sizes--;
       x->copy(x->left);
      }
      else if(x->left==NULL){
        sizes--;
        x->copy(x->right);
      }
      else{
        Key temp_k = successor(x->key);
        Value temp_v = get(temp_k);
        remove(temp_k);
        x->key = temp_k;
        x->value = temp_v;  
      }
      
    }
    else{
      cout<<"Key isn't present in tree";
    }
}

template <class Key,class Value>
int BSTree<Key,Value>::getHeight(){
  return height(root);
}

template <class Key,class Value>
int BSTree<Key,Value>::size(){
  return sizes;
}

template <class Key,class Value>
void BSTree<Key,Value>::print(){
  print_in_order();
}

template <class Key,class Value>
void BSTree<Key,Value>::print_in_order(){
  print_inorder(root);
}

template <class Key,class Value>
void BSTree<Key,Value>::print_pre_order(){
  print_preorder(root);
}

template <class Key,class Value>
void BSTree<Key,Value>::print_post_order(){
  print_postorder(root);
}

template <class Key,class Value>
void BSTree<Key,Value>::in_order(void (*fun)(const Key& key, const Value& value)){
  inorder(root, fun);
}
template <class Key,class Value>
void BSTree<Key,Value>::pre_order(void (*fun)(const Key& key, const Value& value)){
  preorder(root, fun);
}template <class Key,class Value>
void BSTree<Key,Value>::post_order(void (*fun)(const Key& key, const Value& value)){
  postorder(root, fun);
}
template <class Key,class Value>
node<Key,Value>* BSTree<Key,Value>::getNode(const Key& key){
  node<Key,Value> *x = root;
  while(x!=NULL){
    if(x->key==key)
      return x;
    else if(key<x->key)
      x = x->left;
    else
      x = x->right;
  }
  return x;
}

template <class Key,class Value>
Key BSTree<Key,Value>::minimum(){
  node<Key,Value> *min = root;
  while (min->left!=NULL){
    min = min->left;
  }
  Key m = min->key;
  return m;
}

template <class Key,class Value>
Key BSTree<Key,Value>::maximum(){
  node<Key,Value> *max = root;
  while (max->right!=NULL){
    max = max->right;
  }
  Key m = max->key;
  return m;
}

template <class Key,class Value>
Key BSTree<Key,Value>::successor(const Key& key){
    node<Key,Value> *ret = getNode(key);
    if(ret->right!=NULL){
      ret = ret->right;
      while (ret->left!=NULL)
        ret = ret->left;
      return ret->key;
    }
    node<Key,Value> *t = root;
    node<Key,Value> *next = NULL;
    while (t != NULL)
    {
        if (ret->key < t->key)
        {
            next = t;
            t = t->left;
        }
        else if (ret->key > t->key)
            t = t->right;
        else
           break;
    }
 
    return next->key;

}

template <class Key,class Value>
Key BSTree<Key,Value>::predecessor(const Key& key){
    node<Key,Value> *ret = getNode(key);
    if(ret->left!=NULL){
      ret = ret->left;
      while (ret->right!=NULL)
        ret = ret->right;
      return ret->key;
    }
    node<Key,Value> *t = root;
    node<Key,Value> *prev = NULL;
    while (t != NULL)
    {
        if (ret->key > t->key)
        {
            prev = t;
            t = t->right;
        }
        else if (ret->key < t->key)
            t = t->left;
        else
           break;
    }
 
    return prev->key;

}

template <class Key,class Value>
void BSTree<Key,Value>::put(const Key& key, const Value& value){
    node<Key,Value> *ins = new node<Key,Value>(key, value);
    if(root==NULL){
      sizes++;
      root = ins;
      return;
    }
    sizes++;
    node<Key,Value> *temp = root;
    while(true){
      if(key >= temp->key){
        if(temp->right!=NULL)
          temp = temp->right;
        else{
          temp->right = ins;
          break;
        }
      }
      else{
        if(temp->left!=NULL)
          temp = temp->left;
        else{
          temp->left = ins;
          break;
        } 
      }
    }
}

template <class Key,class Value>
bool BSTree<Key,Value>::has(const Key& key){
    node<Key,Value> *x = root;
    while(x!=NULL){
      if(key > x->key)
        x = x->right;
      else if(key < x->key)
        x = x->left;
      else
        return true;
    }
    return false;

}

#endif /* ifndef BSTREE_HPP */