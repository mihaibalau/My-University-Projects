from texttable import Texttable
from exceptions import BattleshipError, GameOver


class Board:
    def __init__(self, size: int = 6):
        self._size = 6
        self._box_data = [[' ' for i in range(size)] for j in range(size)]
        self._hit_count = 0

    @property
    def size(self):
        return self._size

    def place_ship(self, row, column):
        if not (0 <= column < int(self._size - 2)):
            raise BattleshipError("Ship outside bounds")
        if not (0 <= row < int(self._size)):
            raise BattleshipError("Ship outside bounds")
        for i in (0, 1, 2):
            self._box_data[row][column + i] = 'S'

    def check_if_the_box_is_fireable_by_computer(self, row, column):
        if self._box_data[row][column] == ' ' or 'S':
            return True
        return False

    def fire_a_box(self, row, column):
        if not (0 <= row < self._size) or not (0 <= column < self._size):
            raise BattleshipError("Attack outside the board")

        if self._box_data[row][column] in ('$', '*'):
            raise BattleshipError("The square was attacked before")
        if self._box_data[row][column] == ' ':
            self._box_data[row][column] = '*'
            return False
        if self._box_data[row][column] == 'S':
            self._box_data[row][column] = '$'
            self._hit_count += 1
            return True


class PlayerBoard(Board):
    def __str__(self):
        t = Texttable()
        header = []
        for i in range(ord('A'), ord('A') + self._size):
            header.append(chr(i))
        header.append("\\")
        t.header(header)

        for i in range(self._size):
            t.add_row(self._box_data[i] + [i + 1])
        return t.draw()

    def check_if_won(self):
        if self._hit_count == 3:
            raise GameOver("  ~  Computer the game  ~  ")


class TargetBoard(Board):
    def __str__(self):
        t = Texttable()
        header = []
        for i in range(ord('A'), ord('A') + self._size):
            header.append(chr(i))
        header.append("\\")
        t.header(header)

        for i in range(self._size):
            row = [' ' if char == 'S' else char for char in self._box_data[i]] + [i + 1]
            t.add_row(row)
        return t.draw()

    def check_if_won(self):
        if self._hit_count == 3:
            raise GameOver("  ~  You won won the game  ~  ")
