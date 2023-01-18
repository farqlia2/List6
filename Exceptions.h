//
// Created by julia on 1/16/2023.
//

#ifndef LIST6_EXCEPTIONS_H
#define LIST6_EXCEPTIONS_H

#include <exception>
#include <utility>
#include <string>

using namespace std;

class IOException : public std::exception {
public:
    explicit IOException(string&& message) : message(std::move(message)) {};

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    const string message;
};

class BadFormattingException : public std::exception {
public:
    explicit BadFormattingException(string&& message) : message(std::move(message)) {};

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    const string message;
};

class IllegalArgumentException : public std::exception {
public:
    explicit IllegalArgumentException(string&& message) : message(std::move(message)) {};

    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    const string message;
};

#endif //LIST6_EXCEPTIONS_H
