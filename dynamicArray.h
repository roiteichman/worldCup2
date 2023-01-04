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
    int m_capacity=0;// current memory capacity
    T* m_vector = nullptr;   // pointer to first data element


public:
    // Constructors
    //Vector() = default; // default constructor
    // constructor based on capacity and a default value
    Vector(int capacity, T& initial);
    explicit Vector(T initial = T{});

    // Destructor
    ~Vector() {delete[] m_vector;}

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

    return m_vector[index];
}

template<class T>
Vector<T>::Vector(T initial): m_capacity{INITIAL_SIZE},
                              m_vector{new T[INITIAL_SIZE]{}}
// allocate stack and store its pointer
{
    for (size_t i=0; i < INITIAL_SIZE; ++i)
        m_vector[i] = initial;   // initialize
}


template<class T>
Vector<T>::Vector(int capacity, T& initial): m_capacity{capacity},
                                             m_vector{new T[capacity]{}} // allocate stack and store its pointer
{
    for (size_t i=0; i < capacity; ++i)
        m_vector[i] = initial;   // initialize
}


#endif //UNTITLED_DYNAMICARRAY_H
