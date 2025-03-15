#include "domainValidator.h"
#include "domain.h"

void domainValidator::validate(const Dog& _dog) {
    std::string errors;
    if(_dog.get_age() <= 0)
        errors += std::string("Error: The age can't be a positive number\n");
    if(_dog.get_photograph_link().size() <= 3)
        errors += std::string("Error: The photograph link is too short!\n");
    if(_dog.get_name().size() <= 2)
        errors += std::string("Error: The dog's name is too short!\n");
    if(_dog.get_breed().size() <= 2)
        errors += std::string("Error: The dog's breed is too short!\n");

    if(!errors.empty())
        throw ValidationException(errors);
}
