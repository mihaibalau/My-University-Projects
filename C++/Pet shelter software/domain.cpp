#include "domain.h"
#include <sstream>
#include <iostream>
#include <string>

Dog::Dog(std::string& breed, std::string& name, int& age, std::string& photograph_link){
    this->age = age;
    this->breed = breed;
    this->name = name;
    this->photograph_link = photograph_link;
}

Dog::Dog(){
    this->age = 0;
    this->breed = "0";
    this->name = "0";
    this->photograph_link = "0";
}

std::string Dog::get_breed() const{
    return this->breed;
}

std::string Dog::get_name() const{
    return this->name;
}

int Dog::get_age() const{
    return this->age;
}


std::string Dog::get_photograph_link() const{
    return this->photograph_link;
}

void Dog::set_breed(const std::string& new_breed){
    this->breed = new_breed;
}
void Dog::set_name(const std::string& new_name){
    this->name = new_name;
}

void Dog::set_age(const int& new_age){
    this->age = new_age;
}

void Dog::set_photograph_link(const std::string& new_photograph_link){
    this->photograph_link = new_photograph_link;
}

Dog& Dog::operator=(const Dog &v) {
        this->name = v.name;
        this->breed = v.breed;
        this->age = v.age;
        this->photograph_link = v.photograph_link;
        return *this;
}

bool Dog::operator==(const Dog &dog) const {
    return this->photograph_link == dog.photograph_link;
}

std::string Dog::toString() {

    std::stringstream text;
    text << "Breed: " << this->breed << " Name: " << this->name << " Age: " << this->age << " Photograph link: " << this->get_photograph_link() << "\n";
    return text.str();
}

std::istream &operator>>(std::istream &stream, Dog &dog) {
    std::getline(stream,dog.breed, ';');
    std::getline(stream,dog.name, ';');
    stream >> dog.age;
    stream.ignore();
    std::getline(stream,dog.photograph_link);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Dog &dog) {
    stream << dog.breed << ";" << dog.name << ";" << dog.age << ";" << dog.photograph_link << std::endl;
    return stream;
}




















