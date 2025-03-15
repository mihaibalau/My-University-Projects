//
// Created by mihib on 4/18/2024.
//

#ifndef OOP_A6_7_BALAUMIHAI_UI_H
#define OOP_A6_7_BALAUMIHAI_UI_H

#include "services.h"

class UserInterface {

private:
    Services services;

    void administrator_mode_menu();
    void add_a_new_dog();
    void delete_a_dog();
    void update_a_dog();
    void list_all_dogs();
    void user_mode_menu();
    void see_the_dogs_available_for_adoption();
    void see_the_dogs_available_for_adoption_filtered_by_breed_and_age();
    void see_the_adoption_list();

public:
    UserInterface(Services& linked_service) : services(linked_service) {}
    void program_run();
};

#endif //OOP_A6_7_BALAUMIHAI_UI_H
