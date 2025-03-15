from Repository import Graph
from Services import GraphsServices
from UserInterface import GraphsUI

if __name__ == "__main__":
    MainRepository = Graph(0, 0) #
    BackupRepository = Graph(0, 0)
    ProgramServices = GraphsServices(MainRepository, BackupRepository)
    UserInterface = GraphsUI(ProgramServices)
    UserInterface.run_code()
