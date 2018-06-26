#ifndef LRU_HPP
#define LRU_HPP


#include "DoublyLinkedList.hpp"
#include "OpenMap.hpp"


template<class Key,class Value>
class LRUCache{
	private:
		int capacity,current_size;
		DoublyLinkedList<Key,Value> *page;
		cs202::OpenMap<Key,doublyNode<Key,Value>* > page_map;

	public:
		LRUCache(int maxSize){
			capacity = maxSize;
			current_size = 0;
			page = new DoublyLinkedList<Key,Value>();
			page_map = cs202::OpenMap<Key,doublyNode<Key,Value>* >();
		}
		~LRUCache(){
			current_size = 0;
		}
		Value get(Key key){
			if(!page_map.has(key))	return Value(-1);
			Value val = page_map[key]->value;
			page->moveToHead(page_map[key]);
			return val;
		}
		void put(Key key, Value val){
			if(page_map.has(key)){
				page_map[key]->value = val;
				page->moveToHead(page_map[key]);
				return;
			}
			if(current_size==capacity){
				Key key = page->getBack()->key;
				page_map.remove(key);
				page->removeBackPage();
				current_size--;
			}
			doublyNode<Key,Value> *temp = page->addToHead(key,val);
			current_size++;
			page_map[key] = temp;
		}
};

#endif
