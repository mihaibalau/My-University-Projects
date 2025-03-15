from src.validators.Exception import ValidationException

class ValidateActivity:
    def __init__(self):
        pass

    @staticmethod
    def validate_id_characters(received_id):
        if not received_id.isnumeric():
            raise ValidationException("Activity's ID is invalid!")

    @staticmethod
    def validate_if_id_is_unique(received_id, checked_list):
        for current_activity_index in checked_list:
            if received_id == int(current_activity_index):
                raise ValidationException("This activity ID is already used!")

    @staticmethod
    def validate_if_id_exist(received_id, checked_list):
        id_found = False
        for current_activity_index in checked_list:
            if received_id == int(current_activity_index):
                id_found = True
        if not id_found:
            raise ValidationException("This activity ID wasn't found used!")

    @staticmethod
    def validate_date(received_date):
        received_date = received_date.split("/")
        if len(received_date) != 3:
            raise ValidationException("Date format is invalid!")
        for each_element in received_date:
            if not each_element.isdigit():
                raise ValidationException("The date can contain only digits!")
        day = int(received_date[0])
        month = int(received_date[1])
        year = int(received_date[2])
        if day < 1 or day > 31:
            raise ValidationException("The day is invalid!")
        if month < 1 or month > 12:
            raise ValidationException("The month is invalid!")
        if year < 2022 or month > 2023:
            raise ValidationException("The year can be only 2022 or 2023!")

    @staticmethod
    def validate_time(received_time):
        received_time = received_time.split(":")
        if len(received_time) != 2:
            raise ValidationException("Time format is invalid!")
        for each_element in received_time:
            if not each_element.isdigit():
                raise ValidationException("The time can contain only digits!")
        hour = int(received_time[0])
        minute = int(received_time[1])
        minimum_hour_to_start_an_activity = 10
        maximum_hour_to_start_an_activity = 18
        if hour < minimum_hour_to_start_an_activity or hour > maximum_hour_to_start_an_activity:
            raise ValidationException("The activity can start only in the interval 10-18!")
        if minute < 0 or minute >= 60:
            raise ValidationException("The iputed minutes are invalid!")

    @staticmethod
    def validate_duration(received_duration):
        if not received_duration.isnumeric():
            raise ValidationException("Activity's duration is invalid!")
        maximum_duraiton_in_hours = 5
        received_duration = int(received_duration)
        if received_duration > maximum_duraiton_in_hours:
            raise ValidationException("Activity's duration is too long!")

    @staticmethod
    def validate_description(received_description):
        if len(received_description) < 5:
            raise ValidationException("This description is too short!")
