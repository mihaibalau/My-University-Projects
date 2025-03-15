#ifndef OOP_A6_7_BALAUMIHAI_EXCEPTIONCLASS_H
#define OOP_A6_7_BALAUMIHAI_EXCEPTIONCLASS_H

#include <exception>
#include <string>
#include <utility>

class InvalidAgeException : public std::exception {

private:
    std::string message;

public:
    explicit InvalidAgeException(std::string  message)  : message(std::move(message)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }

};

class AlreadyExistElement : public std::exception {

private:
    std::string message;

public:
    explicit AlreadyExistElement(std::string  message) : message(std::move(message)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }

};

class ElementDoesntExist : public std::exception {

private:
    std::string message;

public:
    explicit ElementDoesntExist(std::string  message) : message(std::move(message)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }

};


#endif
