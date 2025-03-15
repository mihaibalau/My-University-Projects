
class Person:
    def __init__(self, person_id, person_name, person_phone_number):
        self.__id = person_id
        self.__name = person_name
        self.__phone_number = person_phone_number
        
    @property
    def get_person_id(self):
        return self.__id
    
    @property
    def get_person_name(self):
        return self.__name
    
    @property
    def get_person_phone_number(self):
        return self.__phone_number

    @get_person_id.setter
    def get_person_id(self, new_id):
        self.__id = new_id
        
    @get_person_name.setter
    def get_person_name(self, new_name):
        self.__name = new_name
        
    @get_person_phone_number.setter
    def get_person_phone_number(self, new_phone_number):
        self.__phone_number = new_phone_number
        
    def __eq__(self, compared_person):
        if not isinstance(self, compared_person):
            return False
        elif self.__id == compared_person.get_person_id:
            return True
        return False

    def __str__(self):
        return str(self.__id) + ', ' + str(self.__name) + ', ' + str(self.__phone_number)
    