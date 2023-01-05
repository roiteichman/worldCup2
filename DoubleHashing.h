/**
 Lab 3 - Linear Probing, Quadratic Probing, and Double Hashing
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file DoubleHashing.hpp
 @author Russell Taylor
 @date 9/9/20
*/

#ifndef DoubleHashing_hpp
#define DoubleHashing_hpp

#include "dynamicArray.h"
#include <iostream>

#include <stdexcept>
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
    Record(const Key &key, const Value &value): key(key), value(value)
    {}
    Record(const Key &key) {
        this->key = key;
        //this->value = NULL;
    }
};


template<typename Key, typename Value>
class DoubleHashing {
public:
/**
 Constructor
 @param initialSize the initial size of the hash m_table
 @param doubleFactor factor R to be used in double hashing
 */
    DoubleHashing();

/**
 Destructor
 */
    virtual ~DoubleHashing();

/**
Puts a key-value pair into the hash m_table
@param key the key
@param value the value
*/
    void put(const Key &key, const Value &value);
    void put(Record<Key, Value> *p);
/**
Gets the value corresponding to a given key
@param key the key
@return the corresponding value
*/
    Value *get(const Key &key);

    void print();


private:
/**
 Looks up a key in the hash m_table
 @param key the key
 @return the index of the key in the hash m_table
 */
    virtual int lookUp(const Key &key, int modFactor);

    int hashIndex(const Key &key) const;

    Vector<Record<Key, Value> *>* m_table;

/**
 Hashes the key a second time
 @param key the key
 @return the hashed key
 */
    int hash2(const Key &key);
    Record<Key, Value>* initialValue;
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
 @param initialSize the initial size of the hash m_table
 @param doubleFactor factor R to be used in double hashing
 */
template<typename Key, typename Value>
DoubleHashing<Key, Value>::DoubleHashing():
        initialValue(new Record<Key, Value>(0))
{
    m_table = (new Vector<Record<Key, Value> *> (7, initialValue));
}

template<typename Key, typename Value>
void DoubleHashing<Key, Value>::put(Record<Key, Value> *p) {
    int index = lookUp(p->key, capacity);
    (*m_table)[index] = p;
}

template<typename Key, typename Value>
void DoubleHashing<Key, Value>::put(const Key &key, const Value &value) {
    // searching the index
    int index = lookUp(key, capacity);
    // check if there place in table
    if (index > m_table->size()) {
        // no place
        Vector < Record<Key, Value> * >* newTable = (new Vector < Record<Key, Value> * > (2 * capacity + 1, initialValue));
        Vector < Record<Key, Value> * >* oldTable = m_table;
        int oldSize = m_table->size();
        m_table = newTable;
        capacity = 2 * capacity + 1;
        for (int i = 0; i < oldSize; i++) {
            this->put((*oldTable)[i]);
            (*oldTable)[i] = nullptr;
        }
        this->put(key, value);
        delete oldTable;
        return;
    }
    // create new struct and push it into table
    Record<Key, Value> *p = (*m_table)[index];
    if (p->key == 0) {
        (*m_table)[index] = new Record<Key, Value>(key, value);
        size++;
    } else
        p->value = value;
}

template<typename Key, typename Value>
void DoubleHashing<Key, Value>::print() {
    for (int i = 0; i < capacity; i++) {
        if ((*m_table)[i]->key) {
            std::cout <<" "<< i  << "->" << (*m_table)[i]->key<<"\n";
        }
    }
}

template<typename Key, typename Value>
Value *DoubleHashing<Key, Value>::get(const Key &key) {
    int index = lookUp(key, capacity);
    if (index > m_table->size())
        return nullptr;

    Record<Key, Value> *p = (*m_table)[index];
    return p->key ? &(p->value) : nullptr;
}

/**
 Destructor
 */
template<typename Key, typename Value>
DoubleHashing<Key, Value>::~DoubleHashing() {
    for (int i = 0; i < m_table->size(); i++)
        if((*m_table)[i] != initialValue)
            delete (*m_table)[i];
    delete initialValue;
    delete m_table;
}

/**
 Hash index
 @param key the key
 @return the hash index of the key
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::hashIndex(const Key &key) const {
    return key % m_table->size();
}

/**
 Looks up a key in the hash m_table
 @param key the key
 @return the index of the key in the hash m_table
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::lookUp(const Key &key, int modFactor) {
    const int startIndex = this->hashIndex(key);
    int index = startIndex, i = 0;

    while (true) {
        const Record<Key, Value> *p = (*m_table)[index];
        if (p->key == 0 || p->key == key)
            return index;

        i += 1;
        index = (i * hash2(key) + startIndex) % capacity;

        if (index == startIndex)
            return int(capacity) + 1;
    }
}

/**
 Hashes the key a second time
 @param key the key
 @return the hashed key
 */
template<typename Key, typename Value>
int DoubleHashing<Key, Value>::hash2(const Key &key) {
    return 1 + (key % (m_table->size() - 1));
}




//#include "DoubleHashing-impl.h"

#endif /* DoubleHashing_hpp */
