
class Activity:
    def __init__(self, activity_id, participant_persons_ids, activity_date, activity_time, activity_descrption):
        self.__id = activity_id
        self.__participants_ids = participant_persons_ids
        self.__date = activity_date
        self.__time = activity_time
        self.__description = activity_descrption

    @property
    def get_activity_id(self):
        return self.__id

    @property
    def get_activity_participants_ids(self):
        return self.__participants_ids

    @property
    def get_activity_date(self):
        return self.__date

    @property
    def get_activity_time(self):
        return self.__time

    @property
    def get_activity_description(self):
        return self.__description

    @get_activity_id.setter
    def get_activity_id(self, new_id):
        self.__id = new_id

    @get_activity_participants_ids.setter
    def get_activity_participants_ids(self, new_ids):
        self.__participants_ids = new_ids

    @get_activity_date.setter
    def get_activity_date(self, new_date):
        self.__date = new_date

    @get_activity_time.setter
    def get_activity_time(self, new_time):
        self.__time = new_time

    @get_activity_description.setter
    def get_activity_description(self, new_description):
        self.__description = new_description

    def __eq__(self, compared_activity):
        if not isinstance(self, compared_activity):
            return False
        elif self.__id == compared_activity.get_activity_id:
            return True
        return False

    def __str__(self):
        return "ID: " + str(self.__id) + ";   Participants' ID: " + str(self.__participants_ids) + '\nDate: ' + str(self.__date) + ';   Duration: ' + str(self.__time) + '\nDescription: ' + str(self.__description) + '\n'
