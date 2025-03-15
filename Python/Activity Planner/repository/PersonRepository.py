import random

from src.domain.Person import Person


class PersonRepository:
    def __init__(self):
        self.__persons_list = {}

    def number_of_persons(self):
        return len(self.__persons_list)

    def add_a_person_in_repository(self, person):
        self.__persons_list[person.get_person_id] = person

    def remove_a_person_from_repository(self, person_id):
        self.__persons_list.pop(person_id)

    def update_an_person_from_repository(self, new_person):
        self.__persons_list[new_person.get_person_id] = new_person

    def get_a_person_from_repository(self, person_index):
        return self.__persons_list[person_index]

    def get_all_persons_from_repository(self):
        return self.__persons_list

    def generate_random_persons(self, number_of_random_generated_persons):
        first_names = ['Alice', 'Bob', 'Charlie', 'David', 'Emma', 'Frank']
        last_names = ['Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis']
        starting_id_numbers = 101
        for index in range(0, number_of_random_generated_persons):
            new_person_id = starting_id_numbers + index
            new_person_name = str(random.choice(first_names)) + ' ' + str(random.choice(last_names))
            new_person_phone_number = random.randint(700000000, 799999999)
            new_person_phone_number = '0' + str(new_person_phone_number)
            new_person = Person(new_person_id, new_person_name, new_person_phone_number)
            self.__persons_list[new_person_id] = new_person
