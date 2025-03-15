import random

from src.domain.Activity import Activity


class ActivityRepository:
    def __init__(self):
        self.__activities_list = {}

    def __len__(self):
        return len(self.__activities_list)

    def number_of_activities(self):
        return len(self.__activities_list)

    def add_an_activity_in_repository(self, activity):
        self.__activities_list[activity.get_activity_id] = activity

    def remove_an_activity_from_repository(self, activity_id):
        self.__activities_list.pop(activity_id)

    def update_an_activity_from_repository(self, new_activity):
        self.__activities_list[new_activity.get_activity_id] = new_activity

    def get_an_activity_from_repository(self, activity_id):
        return self.__activities_list[activity_id]

    def get_all_activities_from_repository(self):
        return self.__activities_list

    def generate_random_activities(self, number_of_random_generated_persons):
        available_activities = ['Bowling', 'Golf', 'Gym', 'Drawing', 'Singing', 'Dancing', 'Reading', 'Cycling']
        available_random_minutes = ['00', '10', '15', '30', '45']
        starting_id_numbers = 11
        for index in range(0, number_of_random_generated_persons):
            new_activity_id = starting_id_numbers + index
            new_activity_date = str(random.randint(1, 31)) + "/" + str(random.randint(1, 12)) + "/" + str(random.randint(2022, 2023))
            new_activity_start_time_hour = random.randint(10, 18)
            new_activity_time_minutes = random.choice(available_random_minutes)
            new_activity_end_time_hour = new_activity_start_time_hour + random.randint(1, 4)
            new_activity_time = str(new_activity_start_time_hour) + ":" + new_activity_time_minutes + " -> " + str(new_activity_end_time_hour) + ":" + new_activity_time_minutes
            new_activity_type = random.choice(available_activities)
            new_activity_description = "Relax through an activity of " + new_activity_type
            new_activity = Activity(new_activity_id, [], new_activity_date, new_activity_time, new_activity_description)
            self.__activities_list[new_activity_id] = new_activity
