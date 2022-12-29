/**
 Lab 3 - Linear Probing, Quadratic Probing, and Double Hashing
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file DoubleHashing.hpp
 @author Russell Taylor
 @date 9/9/20
*/

#ifndef
DoubleHashing_hpp
#define
        DoubleHashing_hpp

#include

"dynamicArray.h"

#include

<stdexcept>
///TODO: check if we are allowed to use stdexcept


template<typename Key, typename Value>
struct Record {
    Key key;
    Value value;

/**
 Constructor
 @param key the record key
 @param value the record value
 */
    Record(const Key &key, const Value &value) {
        this->key = key;
        this->value = value;
    }
};


template<typename Key, typename Value>
class DoubleHashing {
public:
/**
 Constructor
 @param initialSize the initial size of the hash table
 @param doubleFactor factor R to be used in double hashing
 */
    DoubleHashing();

/**
 Destructor
 */
    ~DoubleHashing();

/**
Puts a key-value pair into the hash table
@param key the key
@param value the value
*/
    void put(const Key &key, const Value &value);

/**
Gets the value corresponding to a given key
@param key the key
@return the corresponding value
*/
    Value *get(const Key &key);

    void print();


private:
/**
 Looks up a key in the hash table
 @param key the key
 @return the index of the key in the hash table
 */
    virtual int lookUp(const Key &key, int modFactor);

    int hashIndex(const Key &key) const;

    Vector<Record<Key, Value> *> table;

/**
 Hashes the key a second time
 @param key the key
 @return the hashed key
 */
    int hash2(const Key &key);

    int capacity = 7;
    int size = 0;

};

/**
 Gets the value corresponding to a given key
 @param key the key
 @return the corresponding value
 */



/**
 Constructor
 @param initialSize the initial size of the hash table
 @param doubleFactor factor R to be used in double hashing
 */
template<typename Key, typename Value>
DoubleHashing<Key, Value>::DoubleHashing() {
}


template<typename Key, typename Value>
void DoubleHashing<Key, Value>::put(const Key &key, const Value &value) {
    int index = lookUp(key, capacity);

    if (index > table.size()) {
///TODO
        Record<Key, Value> p(0, 0);
        Vector < Record<Key, Value> * > helpTable(2 * capacity + 1, &p);
        Vector < Record<Key, Value> * > helpTable2 = table;
        int tempSize = size;
        table = helpTable;
        capacity = 2 * capacity + 1;
        for (int i = 0; i < tempSize; i++)
            this->put(helpTable2[i]->key, helpTable2[i]->value);
        this->put(key, value);
        return;
    }

    Record<Key, Value> *p = table[index];
    if (p == nullptr) {
        table[index] = new Record<Key, Value>(key, value);
        size++;
    } else
        p->value = value;
}

template<typename Key, typename Value>
void DoubleHashing<Key, Value>::print() {
    for (int i = 0; i < size; i++) {
        if (table[i]->key)
            std::cout << table[i]->key;
    }
}

template<typename Key, typename Value>
Value *DoubleHashing<Key, Value>::get(const Key &key) {
    int index = lookUp(key, capacity);
    if (index > table.size())
        return nullptr;

    Record<Key, Value> *p = table[index];
    return p ? &(p->value) : nullptr;
}

/**
 Destructor
 */
template<typename Key, typename Value>
DoubleHashing<Key, Value>::~DoubleHashing() {
    for (int i = 0; i < table.size(); i++)
        if (table[i])
            delete table[i];
}

/**
 Hash index
 @param key the key
 @return the hash index of the key
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::hashIndex(const Key &key) const {
    return key % table.size();
}

/**
 Looks up a key in the hash table
 @param key the key
 @return the index of the key in the hash table
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::lookUp(const Key &key, int modFactor) {
    const int startIndex = this->hashIndex(key);
    int index = startIndex, i = 0;

    while (true) {
        const Record<Key, Value> *p = this->table[index];
        if (p->key == 0 || p->key == key)
            return index;

        i += 1;
        index = (i * hash2(key) + startIndex) % modFactor;

        if (index == startIndex)
            return int(modFactor) + 1;
    }
}

/**
 Hashes the key a second time
 @param key the key
 @return the hashed key
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::hash2(const Key &key) {
    return 1 + (key % table.size() - 1);
}




//#include "DoubleHashing-impl.h"

#endif /* DoubleHashing_hpp */
