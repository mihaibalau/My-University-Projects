import random


class ComputerPlayer:

    def place_ship(self):
        row = random.randint(0, self.__target_board.size - 1)
        column = random.randint(0, self.__target_board.size - 3)
        self.__target_board.place_ship(row, column)

    def __init__(self, player_board, target_board):
        self.__player_board = player_board
        self.__target_board = target_board

        self.__candidates = []
        for i in range(self.__target_board.size):
            for j in range(self.__target_board.size):
                self.__candidates.append((i, j))

        self.__hits = set()
        self.place_ship()

    def random_fire_a_box(self):
        while True:
            available_placing_header_positions = ('A', 'B', 'C', 'D', 'E', 'F')
            row = random.randint(1, 6)
            row = int(row) - 1
            column = random.choice(available_placing_header_positions)
            column = int(ord(column) - ord('A'))
            if self.__player_board.check_if_the_box_is_fireable_by_computer(row, column):
                self.__player_board.fire_a_box(row, column)
                break
