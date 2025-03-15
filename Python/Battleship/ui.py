from computer_player import ComputerPlayer
from domain import PlayerBoard, TargetBoard
from exceptions import BattleshipError, GameOver


class UserInterface:

    def __init__(self):
        self.__player_board = PlayerBoard()
        self.__target_board = TargetBoard()
        self.__computer = ComputerPlayer(self.__player_board, self.__target_board)

    def place_player_ship(self):
        while True:
            try:
                available_placing_header_positions = ('A', 'B', 'C', 'D', 'E', 'F')
                target = input(" Where to place your ship (starting position from left to right)?: ")
                if not target[1].isdigit():
                    raise BattleshipError("Your input format is invalid! (Example: A1 - left and top corner)")
                row = int(target[1]) - 1
                if not target[0] in available_placing_header_positions:
                    raise BattleshipError("Your input format is invalid! (Example: A1 - left and top corner)")
                column = int(ord(target[0]) - ord('A'))
                self.__player_board.place_ship(row, column)
                break
            except BattleshipError as error_message:
                print("Error: ", error_message)

    def run_program(self):
        print("\n")
        print("  ~  Battleship Game  ~  ")
        print("")
        print("  >  Your bord:")
        print("")
        print(self.__player_board)
        print("")
        self.place_player_ship()
        print("")
        print("  ~  Game started  ~  ")

        try:
            while True:
                print(" ")
                print(" > Your Bord: < ")
                print(self.__player_board)
                print(" ")
                print(" > Computer Bord: < ")
                print(self.__target_board)
                try:
                    available_placing_header_positions = ('A', 'B', 'C', 'D', 'E', 'F')
                    target = input(" Where to fire?: ")
                    if not target[1].isdigit():
                        raise BattleshipError("Your input format is invalid! (Example: A1 - left and top corner)")
                    row = int(target[1]) - 1
                    if not target[0] in available_placing_header_positions:
                        raise BattleshipError("Your input format is invalid! (Example: A1 - left and top corner)")
                    column = int(ord(target[0]) - ord('A'))
                    self.__target_board.fire_a_box(row, column)
                    self.__target_board.check_if_won()
                    self.__computer.random_fire_a_box()
                    self.__player_board.check_if_won()
                except BattleshipError as error_message:
                    print(error_message)
        except GameOver as winner_message:
            print("\n", winner_message, "\n")


user_interface = UserInterface()
user_interface.run_program()
