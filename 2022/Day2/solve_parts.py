import math

class game_round():
    def __init__(self, in1, in2):
        LOSE = 0
        DRAW = 3
        WIN  = 6
        self.item_val = 0
        self.points = 0
        self.did_win = False
        self.did_draw = False
        self.did_lose = False

        if in1 == 'A':
            self.player_me = 'rock'
        elif in1 == 'B':
            self.player_me = 'paper'
        elif in1 == 'C':
            self.player_me = 'scissors'
        else:
            print("error, me failed")

        if in2 == 'X':
            self.player_them = 'rock'
        elif in2 == 'Y':
            self.player_them = 'paper'
        elif in2 == 'Z':
            self.player_them = 'scissors'
        else:
            print("error, them failed")

        if self.player_me == 'rock':            
            self.item_val = 1
        elif self.player_me == 'paper':
            self.item_val = 2
        elif self.player_me == 'scissors':
            self.item_val = 3
        else:
            print("error, Item failed")

        self.did_win = False
        self.did_draw = False
        self.did_lose = False 
        if self.player_me == self.player_them:
            self.points = DRAW + self.item_val
            self.did_draw = True
        elif self.player_me == 'rock' and self.player_them == 'paper':
            self.points = LOSE + self.item_val
            self.did_lose = True
        elif self.player_me == 'rock' and self.player_them == 'scissors':
            self.points = WIN + self.item_val
            self.did_win = True
        elif self.player_me == 'paper' and self.player_them == 'scissors':
            self.points = LOSE + self.item_val
            self.did_lose = True
        elif self.player_me == 'paper' and self.player_them == 'rock':
            self.points = WIN + self.item_val
            self.did_win = True
        elif self.player_me == 'scissors' and self.player_them == 'rock':
            self.points = LOSE + self.item_val
            self.did_lose = True
        elif self.player_me == 'scissors' and self.player_them == 'paper':
            self.points = WIN + self.item_val
            self.did_win = True
        else:
            print("error, round failed")


def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines


def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    rounds = []


    AX = 4
    AY = 8
    AZ = 3
    BX = 1
    BY = 5
    BZ = 9
    CX = 7
    CY = 2
    CZ = 6
    total_points = 0

    for line in lines:
        them, me = line.split(' ')

        if me == "X":
            if them == "A":
                result = AX
            elif them == "B":
                result = BX
            elif them == "C":
                result = CX

        elif me == "Y":
            if them == "A":
                result = AY
            elif them == "B":
                result = BY
            elif them == "C":
                result = CY

        elif me == "Z":
            if them == "A":
                result = AZ
            elif them == "B":
                result = BZ
            elif them == "C":
                result = CZ

        else:
            print("error!")
        total_points += result

    return total_points

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    # X = "lose"
    # Y = "draw"
    # Z = "win"

    AX = 3
    AY = 4
    AZ = 8
    BX = 1
    BY = 5
    BZ = 9
    CX = 2
    CY = 6
    CZ = 7
    total_points = 0

    for line in lines:
        them, outcome = line.split(' ')

        if outcome == "X":
            if them == "A":
                result = AX
            elif them == "B":
                result = BX
            elif them == "C":
                result = CX

        elif outcome == "Y":
            if them == "A":
                result = AY
            elif them == "B":
                result = BY
            elif them == "C":
                result = CY

        elif outcome == "Z":
            if them == "A":
                result = AZ
            elif them == "B":
                result = BZ
            elif them == "C":
                result = CZ

        else:
            print("error!")
        total_points += result

    return total_points
