/*
 * ChainedMap.hpp
 *
 */

#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_

#ifndef utility_
#include <utility>
#include <functional>
#endif

#include "Dictionary.hpp"

template<class T>
struct List{
    T val;
    struct List *next;
};

namespace cs202{
template<class Key, class Value>
class ChainedMap  : public Dictionary<Key, Value>
{
private:
    List<std::pair<Key,Value> > **hTable;
    int TABLE_SIZE = 100003;
    /*
     * Function rehash:
     * Resizes the hash table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();
public:
    /*
     * Constructor: ChainedMap
     * Creates a Chained Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	ChainedMap(){
        hTable = new List<std::pair<Key,Value> > *[TABLE_SIZE];
        for(int i=0; i<TABLE_SIZE; i++){
            hTable[i] = NULL;
        }
    }
    /*
     * Constructor:ChainedMap
     * Creates an empty Chained Map with the ability to hold atleast num Key value pairs.
     */
	ChainedMap(const int& num){
        hTable = new List<std::pair<Key,Value> > *[2*num+1];
        for(int i=0; i<num; i++){
            hTable[i] = NULL;
        }
        TABLE_SIZE = num;
    }
    /*
     * Constructor: Chained Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	ChainedMap(ChainedMap<Key, Value>& ht){
        bool first_time = true;
        TABLE_SIZE = ht.getSize();
        hTable = new List<std::pair<Key,Value> > *[TABLE_SIZE];
        List<std::pair<Key,Value> > *temp_ht, *temp_current;
        for(int i=0; i<TABLE_SIZE; i++){
            hTable[i] = new List<std::pair<Key,Value> >;
        }
        for(int i=0; i<TABLE_SIZE; i++){
            temp_ht = ht.hTable[i];
            temp_current = hTable[i];
            if(temp_ht==NULL){
                delete[] hTable[i];
                continue;
            }
            while(temp_ht!=NULL){
                if(!first_time)
                    temp_current = temp_current->next;
                temp_current->val = temp_ht->val;
                temp_current->next = new List<std::pair<Key,Value> >;
                temp_ht = temp_ht->next;
                first_time = false;
            }
            delete[] temp_current->next;
            temp_current->next = NULL;
        }
    }
    /*
     * Destructor
     * Deletes the memory acquired by the given Hash Map.
     */
	~ChainedMap(){
        // for(int i=0; i<TABLE_SIZE; i++){
        //     delete[] hTable[i];
        // }
        // delete[] hTable;
    }



    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * ChainedHashMap<int,int> ht;
     * ht[1] = 2;
     * ht[1] = 4;
     * ht[2] = 3;
     */
    Value something;
    Value& operator[](const Key& key){
        if(!has(key))
            put(key,something);
        return get(key);
    }


    bool has(const Key& key){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        List<std::pair<Key,Value> > *temp = hTable[hashed];
        while(temp!=NULL){
            if(temp->val.first==key)    return true;
        }
        return false;
    }

    
    void remove(const Key& key){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        List<std::pair<Key,Value> > *temp = hTable[hashed];
        List<std::pair<Key,Value> > *temp_back = hTable[hashed];
        if(temp==NULL)  return;
        while(temp!=NULL){
            if(temp->val.first==key){
                if(temp==temp_back){
                    hTable[hashed] = temp->next;
                }
                else{
                    temp_back->next = temp->next;
                }
                temp->next = NULL;
                delete[] temp;
                return;
            }
            if(temp != temp_back){
                temp_back = temp_back->next;
            }
            temp = temp->next;
        }
    }

    
    Value& get(const Key& key){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        List<std::pair<Key,Value> > *temp = hTable[hashed];
        while(temp!=NULL){
            if(temp->val.first==key)    return temp->val.second;
            temp = temp->next;
        }
        throw "key not found";
    }

    
    void put(const Key& key, const Value& value){
        bool found = false;
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        List<std::pair<Key,Value> > *temp = hTable[hashed];
        if(temp==NULL){
            hTable[hashed] = new List<std::pair<Key,Value> >;
            temp = hTable[hashed];
            temp->val = std::make_pair(key, value);
            temp->next = NULL;
        }
        else{
            while(1){
                if(temp->val.first==key){
                    found = true;
                    break;
                }
                if(temp->next==NULL){
                    break;
                }
                temp = temp->next;
            }
            if(!found){
                temp->next = new List<std::pair<Key,Value> >;
                temp = temp->next;
            }
            temp->val = std::make_pair(key, value);
            if(!found){
                temp->next = NULL;
            }
        }
    }

    inline int getSize(){
        return TABLE_SIZE;
    }
};

}
#endif /* CHAINEDMAP_HPP_ */


