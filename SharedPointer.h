//
// Created by julia on 1/16/2023.
//

#ifndef LIST6_SHAREDPOINTER_H
#define LIST6_SHAREDPOINTER_H

#include <iostream>
#include "Counter.h"
#include "Globals.h"

template <typename T> class SharedPointer
{
public:
    explicit SharedPointer(T* pointer);
    SharedPointer(const SharedPointer<T>& other);
    SharedPointer(SharedPointer<T>&& other) noexcept ;
    ~SharedPointer();

    SharedPointer<T>& operator=(const SharedPointer<T>& other);
    T& operator*();
    T* operator&();
private:
    void copy(const SharedPointer<T>& other);
    T* pointer;
    Counter* counter;
    void clear();
};



template <typename T>
SharedPointer<T>::SharedPointer(T* pointer) {
    this->pointer = pointer;
    this->counter = new Counter();
    counter->incr();
    if (DEBUG) std::cout << "copy " << counter->get() << "\n";
}
template <typename T>
void SharedPointer<T>::clear() {
    if (counter->decr() <= 0) {
        if (DEBUG) std::cout << "delete entries\n";
        delete pointer;
        delete counter;
    }
}

template <typename T>
void SharedPointer<T>::copy(const SharedPointer<T>& other){
    this->pointer = other.pointer;
    this->counter = other.counter;
    counter->incr();
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    if (DEBUG) std::cout << "delete " << counter->get() << "\n";
    clear();
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other){
    copy(other);
}
template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer<T>&& other) noexcept{

    this->counter = other.counter;
    this->pointer = other.pointer;
    other.counter = new Counter();
    other.pointer = nullptr;

}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other) {

    if (&other != this) {
        clear();
        copy(other);
    }
    return *this;

}

template <typename T>
T& SharedPointer<T>::operator*() {
    return *pointer;
}

template <typename T>
T* SharedPointer<T>::operator&() {
    return pointer;
}

#endif //LIST6_SHAREDPOINTER_H
