/*
 * DoubleHashMap.hpp
 *
 * This is an interface for a hash table using Double Hashing.
 */

#ifndef DOUBLEHASHMAP_HPP_
#define DOUBLEHASHMAP_HPP_


namespace cs202
{
template<class Key, class Value>
class DoubleHashMap  : public Dictionary<Key,Value>
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
            int hashed2 = 1 + h%(TABLE_SIZE-1);
            while(flag2[hashed]!=0 && flag2[hashed]!=-1){
                 hashed = (hashed + hashed2)%TABLE_SIZE;
            if(hashed>=TABLE_SIZE2)  hashed -= TABLE_SIZE2;
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
     * Constructor: DoubleHashMap
     * Creates a Double Hash Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	DoubleHashMap(){
        flag = new int [TABLE_SIZE];
        hTable = new std::pair<Key,Value>[TABLE_SIZE];
        countFill = 0;
        for(int i=0; i<TABLE_SIZE; i++)
            flag[i] = 0;
    }
    /*
     * Constructor:DoubleHashMap
     * Creates an empty Double Hash Map with the ability to hold atleast num Key value pairs.
     */
	DoubleHashMap(const int& num){
        TABLE_SIZE = 2*num+1;
        flag = new int[TABLE_SIZE];
        hTable = new std::pair<Key,Value>[TABLE_SIZE];
        countFill = 0;
        for(int i=0; i<TABLE_SIZE; i++)
            flag[i] = 0;
    }
    /*
     * Constructor: Double Hash Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	DoubleHashMap(DoubleHashMap<Key, Value>& ht){
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
	~DoubleHashMap(){

    }
    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * DoubleHashMap<int,int> ht;
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
        int hashed2 = 1 + h%(TABLE_SIZE-1);
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key){
                    return true;
                }
            }
            hashed = (hashed + hashed2)%TABLE_SIZE;
            if(hashed==hashed_) break;
            if(hashed>=TABLE_SIZE)  hashed -= TABLE_SIZE;
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
        int hashed2 = 1 + h%(TABLE_SIZE-1);
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key){
                    flag[hashed] = -1;
                    countFill--;
                    return;
                }
            }
            hashed = (hashed + hashed2)%TABLE_SIZE;
            if(hashed==hashed_) break;
            if(hashed>=TABLE_SIZE)  hashed -= TABLE_SIZE;
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
        int hashed2 = 1 + h%(TABLE_SIZE-1);
        while(flag[hashed]!=0){
            if(flag[hashed]==1){
                if(hTable[hashed].first==key)
                    return hTable[hashed].second;
            }
            hashed = (hashed + hashed2)%TABLE_SIZE;
            if(hashed==hashed_) break;
            if(hashed>=TABLE_SIZE)  hashed -= TABLE_SIZE;
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
        int hashed2 = 1 + h%(TABLE_SIZE-1);
        if(countFill==TABLE_SIZE){
            rehash();
        }
        while(flag[hashed]!=0 && flag[hashed]!=-1){
            hashed = (hashed + hashed2)%TABLE_SIZE;
            if(hashed>=TABLE_SIZE)  hashed -= TABLE_SIZE;
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