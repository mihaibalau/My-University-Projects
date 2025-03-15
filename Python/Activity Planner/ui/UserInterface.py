from src.validators.Exception import ValidationException


class ManagePersonsAndActivities:
    def __init__(self, service_for_persons, service_for_activities):
        self.__persons_service = service_for_persons
        self.__activities_service = service_for_activities

    @staticmethod
    def print_class_menu():
        print("")
        print("  ~  Activity Planner - First Option  ~  ")
        print("1. Add a person")
        print("2. Remove a person")
        print("3. Update a person")
        print("4. List a person")
        print("5. Add an activity")
        print("6. Remove an activity")
        print("7. Update an activity")
        print("8. List an activity")
        print(" ")

    def handle_add_a_person_to_list(self):
        while True:
            try:
                new_person_id = input("Enter new person's id: ")
                new_person_name = input("Enter new person's name: ")
                new_person_phone_number = input("Enter new person's phone number: ")
                self.__persons_service.add_a_person_to_list(new_person_id, new_person_name, new_person_phone_number)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_remove_a_person_from_list(self):
        while True:
            try:
                person_id = input("Enter person id: ")
                self.__persons_service.remove_a_person_from_list(person_id)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_update_a_person_inside_the_list(self):
        while True:
            try:
                person_id = input("Enter person id: ")
                new_person_name = input("Enter new person's name: ")
                new_person_phone_number = input("Enter new person's phone number: ")
                self.__persons_service.update_a_person_inside_the_list(person_id, new_person_name, new_person_phone_number)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_list_all_persons_from_list(self):
        print(" > The persons list is:")
        printed_list = self.__persons_service.list_all_persons_from_list()
        for each_person in printed_list:
            printed_person = self.__persons_service.get_a_person_from_repository(each_person)
            print(printed_person)
        print("  Operation made successfully! ")

    def handle_add_an_activity_to_list(self):
        while True:
            try:
                new_activity_id = input("Enter the activity id: ")
                new_activity_date = input("Enter the activity date (DD/MM/YYYY): ")
                new_activity_start_time = input("Enter the activity start time (HH:MM): ")
                new_activity_duration = input("Enter the activity duration: ")
                new_activity_description = input("Enter the activity description: ")
                self.__activities_service.add_an_activity_to_list(new_activity_id, new_activity_date, new_activity_start_time, new_activity_duration, new_activity_description)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_remove_an_activity_from_list(self):
        while True:
            try:
                activity_id = input("Enter the activity id: ")
                self.__activities_service.remove_an_activity_from_list(activity_id)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_update_an_activity_inside_the_list(self):
        while True:
            try:
                activity_id = input("Enter the activity id: ")
                new_activity_date = input("Enter the new activity date (DD/MM/YYYY): ")
                new_activity_start_time = input("Enter the new activity start time (HH:MM): ")
                new_activity_duration = input("Enter the new activity duration: ")
                new_activity_description = input("Enter the new activity description: ")
                self.__activities_service.update_an_activity_inside_the_list(activity_id, new_activity_date, new_activity_start_time, new_activity_duration, new_activity_description)
                print("  Operation made successfully! ")
                break
            except ValidationException as error_message:
                print("Error:", error_message)

    def handle_list_all_activities_from_list(self):
        print(" > The activities list is:")
        printed_list = self.__activities_service.list_all_activities_from_list()
        for each_activity in printed_list:
            printed_activity = self.__activities_service.get_an_activity_from_repository(each_activity)
            print(printed_activity)
        print("  Operation made successfully! ")

    def run_option(self):
        try:
            self.print_class_menu()
            inputed_option = input("Enter the option: ")
            add_a_person = '1'
            remove_a_person = '2'
            update_a_person = '3'
            list_a_person = '4'
            add_an_activity = '5'
            remove_an_activity = '6'
            update_an_activity = '7'
            list_an_activity = '8'
            if inputed_option == add_a_person:
                self.handle_add_a_person_to_list()
            elif inputed_option == remove_a_person:
                self.handle_remove_a_person_from_list()
            elif inputed_option == update_a_person:
                self.handle_update_a_person_inside_the_list()
            elif inputed_option == list_a_person:
                self.handle_list_all_persons_from_list()
            elif inputed_option == add_an_activity:
                self.handle_add_an_activity_to_list()
            elif inputed_option == remove_an_activity:
                self.handle_remove_an_activity_from_list()
            elif inputed_option == update_an_activity:
                self.handle_update_an_activity_inside_the_list()
            elif inputed_option == list_an_activity:
                self.handle_list_all_activities_from_list()
            else:
                raise ValidationException("Error: Invalid option!")
        except ValidationException as error_message:
            print("Error:", error_message)


class AddOrRemoveActivities:

    def __init__(self, service_for_persons, service_for_activities):
        self.__persons_service = service_for_persons
        self.__activities_service = service_for_activities

    @staticmethod
    def print_class_menu():
        print("")
        print("  ~  Activity Planner - Second Option  ~  ")
        print("1. Add persons to an activity")
        print("2. Remove persons from an activity")
        print("")

    def handle_add_an_activity_to_a_person(self):
        activity_id = input("Enter the activity id: ")
        person_id = input("Enter the person id: ")
        self.__persons_service.verifity_person_inputs(person_id)
        self.__activities_service.add_an_activity_to_a_person(activity_id, person_id)
        print("  Operation made successfully! ")

    def handle_remove_an_activity_to_a_person(self):
        activity_id = input("Enter the activity id: ")
        person_id = input("Enter the person id: ")
        self.__activities_service.remove_an_activity_to_a_person(activity_id, person_id)
        print("  Operation made successfully! ")

    def run_option(self):
        try:
            self.print_class_menu()
            inputed_option = input("Enter the option: ")
            add_an_activity_to_a_person = '1'
            remove_an_activity_to_a_person = '2'
            if inputed_option == add_an_activity_to_a_person:
                self.handle_add_an_activity_to_a_person()
            elif inputed_option == remove_an_activity_to_a_person:
                self.handle_remove_an_activity_to_a_person()
            else:
                raise ValidationException("Error: Invalid option!")
        except ValidationException as error_message:
            print("Error:", error_message)


class SearchPersonOrActivity:

    def __init__(self, service_for_persons, service_for_activities):
        self.__persons_service = service_for_persons
        self.__activities_service = service_for_activities

    @staticmethod
    def print_class_menu():
        print("")
        print("  ~  Activity Planner - Third Option  ~  ")
        print("1. Search for a person through name")
        print("2. Search for a person through phone number")
        print("3. Search for an activity through date/time")
        print("4. Search for an activity through description")
        print("")

    def handle_person_search_by_name(self):
        searched_person_name = input("Enter the searched person name: ")
        printed_list = self.__persons_service.person_search_by_name(searched_person_name)
        if printed_list != -1:
            print(" > The resulted persons list for your search: ")
            for each_person in printed_list:
                print(each_person)
            print("  Operation made successfully! ")
        else:
            print("  No person found!  ")

    def handle_person_search_by_phone_number(self):
        searched_person_phone_number = input("Enter the searched person phone number: ")
        printed_list = self.__persons_service.person_search_by_phone_number(searched_person_phone_number)
        if printed_list != -1:
            print(" > The resulted persons list for your search: ")
            for each_person in printed_list:
                print(each_person)
            print("  Operation made successfully! ")
        else:
            print("  No person found!  ")

    def handle_activity_search_by_date_time(self):
        searched_activity_date_or_time = input("Enter the searched activity date or time: ")
        printed_list = self.__activities_service.activity_search_by_date_time(searched_activity_date_or_time)
        if printed_list != -1:
            print(" > The resulted activities list for your search: ")
            for each_activity in printed_list:
                print(each_activity)
            print("  Operation made successfully! ")
        else:
            print("  No activity found!  ")

    def handle_activity_search_by_description(self):
        searched_activity_description = input("Enter the searched activity description: ")
        printed_list = self.__activities_service.activity_search_by_description(searched_activity_description)
        if printed_list != -1:
            print(" > The resulted activities list for your search: ")
            for each_activity in printed_list:
                print(each_activity)
            print("  Operation made successfully! ")
        else:
            print("  No activity found!  ")

    def run_option(self):
        try:
            self.print_class_menu()
            inputed_option = input("Enter the option: ")
            person_search_by_name = '1'
            person_search_by_phone_number = '2'
            activity_search_by_date_time = '3'
            activity_search_by_description = '4'
            if inputed_option == person_search_by_name:
                self.handle_person_search_by_name()
            elif inputed_option == person_search_by_phone_number:
                self.handle_person_search_by_phone_number()
            elif inputed_option == activity_search_by_date_time:
                self.handle_activity_search_by_date_time()
            elif inputed_option == activity_search_by_description:
                self.handle_activity_search_by_description()
            else:
                raise ValidationException("Error: Invalid option!")
        except ValidationException as error_message:
            print("Error:", error_message)


class CreateStatistics:

    def __init__(self, service_for_persons, service_for_activities):
        self.__persons_service = service_for_persons
        self.__activities_service = service_for_activities

    @staticmethod
    def print_class_menu():
        print("")
        print("  ~  Activity Planner - Fourth Option  ~  ")
        print("1. List the activities for a given date, in the order of their start time")
        print("2. List upcoming dates with activities")
        print("3. List all upcoming activities to which a given person will participate")
        print("")

    def handle_list_activities_for_a_given_date(self):
        printed_activities_for_that_date = input("Enter the date: ")
        printed_list = self.__activities_service.list_activities_for_a_given_date(printed_activities_for_that_date)
        if printed_list != -1:
            print(" > The activities from inputed date: ")
            for each_activity in printed_list:
                print(each_activity)
            print("  Operation made successfully! ")
        else:
            print("  No activity found for that date!  ")

    def handle_list_upcoming_dates_with_activities(self):
        printed_list = self.__activities_service.list_upcoming_dates_with_activities()
        if printed_list != -1:
            print(" > The activities from busiest day: ")
            for each_activity in printed_list:
                print(each_activity)
            print("  Operation made successfully! ")
        else:
            print("  No activity found for that date!  ")

    def handle_list_all_upcoming_activities_for_a_person(self):
        printed_perons_activities = input("Enter the person id: ")
        printed_list = self.__activities_service.list_all_upcoming_activities_for_a_person(printed_perons_activities)
        if printed_list != -1:
            print(" > The activities from inputed date: ")
            for each_activity in printed_list:
                print(each_activity)
            print("  Operation made successfully! ")
        else:
            print("  No activity found for that date!  ")

    def run_option(self):
        try:
            self.print_class_menu()
            inputed_option = input("Enter the option: ")
            list_activities_for_a_given_date = '1'
            list_upcoming_dates_with_activities = '2'
            list_all_upcoming_activities_for_a_person = '3'
            if inputed_option == list_activities_for_a_given_date:
                self.handle_list_activities_for_a_given_date()
            elif inputed_option == list_upcoming_dates_with_activities:
                self.handle_list_upcoming_dates_with_activities()
            elif inputed_option == list_all_upcoming_activities_for_a_person:
                self.handle_list_all_upcoming_activities_for_a_person()
            else:
                raise ValidationException("Error: Invalid option!")
        except ValidationException as error_message:
            print("Error:", error_message)


class UserInterface:

    def __init__(self, service_for_persons, service_for_activities):
        self.__manage_persons_and_activities = ManagePersonsAndActivities(service_for_persons, service_for_activities)
        self.__add_or_remove_activities = AddOrRemoveActivities(service_for_persons, service_for_activities)
        self.__search_person_or_activities = SearchPersonOrActivity(service_for_persons, service_for_activities)
        self.__create_statistics = CreateStatistics(service_for_persons, service_for_activities)

    @staticmethod
    def print_main_menu():
        print("")
        print("  ~  Activity Planner - Main Menu  ~  ")
        print("1. Manage persons and activities")
        print("2. Add/remove activities")
        print("3. Search for persons or activities")
        print("4. Create statistics")
        print("5. Close program")
        print("")

    def run_program(self):
        while True:
            try:
                self.print_main_menu()
                inputed_option = input("Enter the option: ")
                manage_persons_and_activities = '1'
                add_or_remove_activities = '2'
                search_for_persons_or_activities = '3'
                create_statistics = '4'
                close_program = '5'
                if inputed_option == manage_persons_and_activities:
                    self.__manage_persons_and_activities.run_option()
                elif inputed_option == add_or_remove_activities:
                    self.__add_or_remove_activities.run_option()
                elif inputed_option == search_for_persons_or_activities:
                    self.__search_person_or_activities.run_option()
                elif inputed_option == create_statistics:
                    self.__create_statistics.run_option()
                elif inputed_option == close_program:
                    break
                else:
                    raise ValidationException("Error: Invalid option!")
            except ValidationException as error_message:
                print("Error:", error_message)
