#ifndef OOP_A6_7_BALAUMIHAI_SERVICES_H
#define OOP_A6_7_BALAUMIHAI_SERVICES_H

#include "repository.h"

class Services {

private:
    Repository repository;
    UserRepository* userRepository;

public:
    explicit Services(Repository& linked_repository, UserRepository* linked_user_repository)
            : repository(linked_repository), userRepository(linked_user_repository) {};

    ~Services() {
        delete userRepository;
    }

    void add_a_new_dog_function(std::string breed, std::string name, int age, std::string photograph_link);
    void delete_a_dog_function(const std::string& photograph_link);
    void update_a_dog_function(std::string new_breed, std::string new_name, int new_age, std::string photograph_link);
    std::vector<Dog> list_all_dogs_function();
    void initialize_repository();
    static int convertToPositiveInt(const std::string& input);

    void add_a_new_dog_to_adoption_list(const Dog& new_dog);
    std::vector<Dog> list_add_dogs_from_adoption_list();
    std::vector<Dog> list_all_dogs_function_filtered(const std::string& breed, int age);
};

#endif
