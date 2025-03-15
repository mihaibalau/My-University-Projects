#include <fstream>
#include "repository.h"
#include "exceptionClass.h"
#include <windows.h>
#include <string>
#include <vector>

/*
 * Construct the repository with 20 elements slots default
 */

void Repository::search_for_a_pet(const Dog& new_dog) {
    for (auto& dog : this->database)
        if (dog == new_dog)
            throw AlreadyExistElement("Error: This link already exist for a dog!");
}


/*
 * Get an element as a parameter and add it
 * at the end of the current elements array.
 * Return true if the add was did successfully
 * Return false if there already exist an element with that photograph link
 */
void Repository::add_a_new_dog_in_repository(const Dog& new_dog){

    this->search_for_a_pet(new_dog);
    this->database.push_back(new_dog);
    this->save_to_file_database(this->shelter_file_name);

}

/*
 * Get as parameter a photograph link and search for it inside vector elements.
 * Return true if it was found and the element which have it was removed, else false.
 */
void Repository::remove_a_dog_from_repository(const std::string& photograph_link){

    auto it = std::remove_if(this->database.begin(), this->database.end(), [photograph_link](const Dog& dog){
        return dog.get_photograph_link() == photograph_link;
    });
    if (it == database.end())
        throw ElementDoesntExist("Error: Imputed photograph link wasn't found for any dog!");

    database.erase(it, database.end());
    this->save_to_file_database(this->shelter_file_name);
}

/*
 * Get a new created element which need to have same
 * photograph id as an existing element inside vector.
 * If it has, the new element is replaced with this and return true.
 * If that link doesn't exist inside repository, its return false.
 */
void Repository::update_a_dog_from_repository(Dog& updated_dog){

    auto hasSamePhotographLink = [updated_dog](const Dog& dog) {
        return dog == updated_dog;
    };

    auto it = std::find_if(this->database.begin(), this->database.end(), hasSamePhotographLink);

    if (it == database.end())
        throw ElementDoesntExist("Error: Imputed photograph link wasn't found for any dog!");

    *it = updated_dog;
    this->save_to_file_database(this->shelter_file_name);
}

/*
 * Return dynamic array class with Dog class elements.
 */
std::vector<Dog> Repository::get_all_dogs_from_repository(){
    return this->database;
}

void Repository::save_to_file_database(const std::string &filename) {
    std::ofstream file(filename);

    if(file.is_open()) {
        for (const auto &dog: database)
            file << dog;
        file.close();
    }
}

void Repository::load_from_file_database(const std::string &filename) {
    std::ifstream file(filename);
    if(file.is_open()){
        database.clear();
        Dog dog;
        while(file >> dog)
            database.push_back(dog);
        file.close();
    }

}

void Repository::clear_data_base() {
    this->database.clear();
    this->shelter_file_name = "tests.db";
}


//////////


/*
 * Call the add function from templated array to add a new dog.
 */
void UserRepository::add_a_new_dog_in_adoption_list(const Dog& new_dog) {
    this->adoption_list.push_back(new_dog);
}

void UserRepository::load_from_file_user_database(const std::string &filename) {
    std::ifstream file(filename);
    if(file.is_open()){
        adoption_list.clear();
        Dog dog;
        while(file >> dog)
            adoption_list.push_back(dog);
        file.close();
    }
}

void UserRepository::clear_data_base() {
    this->adoption_list.clear();
}


//////////


void TxtUserRepository::save_to_file_user_database(const std::string &filename) {
    std::ofstream file(filename);

    if(file.is_open()) {
        for (const auto &dog: adoption_list)
            file << dog;
        file.close();
    }
}

std::vector<Dog> TxtUserRepository::get_all_dogs_from_adoption_list() {
    this->save_to_file_user_database(this->user_file_name);
    return this->adoption_list;
}

void HtmlUserRepository::save_to_file_user_database(const std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "<!DOCTYPE html> <html> <head> <title> Movie WatchList</title> </head > <body> <table border=\1\>";
        file << "<tr> <td> Title </td> <td> Presenter </td> <td> Duration </td> <td> Likes </td> <td> Link </td> </tr>";
        for (const auto &dog: this->adoption_list){
             file << "<tr> <td>" << dog.get_breed() << "</td> <td>" << dog.get_name() << "</td> <td>"
                 << dog.get_age() << "</td> <td> <a href=\"" << dog.get_photograph_link() << "\"> Link</a></ td> </tr>";
        }
        file << "</table>\n"
                "</body>\n"
                "</html>";
    }
}

std::vector<Dog> HtmlUserRepository::get_all_dogs_from_adoption_list() {

    this->save_to_file_user_database(this->user_file_name);

    std::wstring user_file_name_wide(user_file_name.begin(), user_file_name.end());
    ShellExecuteW(NULL, L"open", user_file_name_wide.c_str(), NULL, NULL, SW_SHOWNORMAL);

    return this->adoption_list;
}

void CsvUserRepository::save_to_file_user_database(const std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open())
        for (const auto &dog: this->adoption_list){
            file << dog.get_breed() << ",";
            file << dog.get_name() << ",";
            file << dog.get_age() << ",";
            file << dog.get_photograph_link() << "\n";
        }
    file.close();
}

std::vector<Dog> CsvUserRepository::get_all_dogs_from_adoption_list() {

    this->save_to_file_user_database(this->user_file_name);

    std::string path = this->user_file_name;
    std::string command = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" ";
    command += path;
    system(command.c_str());

    return this->adoption_list;
}
