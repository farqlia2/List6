//
// Created by julia on 1/10/2023.
//
#pragma once
#ifndef LIST6_UNIQUEPOINTER_H
#define LIST6_UNIQUEPOINTER_H


#include <iostream>
#include "Counter.h"
#include "Globals.h"

template <typename T> class UniquePointer
{
public:
    explicit UniquePointer(T* pointer);
    UniquePointer(UniquePointer<T>&& other) noexcept;

    ~UniquePointer();

    UniquePointer<T>& operator=(UniquePointer<T>&& other);
    T& operator*();
    T* operator&();

private:
    T* pointer;
};

template <typename T>
UniquePointer<T>::UniquePointer(T* pointer) {
    this->pointer = pointer;
}
template <typename T>
UniquePointer<T>::~UniquePointer() {
    delete pointer;
}
template <typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept {
    this->pointer = other.pointer;
    other.pointer = nullptr;
}

template <typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& other) {

    this->pointer = other.pointer;
    other.pointer = nullptr;
    return *this;

}

template <typename T>
T& UniquePointer<T>::operator*() {
    return *pointer;
}

template <typename T>
T* UniquePointer<T>::operator&() {
    return pointer;
}


#endif //LIST6_UNIQUEPOINTER_H
