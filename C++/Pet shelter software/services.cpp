#include <sstream>
#include "services.h"
#include "domain.h"
#include "exceptionClass.h"
#include "domainValidator.h"

/*
 * This function get as parameters the fields to register a new dog,
 * and call the function from repository to add this new objected created.
 * It returns true if add was did successfully, else return 0.
 * 0 mean exist inside the repository an object with that photograph link
 */
void Services::add_a_new_dog_function(std::string breed, std::string name, int age, std::string photograph_link){
    Dog new_dog = Dog{breed, name, age, photograph_link};
    domainValidator::validate(new_dog);
    this->repository.add_a_new_dog_in_repository(new_dog);
}

/*
 * This function get as parameter the identifier, here photograph link
 * for a dog and call the function from repository to remove it from database.
 * It returns true if add was did successfully, else return 0.
 * 0 mean that object wasn't found inside the repository
 */
void Services::delete_a_dog_function(const std::string& photograph_link){
    this->repository.remove_a_dog_from_repository(photograph_link);
}

/*
 * This function get as parameters new data for a dog from database,
 * create a new object with that dates and send it to be updated inside the database.
 * It returns true if add was did successfully, else return 0.
 * 0 mean that object wasn't found inside the repository
 */
void Services::update_a_dog_function(std::string new_breed, std::string new_name, int new_age, std::string photograph_link){
    Dog updated_dog = Dog{new_breed, new_name, new_age, photograph_link};
    domainValidator::validate(updated_dog);
    this->repository.update_a_dog_from_repository(updated_dog);
}

/*
 * This function call a function from repository to get the array with
 * all objects and return it to print functions.
 */
std::vector<Dog> Services::list_all_dogs_function(){
    return this->repository.get_all_dogs_from_repository();
}

/*
 * Generate 10 objects at startup to be inside the database.
 */
void Services::initialize_repository() {
    this->add_a_new_dog_function("Great Dane", "Scooby Doo", 7 , "https://imgur.com/uFvuZx7");
    this->add_a_new_dog_function("Husky", "Aky", 10 , "https://imgur.com/zPXxvQ5");
    this->add_a_new_dog_function("Rough Collie", "Lassie", 7 , "https://imgur.com/VV7ATob");
    this->add_a_new_dog_function("German Shepard", "Max", 4 , "https://imgur.com/hQrG4U3");
    this->add_a_new_dog_function("Husky", "Leo", 6 , "https://imgur.com/eLBBloz");
    this->add_a_new_dog_function("Rottweiler", "Puffy", 4 , "https://imgur.com/Tbys1bj");
    this->add_a_new_dog_function("German Shepard", "Josh", 4 , "https://imgur.com/35jWrLi");
    this->add_a_new_dog_function("Akita", "Ham", 9 , "https://imgur.com/aN6yDY3");
    this->add_a_new_dog_function("Husky", "Max", 2 , "https://imgur.com/4K0zb7K");
    this->add_a_new_dog_function("Great Pyrenees", "Casper", 10 , "https://imgur.com/BMc8bWT");
    this->add_a_new_dog_function("Czechoslovakian wolf", "Bob", 3 , "https://imgur.com/A3WDfmI");
}
/*
 * This function call a function from repository to add
 * a dog, get and send as parameter, to the adoption list of a user.
 */
void Services::add_a_new_dog_to_adoption_list(const Dog& new_dog) {
    this->userRepository->add_a_new_dog_in_adoption_list(new_dog);
}

/*
 * This function call a from repository function to get
 * the adoption list and return it as a dynamic array.
 */
std::vector<Dog> Services::list_add_dogs_from_adoption_list() {
    return this->userRepository->get_all_dogs_from_adoption_list();
}

/*
 * This function call a function from repository to get
 * all available dogs for adoption in a new created array.
 * Then, this array is filtered to contain the dogs which have
 * a specific breed, get as parameter, and the age lower than
 * a number, get also as parameter.
 * The function return the filtered array to be printed.
 */
std::vector<Dog> Services::list_all_dogs_function_filtered(const std::string& breed, int age) {
    if(breed.empty())
        return this->repository.get_all_dogs_from_repository();

    else {
        std::vector<Dog> returned_list = this->repository.get_all_dogs_from_repository();
        Dog updated_dog;
        updated_dog.set_breed(breed);
        updated_dog.set_age(age);

        auto need_to_be_removed = [updated_dog](const Dog& dog) {
            return !(dog.get_breed() == updated_dog.get_breed() && dog.get_age() < updated_dog.get_age());
        };

        auto it = std::remove_if(returned_list.begin(), returned_list.end(), need_to_be_removed);
        std::vector<Dog> dogsToDeleted(it, returned_list.end());

        returned_list.erase(it, returned_list.end());
        return returned_list;
    }
}

int Services::convertToPositiveInt(const std::string &input) {
    int age;
    std::stringstream ss(input);

    if (!(ss >> age) || age <= 0) {
        throw InvalidAgeException("Error: Your input must be a positive integer!");
    }

    return age;
}
