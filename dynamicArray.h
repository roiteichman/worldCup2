//
// Created by shlom on 28/12/2022.
//

#ifndef UNTITLED_DYNAMICARRAY_H
#define UNTITLED_DYNAMICARRAY_H
#include <math.h>
#include <stdexcept>

const int INITIAL_SIZE=7;

template<class T> class Vector {

    void reserve(const int capacity);
    T* vector_ = nullptr;   // pointer to first data element
    int m_capacity=0;// current memory capacity

public:
    // Constructors
    //Vector() = default; // default constructor
    // constructor based on capacity and a default value
    Vector(int capacity, T& initial);
    explicit Vector(T initial = T{});

    // Destructor
    ~Vector() {delete[] vector_;}

    // Element read/write access
    T& operator[](const int index); // return element reference at index
    int size() const
    {
        return this->m_capacity;
    }
};



// Element read/write access
template<class T>
T& Vector<T>::operator[](const int index)
{
    if (index >= m_capacity)
        throw std::invalid_argument("Index must be less than vector's size");

    return vector_[index];
}

template<class T>
Vector<T>::Vector(T initial): m_capacity{INITIAL_SIZE},
vector_{new T[INITIAL_SIZE]{}}
// allocate stack and store its pointer
{
    for (size_t i=0; i < INITIAL_SIZE; ++i)
        vector_[i] = initial;   // initialize
}


template<class T>
Vector<T>::Vector(int capacity, T& initial): m_capacity{capacity},
                                               vector_{new T[capacity]{}} // allocate stack and store its pointer
{
    for (size_t i=0; i < capacity; ++i)
        vector_[i] = initial;   // initialize
}


#endif //UNTITLED_DYNAMICARRAY_H
