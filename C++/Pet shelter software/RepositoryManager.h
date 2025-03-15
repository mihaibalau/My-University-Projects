#ifndef OOP_A6_7_BALAUMIHAI_REPOSITORYMANAGER_H
#define OOP_A6_7_BALAUMIHAI_REPOSITORYMANAGER_H

#include <iostream>
#include "exceptionClass.h"

class RepositoryManager {
private:
    static void print_option() {
        std::cout << "What kind of file for storing adoption list do you want to use?\n";
        std::cout << "1. Txt File\n";
        std::cout << "2. HTML File \n";
        std::cout << "3. CSV File\n";
    }
public:
    static int select_type(){

        RepositoryManager::print_option();
        int option;
        std::string input;

        while (true) {

            try {

                std::cout << "Enter an option (1 or 2): ";
                std::getline(std::cin, input);

                option = std::stoi(input);
                if (option < 1 || option > 3) {
                    throw std::out_of_range("Error: Option must be 1, 2 or 3!");
                }
                std::cout << "Option selected: " << option << std::endl;
                return option;

            } catch (const std::invalid_argument& error) {
                std::cout << "Error: Invalid input! Please enter a number.\n";

            } catch (const std::out_of_range& error) {
                std::cout << error.what() << std::endl;
            }
        }
    }
};



#endif //OOP_A6_7_BALAUMIHAI_REPOSITORYMANAGER_H
