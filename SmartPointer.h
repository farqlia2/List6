//
// Created by julia on 1/10/2023.
//

#ifndef LIST6_SMARTPOINTER_H
#define LIST6_SMARTPOINTER_H


#pragma once
#include <iostream>
#include "Counter.h"
#include "Globals.h"

template <typename T> class SmartPointer
{
public:
    SmartPointer(T pointer[]);

    ~SmartPointer();

    void operator=(const SmartPointer& other);
    T& operator*();
    T* operator&();
private:
    T* pointer;
    Counter* counter;
    void clear();
};



template <typename T>
SmartPointer<T>::SmartPointer(T pointer[]) {
    this->pointer = pointer;
    this->counter = new Counter();
    counter->incr();
    if (DEBUG) std::cout << "create " << counter->get() << "\n";
}
template <typename T>
void SmartPointer<T>::clear() {
    if (counter->decr() == 0) {
        if (DEBUG) std::cout << "delete entries\n";
        delete[] pointer;
        delete counter;
    }
}

template <typename T>
SmartPointer<T>::~SmartPointer() {
    if (DEBUG) std::cout << "delete " << counter->get() << "\n";
    clear();
}

template <typename T>
void SmartPointer<T>::operator=(const SmartPointer& other) {

    if (&other != this) {
        clear();
        this->pointer = other.pointer;
        this->counter = other.counter;
        counter->incr();
    }

}

template <typename T>
T& SmartPointer<T>::operator*() {
    return *pointer;
}

template <typename T>
T* SmartPointer<T>::operator&() {
    return pointer;
}


#endif //LIST6_SMARTPOINTER_H
