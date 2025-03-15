#include "tests.h"
#include "domain.h"
#include "repository.h"
#include "services.h"
#include <cassert>

void Tests::test_domain() {

    std::string breed = "Breed";
    std::string name = "Name";
    int age = 5;
    std::string link = "link";
    Dog test_dog = Dog{breed, name, age, link};
    assert(test_dog.get_name() == "Name");
    assert(test_dog.get_breed() == "Breed");
    assert(test_dog.get_age() == 5);
    assert(test_dog.get_photograph_link() == "link");

    Dog test_dog2{};
    test_dog2.set_name("New Name");
    test_dog2.set_breed("New Breed");
    test_dog2.set_age(10);
    test_dog2.set_photograph_link("new link");

    assert(test_dog2.get_name() == "New Name");
    assert(test_dog2.get_breed() == "New Breed");
    assert(test_dog2.get_age() == 10);
    assert(test_dog2.get_photograph_link() == "new link");

}

void Tests::test_repository() {
    Repository database;
    UserRepository userRepository;
    database.clear_data_base();
    userRepository.clear_data_base();

    std::string breed = "Akita";
    std::string name = "Doge";
    int age = 10;
    std::string link = "link";
    Dog new_dog = Dog{breed, name, age, link};

    breed = "Pitbull";
    name = "Atodiresei";
    age = 8;
    link = "link2";
    Dog new_dog2 = Dog{breed, name, age, link};

    breed = "Bison";
    name = "Constantin";
    age = 15;
    link = "link3";
    Dog new_dog3 = Dog{breed, name, age, link};
    database.add_a_new_dog_in_repository(new_dog);
    database.add_a_new_dog_in_repository(new_dog2);
    database.add_a_new_dog_in_repository(new_dog3);
    database.remove_a_dog_from_repository("link2");
    userRepository.add_a_new_dog_in_adoption_list(new_dog2);

    breed = "Labrador";
    name = "Robert";
    age = 9;
    link = "link3";
    Dog new_dog3_updated{breed, name, age, link};
    database.update_a_dog_from_repository(new_dog3_updated);

    std::vector<Dog> test_array;
    test_array = database.get_all_dogs_from_repository();

    assert(test_array[0].get_name() == "Doge");
    assert(test_array[1].get_breed() == "Labrador");
    assert(test_array[0].get_age() == 10);
    assert(test_array[1].get_photograph_link() == "link3");

    database.remove_a_dog_from_repository("link3");
    userRepository.add_a_new_dog_in_adoption_list(new_dog3);
    test_array = userRepository.get_all_dogs_from_adoption_list();
    assert(test_array[0].get_name() == "Atodiresei");
    assert(test_array[1].get_breed() == "Bison");
    assert(test_array[0].get_age() == 8);
    assert(test_array[1].get_photograph_link() == "link3");
    assert(test_array.size() == 2);

}

void Tests::test_services() {

    Repository database;
    UserRepository userRepository;
    userRepository.clear_data_base();
    database.clear_data_base();

    Services services(database, userRepository);

    services.add_a_new_dog_function("Akita", "Doge", 10, "link");
    services.add_a_new_dog_function("Pitbull", "Atodiresei", 8, "link2");
    services.add_a_new_dog_function("Bison", "Constantin", 15, "link3");
    services.delete_a_dog_function("link2");
    services.update_a_dog_function("Labrador", "Robert", 9, "link3");

    std::vector<Dog> test_array;
    test_array = services.list_all_dogs_function();

    assert(test_array[0].get_name() == "Doge");
    assert(test_array[1].get_breed() == "Labrador");
    assert(test_array[0].get_age() == 10);
    assert(test_array[1].get_photograph_link() == "link3");

    test_array = services.list_add_dogs_from_adoption_list();
    assert(test_array.empty());

    std::string breed = "Akita";
    std::string name = "Doge";
    int age = 10;
    std::string link = "link";
    Dog new_dog = Dog{breed, name, age, link};
    services.add_a_new_dog_to_adoption_list(new_dog);

    test_array = services.list_all_dogs_function_filtered("", 5);
    assert(test_array.size() == 2);

    std::string check_string;
    check_string = "Akita";
    test_array = services.list_all_dogs_function_filtered(check_string, 11);
    assert(test_array.size() == 1);

    test_array = services.list_all_dogs_function_filtered("Akita", 10);
    assert(test_array.empty());

}

void Tests::run_tests() {
    this->test_domain();
    this->test_services();
    this->test_repository();
}
