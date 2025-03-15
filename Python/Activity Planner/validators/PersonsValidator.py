from src.validators.Exception import ValidationException


class ValidatePerson:
    def __init__(self):
        pass

    @staticmethod
    def validate_id_characters(received_id):
        if not received_id.isnumeric():
            raise ValidationException("Person's ID is invalid!")

    @staticmethod
    def validate_if_id_is_unique(received_id, checked_list):
        for each_person in checked_list:
            if int(received_id) == int(each_person):
                raise ValidationException("This person ID is already used!")

    @staticmethod
    def validate_if_id_exist(received_id, checked_list):
        id_found = False
        for each_person in checked_list:
            if int(received_id) == int(each_person):
                id_found = True
        if not id_found:
            raise ValidationException("This person ID wasn't found used!")

    @staticmethod
    def validate_name(received_name):
        available_names = received_name.split(" ")
        for student_name in available_names:
            if not student_name.isalpha():
                raise ValidationException("Person's name is invalid!")

    @staticmethod
    def validate_phone_number(received_number):
        if len(received_number) < 2:
            raise ValidationException("The phone number is too short!")
        for each_char in received_number:
            if not each_char.isdigit():
                raise ValidationException("Person's phone number is invalid!")
