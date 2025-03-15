#ifndef OOP_A6_7_BALAUMIHAI_REPOSITORY_H
#define OOP_A6_7_BALAUMIHAI_REPOSITORY_H

#include "domain.h"
#include <vector>
#include <algorithm>

class Repository {

private:
    std::vector<Dog> database;

public:
    std::string shelter_file_name = "shelter.db";
    Repository() {
        this->load_from_file_database(this->shelter_file_name);
    };

    void search_for_a_pet(const Dog& new_dog);
    void add_a_new_dog_in_repository(const Dog& new_dog);
    void remove_a_dog_from_repository(const std::string& photograph_link);
    void update_a_dog_from_repository(Dog& updated_dog);
    std::vector<Dog> get_all_dogs_from_repository();
    void clear_data_base();

    void save_to_file_database(const std::string &file);
    void load_from_file_database(const std::string &file);

};

class UserRepository{

protected:
    std::vector<Dog> adoption_list;

public:
    UserRepository() = default;
    virtual ~UserRepository() = default;
    virtual void save_to_file_user_database(const std::string &file) = 0;
    virtual std::vector<Dog> get_all_dogs_from_adoption_list() = 0;

    void load_from_file_user_database(const std::string &file);
    void add_a_new_dog_in_adoption_list(const Dog& new_dog);
    void clear_data_base();
};

class TxtUserRepository : public UserRepository {

private:
    std::string user_file_name = "user_adoption.db";

public:
    TxtUserRepository() {
        this->load_from_file_user_database(this->user_file_name);
    }
    void save_to_file_user_database(const std::string &file) override;
    std::vector<Dog> get_all_dogs_from_adoption_list() override;
};

class HtmlUserRepository : public UserRepository {

private:
    std::string user_file_name = "user_adoption.html";

public:
    void save_to_file_user_database(const std::string &file) override;
    std::vector<Dog> get_all_dogs_from_adoption_list() override;
};

class CsvUserRepository : public UserRepository {

private:
    std::string user_file_name = "user_adoption.csv";

public:
    void save_to_file_user_database(const std::string &file) override;
    std::vector<Dog> get_all_dogs_from_adoption_list() override;
};

#endif
