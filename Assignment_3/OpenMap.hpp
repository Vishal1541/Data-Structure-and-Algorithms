/*
 * OpenMap.hpp
 *
 *This is a Hash Table interface using Linear Probing
 */

#ifndef OPENMAP_HPP_
#define OPENMAP_HPP_

#ifndef utility_
#include <utility>
#include <functional>
#endif

#include "Dictionary.hpp"

namespace cs202
{
template<class Key, class Value>
class OpenMap  : public Dictionary<Key,Value>
{
private:
    int TABLE_SIZE = 100003;
    std::pair<Key,Value> *hTable=NULL;
    int *flag=NULL, countFill;
    /*
     * Function rehash:
     * Resizes the has table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash(){
        int TABLE_SIZE2 = TABLE_SIZE*2+1;
        std::pair<Key,Value> *hTable2 = new std::pair<Key,Value>[TABLE_SIZE2], old;
        int *flag2 = new int[TABLE_SIZE2];
        for(int i=0; i<TABLE_SIZE2; i++)
            flag2[i] = 0;
        for(int i=0; i<TABLE_SIZE; i++){
            old = hTable[i];
            std::size_t h = std::hash<Key>{}(old.first);
            int hashed = h%TABLE_SIZE2;
            while(flag2[hashed]!=0 && flag2[hashed]!=-1){
                hashed++;
                if(hashed==TABLE_SIZE2)  hashed = 0;
            }
            hTable2[hashed] = std::make_pair(old.first, old.second);
            flag2[hashed] = 1;
        }
        delete[] hTable;
        delete[] flag;
        hTable = hTable2;
        flag = flag2;
    }
public:
    /*
     * Constructor: OpenMap
     * Creates a Open Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	OpenMap(){
        flag = new int [TABLE_SIZE];
        hTable = new std::pair<Key,Value>[TABLE_SIZE];
        countFill = 0;
        for(int i=0; i<TABLE_SIZE; i++)
            flag[i] = 0;
    }
    /*
     * Constructor:OpenMap
     * Creates an empty Open Map with the ability to hold atleast num Key value pairs.
     */
	OpenMap(const int& num){
        TABLE_SIZE = 2*num+1;
        flag = new int[TABLE_SIZE];
        hTable = new std::pair<Key,Value>[TABLE_SIZE];
        countFill = 0;
        for(int i=0; i<TABLE_SIZE; i++)
            flag[i] = 0;
    }
    /*
     * Constructor: Open Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	OpenMap(OpenMap<Key, Value>& ht){
        TABLE_SIZE = ht.getSize();
        flag = new int[TABLE_SIZE];
        hTable = new std::pair<Key,Value>[TABLE_SIZE];
        countFill = 0;
        for(int i=0; i<TABLE_SIZE; i++){
            flag[i] = ht.flag[i];
            if(flag[i]==1){
                hTable[i] = ht.hTable[i];
            }
        }
    }
    /*
     * Destructor
     * Deletes the memory acquired by the given Hash Map.
     */
	~OpenMap(){
        // delete[] hTable;
        // delete[] flag;
    }
    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * OpenMap<int,int> ht;
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
        int hashed_ = hashed;
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key){
                    return true;
                }
            }
            hashed++;
            if(hashed==hashed_) break;
            if(hashed==TABLE_SIZE)  hashed = 0;
        }
        return false;
    }
    /*
     * Function : remove
     * Removes the given key and the corresponding value from the Dictionary if the key is in the dictionary.
     * Does nothing otherwise.
     */
    void remove(const Key& key){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        int hashed_ = hashed;
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key){
                    flag[hashed] = -1;
                    countFill--;
                    return;
                }
            }
            hashed++;
            if(hashed==hashed_) break;
            if(hashed==TABLE_SIZE)  hashed = 0;
        }
        throw "no key found";
    }
    /*
     * Function : get
     * Returns the value associated with the given key.
     * Raises an exception if the key does'nt exist in the dictionary.
     */
    Value& get(const Key& key){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        int hashed_ = hashed;
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key)
                    return hTable[hashed].second;
            }
            hashed++;
            if(hashed==hashed_) break;
            if(hashed==TABLE_SIZE)  hashed = 0;
        }
        throw "key not found";
    }
    /*
     * Function : put
     * If the key does'nt exist in the dictionary, then insert the given key and value in the dictionary.
     * Otherwise change the value associated with the key to the given value.
     */
    void put(const Key& key, const Value& value){
        std::size_t h = std::hash<Key>{}(key);
        int hashed = h%TABLE_SIZE;
        if(countFill==TABLE_SIZE){
            rehash();
        }
        while(flag[hashed]!=0 && flag[hashed]!=-1){
            hashed++;
            if(hashed==TABLE_SIZE)  hashed = 0;
        }
        hTable[hashed] = std::make_pair(key, value);
        flag[hashed] = 1;
        countFill++;
    }

    int getSize(){
        return TABLE_SIZE;
    }
};
}

#endif 