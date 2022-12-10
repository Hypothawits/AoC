import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

class step():
    def __init__(self, dir, speed):
        self.dir = dir
        self.speed = int(speed)


class player():
    def __init__(self, pos_x, pos_y):
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.prev_x = pos_x
        self.prev_y = pos_y

    def save_pos(self):
        self.prev_x = self.pos_x
        self.prev_y = self.pos_y

    def move_player(self, dir):
        speed = 1
        if dir == 'U':
            self.pos_y += speed
        elif dir == 'D':
            self.pos_y -= speed
        elif dir == 'L':
            self.pos_x -= speed
        elif dir == 'R':
            self.pos_x += speed

class chaser():
    def __init__(self, pos_x, pos_y):
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.history = []

    def chase_player(self, player):
        px = player.pos_x
        py = player.pos_y

        move_closer_x = False
        move_closer_y = False
        if abs(px - self.pos_x) > 1:
            move_closer_x = True
        if abs(py - self.pos_y) > 1:
            move_closer_y = True

        # a = 0
        if  (move_closer_x and abs(py - self.pos_y) == 1)  or \
            (move_closer_y and abs(px - self.pos_x) == 1) or \
            (move_closer_x and move_closer_y)  :
            self.pos_x = player.prev_x
            self.pos_y = player.prev_y

        elif move_closer_y:
            diff = (py - self.pos_y) > 0# if pos_dif : player is in front, move forward
            if diff:
                self.pos_y += 1
            else:
                self.pos_y -= 1

        elif move_closer_x:
            diff = (px - self.pos_x) > 0
            if diff:
                self.pos_x += 1
            else:
                self.pos_x -= 1

        self.history.append(str(self.pos_x) + " " + str(self.pos_y))




def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    moves = []
    for line in lines:
        dir, speed = line.split(' ')
        new_move = step(dir, speed)
        moves.append(new_move)

    player1 = player(0,0)
    chaser1 = chaser(0,0)
    # chaser1.history.append('00')

    for move in moves:
        for i in range(1, move.speed +1):
            player1.save_pos()
            player1.move_player(move.dir)
            chaser1.chase_player(player1)
            # print("player [x: " + str(player1.pos_x) + " - y: " + str(player1.pos_y) + " ]")
            # print("chaser [x: " + str(chaser1.pos_x) + " - y: " + str(chaser1.pos_y) + " ]")
            # print(" ")

    number_of_steps = len(chaser1.history)
    number_of_unique = len(set(chaser1.history))


    return number_of_unique

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    return -1

