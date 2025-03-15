from src.domain.Activity import Activity
from src.validators.ActivitiesValidator import ValidateActivity
from src.validators.Exception import ValidationException


class ActivitiesServices:
    def __init__(self, activites_repository):
        self.__activites_list = activites_repository
        self.__validate_inputs = ValidateActivity()

    def add_an_activity_to_list(self, inputed_activity_id, inputed_activity_date, inputed_activity_start_time, inputed_activity_duration, inputed_activity_description):
        self.__validate_inputs.validate_id_characters(inputed_activity_id)
        inputed_activity_id = int(inputed_activity_id)
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        self.__validate_inputs.validate_if_id_is_unique(inputed_activity_id, activities_repository)
        self.__validate_inputs.validate_date(inputed_activity_date)
        self.__validate_inputs.validate_time(inputed_activity_start_time)
        self.__validate_inputs.validate_duration(inputed_activity_duration)
        self.__validate_inputs.validate_description(inputed_activity_description)

        starting_time = inputed_activity_start_time.split(":")
        starting_hour = int(starting_time[0])
        starting_minutes = int(starting_time[1])
        ending_hour = starting_hour + int(inputed_activity_duration)
        formated_time = str(starting_hour) + ":" + str(starting_minutes) + " -> " + str(ending_hour) + ":" + str(starting_minutes)

        new_activity = Activity(inputed_activity_id, [], inputed_activity_date, formated_time, inputed_activity_description)
        self.__activites_list.add_an_activity_in_repository(new_activity)

    def remove_an_activity_from_list(self, inputed_activity_id):
        self.__validate_inputs.validate_id_characters(inputed_activity_id)
        inputed_activity_id = int(inputed_activity_id)
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        self.__validate_inputs.validate_if_id_exist(inputed_activity_id, activities_repository)
        self.__activites_list.remove_an_activity_from_repository(inputed_activity_id)
        pass

    def update_an_activity_inside_the_list(self, inputed_activity_id, inputed_activity_date, inputed_activity_start_time, inputed_activity_duration, inputed_activity_description):
        self.__validate_inputs.validate_id_characters(inputed_activity_id)
        inputed_activity_id = int(inputed_activity_id)
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        self.__validate_inputs.validate_if_id_exist(inputed_activity_id, activities_repository)
        self.__validate_inputs.validate_date(inputed_activity_date)
        self.__validate_inputs.validate_time(inputed_activity_start_time)
        self.__validate_inputs.validate_duration(inputed_activity_duration)
        self.__validate_inputs.validate_description(inputed_activity_description)

        starting_time = inputed_activity_start_time.split(":")
        starting_hour = int(starting_time[0])
        starting_minutes = int(starting_time[1])
        ending_hour = starting_hour + int(inputed_activity_duration)
        formated_time = str(starting_hour) + ":" + str(starting_minutes) + " -> " + str(ending_hour) + ":" + str(starting_minutes)

        new_activity = Activity(inputed_activity_id, [], inputed_activity_date, formated_time, inputed_activity_description)
        self.__activites_list.update_an_activity_from_repository(new_activity)

    def list_all_activities_from_list(self):
        return self.__activites_list.get_all_activities_from_repository()

    def get_an_activity_from_repository(self, activity_index):
        return self.__activites_list.get_an_activity_from_repository(activity_index)

    def add_an_activity_to_a_person(self, activity_id, person_id):
        self.__validate_inputs.validate_id_characters(activity_id)
        activity_id = int(activity_id)
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        self.__validate_inputs.validate_if_id_exist(activity_id, activities_repository)

        activity_participants = activities_repository[activity_id].get_activity_participants_ids
        if person_id in activity_participants:
            raise ValidationException("This person ID is already in that activity!")
        else:
            activity_date = activities_repository[activity_id].get_activity_date
            activity_time = activities_repository[activity_id].get_activity_time
            activity_time = activity_time.split(" -> ")
            activity_starting_time = activity_time[0]
            activity_ending_time = activity_time[1]
            activity_starting_time = activity_starting_time.split(":")
            activity_starting_time_hour = int(activity_starting_time[0])
            activity_starting_time_minute = int(activity_starting_time[1])
            activity_ending_time = activity_ending_time.split(":")
            activity_ending_time_hour = int(activity_ending_time[0])
            activity_ending_time_minute = int(activity_ending_time[1])
            for each_activity in activities_repository.values():
                persons_from_current_activity = each_activity.get_activity_participants_ids
                if person_id in persons_from_current_activity:
                    if activity_date is each_activity.get_activity_date:
                        current_activity_time = each_activity.get_activity_time
                        current_activity_time = current_activity_time.split(" -> ")
                        current_activity_starting_time = current_activity_time[0]
                        current_activity_ending_time = current_activity_time[1]
                        current_activity_starting_time = current_activity_starting_time.split(":")
                        current_activity_starting_time_hour = int(current_activity_starting_time[0])
                        current_activity_starting_time_minute = int(current_activity_starting_time[1])
                        current_activity_ending_time = current_activity_ending_time(":")
                        current_activity_ending_time_hour = int(current_activity_ending_time[0])
                        current_activity_ending_time_minutes = int(current_activity_ending_time[1])
                        if current_activity_starting_time_hour < activity_starting_time_hour:
                            if current_activity_ending_time_hour > activity_starting_time_hour:
                                raise ValidationException("Persons activity are overlapping!")
                            elif current_activity_ending_time_hour == activity_starting_time_hour:
                                if current_activity_ending_time_minutes > activity_starting_time_minute:
                                    raise ValidationException("Persons activity are overlapping!")
                        else:
                            if activity_ending_time_hour >= current_activity_starting_time_hour:
                                raise ValidationException("Persons activity are overlapping!")
                            elif activity_ending_time_hour == current_activity_starting_time_hour:
                                if activity_ending_time_minute > current_activity_starting_time_minute:
                                    raise ValidationException("Persons activity are overlapping!")
        activity_participants.append(person_id)
        activities_repository[activity_id].get_activity_participants_ids = activity_participants

    def remove_an_activity_to_a_person(self, activity_id, person_id):
        self.__validate_inputs.validate_id_characters(activity_id)
        activity_id = int(activity_id)
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        self.__validate_inputs.validate_if_id_exist(activity_id, activities_repository)

        activity_participants = activities_repository[activity_id].get_activity_participants_ids
        if person_id in activity_participants:
            activity_participants.remove(person_id)
        else:
            raise ValidationException("This person ID isn't in that activity!")
        activities_repository[activity_id].get_activity_participants_ids = activity_participants


    def activity_search_by_date_time(self, inputed_string):
        returned_list = []
        activity_found = False
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        for each_activity in activities_repository.values():
            if inputed_string in each_activity.get_activity_time:
                activity_found = True
                returned_list.append(each_activity)
            elif inputed_string in each_activity.get_activity_date:
                activity_found = True
                returned_list.append(each_activity)
        if activity_found is True:
            return returned_list
        else:
            return -1

    def activity_search_by_description(self, inputed_description):
        returned_list = []
        activity_found = False
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        for each_activity in activities_repository.values():
            if inputed_description.lower() in each_activity.get_activity_description.lower():
                activity_found = True
                returned_list.append(each_activity)
        if activity_found is True:
            return returned_list
        else:
            return -1

    def list_activities_for_a_given_date(self, inputed_date):
        returned_list = []
        self.__validate_inputs.validate_date(inputed_date)
        activity_found = False
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        for each_activity in activities_repository.values():
            if inputed_date in each_activity.get_activity_date:
                activity_found = True
                returned_list.append(each_activity)

        for first in range(0, len(returned_list)):
            for second in range(first+1, len(returned_list)):
                first_time = returned_list[first].get_activity_time
                first_time = first_time.split(" -> ")
                first_time = first_time[0]
                first_time = first_time.split(":")
                first_time_hour = int(first_time[0])
                first_time_minutes = int(first_time[1])

                second_time = returned_list[second].get_activity_time
                second_time = second_time.split(" -> ")
                second_time = second_time[0]
                second_time = second_time.split(":")
                second_time_hour = int(second_time[0])
                second_time_minutes = int(second_time[1])

                if first_time_hour > second_time_hour:
                    swap_value_save = returned_list[first]
                    returned_list[first] = returned_list[second]
                    returned_list[second] = swap_value_save
                elif first_time_hour == second_time_hour and first_time_minutes > second_time_minutes:
                    swap_value_save = returned_list[first]
                    returned_list[first] = returned_list[second]
                    returned_list[second] = swap_value_save

        if activity_found is True:
            return returned_list
        else:
            return -1

    def list_upcoming_dates_with_activities(self):
        returned_list = []
        return -1

    def list_all_upcoming_activities_for_a_person(self, inputed_id):
        returned_list = []
        activity_found = False
        activities_repository = self.__activites_list.get_all_activities_from_repository()
        for each_activity in activities_repository.values():
            if inputed_id in each_activity.get_activity_participants_ids:
                activity_found = True
                returned_list.append(each_activity)

        if activity_found is True:
            return returned_list
        else:
            return -1
