#include "repository.h"
#include "services.h"
#include "ui.h"
#include "Tests.h"
#include "RepositoryManager.h"


int main(){

    int users_repo_type = RepositoryManager::select_type();

    Repository database;
    UserRepository* userRepository = nullptr;

    if(users_repo_type == 1){
        userRepository = new TxtUserRepository();
    }
    else if(users_repo_type == 2){
        userRepository = new HtmlUserRepository();
    }
    else if(users_repo_type == 3){
        userRepository = new CsvUserRepository();
    }

    Services services(database, userRepository);

    //services.initialize_repository();

    UserInterface userInterface(services);
    userInterface.program_run();
}