#include "ui.h"
#include "domainValidator.h"
#include "exceptionClass.h"
#include <iostream>
#include <limits>

void UserInterface::add_a_new_dog(){
    std::string breed, name, photograph_link;
    int age;

    std::cout << "Enter the breed for new dog: ";
    std::getline(std::cin >> std::ws, breed);
    std::cout << "Enter the name for new dog: ";
    std::getline(std::cin >> std::ws >> std::ws, name);

    std::string input;
    while (true) {
        std::cout << "Enter the age for new dog: " << std::flush;
        std::getline(std::cin, input);

        try {
            age = Services::convertToPositiveInt(input);
            break;
        } catch (const InvalidAgeException& error) {
            std::cout << error.what() << std::endl;
        }
    }

    std::cout << "Enter the photograph link for new dog: ";
    std::getline(std::cin >> std::ws, photograph_link);

    try {
        this->services.add_a_new_dog_function(breed, name, age, photograph_link);
        std::cout << "Operation was made successfully!" << std::endl;
    }
    catch (const AlreadyExistElement& error) {
        std::cout << error.what() << std::endl;
    }
}
void UserInterface::delete_a_dog(){
    std::string photograph_link;

    std::cout << "Enter the photograph link for the dog which you want to be deleted: ";
    std::getline(std::cin >> std::ws, photograph_link);

    try {
        this->services.delete_a_dog_function(photograph_link);
        std::cout << "Operation was made successfully!\n";
    }
    catch (const ElementDoesntExist& error) {
        std::cout << error.what() << std::endl;
    }


}
void UserInterface::update_a_dog(){
    std::string breed, name, photograph_link;
    int age;

    std::cout << "Enter the photograph link for the dog which you want to be updated: ";
    std::getline(std::cin >> std::ws, photograph_link);

    std::cout << "Enter the new breed for this dog: ";
    std::getline(std::cin >> std::ws, breed);
    std::cout << "Enter the new name for this dog: ";
    std::getline(std::cin >> std::ws, name);

    while(true) {
        std::cout << "Enter the new age for this dog: ";
        if (std::cin >> age) {
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Your input must be an integer!\n";
        }
    }

    try {
        this->services.update_a_dog_function(breed, name, age, photograph_link);
        std::cout << "Operation was made successfully!\n";
    }
    catch (const ElementDoesntExist& error) {
        std::cout << error.what() << std::endl;
    }
}
void UserInterface::list_all_dogs(){
    std::vector<Dog> printed_list = this->services.list_all_dogs_function();

    std::cout << " ~ Dogs available for adoption:\n";
    int index = 0;
    for(auto& dog : printed_list){
        std::cout << index << ". Breed: " << dog.get_breed() << "  Name: " << dog.get_name()
                  << "  Age: " << dog.get_age() << "  Photograph link: " << dog.get_photograph_link() << "\n";
        index++;
    }
}

void UserInterface::administrator_mode_menu(){
    try {
        while (true) {
            std::cout << " ~ Administrator options:\n";
            std::cout << "1. Add a new dog\n";
            std::cout << "2. Delete a dog from database\n";
            std::cout << "3. Update infos about a dog\n";
            std::cout << "4. See all dogs from shelter\n";
            std::cout << "5. Return to previous menu\n";
            std::cout << "Your option is: ";
            int option;
            if (std::cin >> option) {
                switch (option) {
                    case 1:
                        this->add_a_new_dog();
                        break;
                    case 2:
                        this->delete_a_dog();
                        break;
                    case 3:
                        this->update_a_dog();
                        break;
                    case 4:
                        this->list_all_dogs();
                        break;
                    case 5:
                        return;
                    default:
                        std::cout << "Error: Your option doesn't exist!\n";
                }
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Your input must be an integer!\n";
            }
        }
    }
    catch (ValidationException& error){
        std::cout << error.what() << std::endl;
    }
}

void UserInterface::see_the_dogs_available_for_adoption() {

    std::cout << " ~ Dogs available for adoption:\n";
    while(true){
        std::vector<Dog> printed_list = this->services.list_all_dogs_function();
        int index = 0;
        for(auto& dog : printed_list) {
            std::cout << index << ". Breed: " << dog.get_breed() << "  Name: " << dog.get_name()
                      << "  Age: " << dog.get_age() << "  Photograph link: " << dog.get_photograph_link() << "\n";

            std::string command = "start " + std::string(dog.get_photograph_link());
            system(command.c_str());

            while (true) {
                std::cout << "Do you want to adopt he? (yes/no/exit)\n";
                std::string option;
                std::getline(std::cin >> std::ws, option);
                if (option == "exit")
                    return;
                else if (option == "yes") {
                    this->services.delete_a_dog_function(dog.get_photograph_link());
                    this->services.add_a_new_dog_to_adoption_list(dog);
                    break;
                } else if (option == "no")
                    break;
                else
                    std::cout << "Error: Your option doesn't exist!\n";
            }
            index++;
        }
    }
}

void UserInterface::see_the_dogs_available_for_adoption_filtered_by_breed_and_age() {

    std::string breed;
    int age;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the breed for which dog you want to adopt: ";
    std::getline(std::cin, breed);

    if (breed.empty())
        breed = "";

    std::string input;
    while (true) {
        std::cout << "Enter the maximum age for a dog: " << std::flush;
        std::getline(std::cin, input);

        try {
            age = Services::convertToPositiveInt(input);
            break;
        } catch (const InvalidAgeException& error) {
            std::cout << error.what() << std::endl;
        }
    }

    std::cout << " ~ Dogs available for adoption filtered:\n";
    while(true){
        std::vector<Dog> printed_list = this->services.list_all_dogs_function_filtered(breed, age);
        if(printed_list.empty())
        {
            std::cout << "No dogs available with this breed and age!\n";
            return;
        }
        int index = 0;
        for(auto& dog : printed_list) {
            std::cout << index << ". Breed: " << dog.get_breed() << "  Name: " << dog.get_name()
                      << "  Age: " << dog.get_age() << "  Photograph link: " << dog.get_photograph_link() << "\n";

            std::string command = "start " + std::string(dog.get_photograph_link());
            system(command.c_str());

            while (true) {
                std::cout << "Do you want to adopt he? (yes/no/exit)\n";
                std::string option;
                std::getline(std::cin >> std::ws, option);
                if (option == "exit")
                    return;
                else if (option == "yes") {
                    this->services.delete_a_dog_function(dog.get_photograph_link());
                    this->services.add_a_new_dog_to_adoption_list(dog);
                    break;
                } else if (option == "no")
                    break;
                else
                    std::cout << "Error: Your option doesn't exist!\n";
            }
            index++;
        }
    }
}

void UserInterface::see_the_adoption_list() {

    std::vector<Dog> printed_list = this->services.list_add_dogs_from_adoption_list();

    std::cout << " ~ Dogs adopted by you:\n";
    int index = 0;
    for(auto& dog : printed_list){
        std::cout << index << ". Breed: " << dog.get_breed() << "  Name: " << dog.get_name()
                  << "  Age: " << dog.get_age() << "  Photograph link: " << dog.get_photograph_link() << "\n";
        index++;
    }


}

void UserInterface::user_mode_menu(){
    while(true) {
        std::cout << " ~ Users options:\n";
        std::cout << "1. See the dogs from database\n";
        std::cout << "2. See all the dogs of a given breed, having an age less than a given number\n";
        std::cout << "3. See the adoption list\n";
        std::cout << "4. Return to previous menu\n";
        std::cout << "Your option is: ";
        int option;
        if(std::cin >> option){
            switch (option){
                case 1:
                    this->see_the_dogs_available_for_adoption();
                    break;
                case 2:
                    this->see_the_dogs_available_for_adoption_filtered_by_breed_and_age();
                    break;
                case 3:
                    this->see_the_adoption_list();
                    break;
                case 4:
                    return;
                default:
                    std::cout << "Error: Your option doesn't exist!\n";
            }
        }
        else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Your input must be an integer!\n";
        }
    }
}

void UserInterface::program_run() {
    std::ios::sync_with_stdio(true);
    while(true) {
        std::cout << "\n  ~ Keep calm and adopt a pet ~  \n";
        std::cout << "1. Administrator mode\n";
        std::cout << "2. User mode\n";
        std::cout << "3. Close the program\n";
        std::cout << "Your option is: ";
        int option;
        if(std::cin >> option){
            switch (option){
                case 1:
                    this->administrator_mode_menu();
                    break;
                case 2:
                    this->user_mode_menu();
                    break;
                case 3:
                    std::cout << "\n  ~ Have a good day! ~  \n";
                    return;
                default:
                    std::cout << "Error: Your option doesn't exist!\n";
            }
        }
        else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Your input must be an integer!\n";
        }

    }
}

