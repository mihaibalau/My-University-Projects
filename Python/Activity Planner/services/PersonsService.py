from src.domain.Person import Person
from src.validators.PersonsValidator import ValidatePerson


class PersonServices:
    def __init__(self, persons_repository):
        self.__persons_list = persons_repository
        self.__validate_inputs = ValidatePerson()

    def add_a_person_to_list(self, inputed_person_id, inputed_person_name, inputed_person_phone_number):
        self.__validate_inputs.validate_id_characters(inputed_person_id)
        inputed_person_id = int(inputed_person_id)
        self.__validate_inputs.validate_name(inputed_person_name)
        self.__validate_inputs.validate_phone_number(inputed_person_phone_number)
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        self.__validate_inputs.validate_if_id_is_unique(inputed_person_id, persons_repository)
        new_person = Person(inputed_person_id, inputed_person_name, inputed_person_phone_number)
        self.__persons_list.add_a_person_in_repository(new_person)

    def remove_a_person_from_list(self, inputed_person_id):
        self.__validate_inputs.validate_id_characters(inputed_person_id)
        inputed_person_id = int(inputed_person_id)
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        self.__validate_inputs.validate_if_id_exist(inputed_person_id, persons_repository)
        self.__persons_list.remove_a_person_from_repository(inputed_person_id)

    def update_a_person_inside_the_list(self, inputed_person_id, inputed_person_name, inputed_person_phone_number):
        self.__validate_inputs.validate_id_characters(inputed_person_id)
        inputed_person_id = int(inputed_person_id)
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        self.__validate_inputs.validate_if_id_exist(inputed_person_id, persons_repository)
        self.__validate_inputs.validate_name(inputed_person_name)
        self.__validate_inputs.validate_phone_number(inputed_person_phone_number)

        new_person = Person(inputed_person_id, inputed_person_name, inputed_person_phone_number)
        self.__persons_list.update_an_person_from_repository(new_person)
        
    def list_all_persons_from_list(self):
        return self.__persons_list.get_all_persons_from_repository()

    def get_a_person_from_repository(self, person_index):
        return self.__persons_list.get_a_person_from_repository(person_index)

    def verifity_person_inputs(self, inputed_person_id):
        self.__validate_inputs.validate_id_characters(inputed_person_id)
        inputed_person_id = int(inputed_person_id)
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        self.__validate_inputs.validate_if_id_exist(inputed_person_id, persons_repository)

    def person_search_by_name(self, inputed_name):
        returned_list = []
        person_found = False
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        for each_person in persons_repository.values():
            if inputed_name in each_person.get_person_name.lower():
                person_found = True
                returned_list.append(each_person)
        if person_found is True:
            return returned_list
        else:
            return -1

    def person_search_by_phone_number(self, inputed_phone_number):
        returned_list = []
        person_found = False
        persons_repository = self.__persons_list.get_all_persons_from_repository()
        for each_person in persons_repository.values():
            if inputed_phone_number in each_person.get_person_phone_number:
                person_found = True
                returned_list.append(each_person)
        if person_found is True:
            return returned_list
        else:
            return -1
