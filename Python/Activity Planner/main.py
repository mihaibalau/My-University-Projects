from src.repository.ActivityRepository import ActivityRepository
from src.repository.PersonRepository import PersonRepository
from src.services.ActivitiesService import ActivitiesServices
from src.services.PersonsService import PersonServices
from src.ui.UserInterface import UserInterface

if __name__ == "__main__":

    persons_repository = PersonRepository()
    activities_repository = ActivityRepository()

    amount_of_random_generated_persons = 20
    amount_of_random_generated_activities = 20

    persons_repository.generate_random_persons(amount_of_random_generated_persons)
    activities_repository.generate_random_activities(amount_of_random_generated_activities)

    persons_services = PersonServices(persons_repository)
    activities_services = ActivitiesServices(activities_repository)

    user_interface = UserInterface(persons_services, activities_services)
    user_interface.run_program()
