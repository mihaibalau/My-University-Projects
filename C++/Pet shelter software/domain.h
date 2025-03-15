#ifndef OOP_A6_7_BALAUMIHAI_DOMAIN_H
#define OOP_A6_7_BALAUMIHAI_DOMAIN_H

#include <string>

class Dog{

private:
    int age;
    std::string breed;
    std::string name;
    std::string photograph_link;

public:
    Dog(std::string& breed, std::string& name, int& age, std::string& photograph_link);
    Dog();
    std::string get_breed() const;
    std::string get_name() const;
    int get_age() const;
    std::string get_photograph_link() const;
    void set_breed(const std::string& breed);
    void set_name(const std::string& name);
    void set_age(const int& age);
    void set_photograph_link(const std::string& photograph_link);
    Dog& operator=(const Dog& dog_param);
    bool operator==(const Dog& dog_param) const;

    std::string toString();
    friend std::istream& operator>>(std::istream& stream, Dog& dog);
    friend std::ostream& operator<<(std::ostream& stream, const Dog& dog);


};

#endif
