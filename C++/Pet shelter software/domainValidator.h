#ifndef OOP_A6_7_BALAUMIHAI_DOMAINVALIDATOR_H
#define OOP_A6_7_BALAUMIHAI_DOMAINVALIDATOR_H
#include "domain.h"

class ValidationException : public std::exception
{
private:
    std::string message;

public:
    explicit ValidationException(std::string  message) : message(std::move(message)) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class domainValidator {

public:
    static void validate(const Dog& _dog);
};


#endif
