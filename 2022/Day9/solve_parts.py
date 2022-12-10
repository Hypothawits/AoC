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
        self.moved_dig = False

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
        self.prev_x = pos_x
        self.prev_y = pos_y
        self.history = []

    def save_pos(self):
        self.prev_x = self.pos_x
        self.prev_y = self.pos_y

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
        if  (move_closer_x or move_closer_y):
            self.pos_x = player.prev_x
            self.pos_y = player.prev_y

        self.history.append(str(self.pos_x) + " " + str(self.pos_y))


class Tail():
    def __init__(self, pos_x, pos_y, last):
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.last_tail = last
        self.moved_dig = False
        self.history = []

    def chase_player(self, Head):
        self.prev_x = self.pos_x
        self.prev_y = self.pos_y

        H_px = Head.pos_x
        H_py = Head.pos_y

        move_closer_x  = False
        move_closer_y  = False
        self.moved_dig = False # Reset for new move

        if abs(H_px - self.pos_x) > 1:
            move_closer_x = True
        if abs(H_py - self.pos_y) > 1:
            move_closer_y = True

        # a = 0
        if  (move_closer_x or move_closer_y) and not Head.moved_dig:
            # if we are the first tail, need to check for diagonal move
            if (abs(H_px - self.pos_x) > 0) and (abs(H_py - self.pos_y) > 0):
                self.moved_dig = True
            else:
                self.moved_dig = False

            # After checking, make the move
            self.pos_x = Head.prev_x
            self.pos_y = Head.prev_y


        elif (move_closer_x or move_closer_y) and Head.moved_dig:
            if (H_px - self.pos_x) == 0 or (H_py - self.pos_y) == 0:

                if (H_px - self.pos_x) == 0:
                    if (H_py - self.pos_y) > 0:
                        self.pos_y += 1
                    else:
                        self.pos_y -= 1

                if (H_py - self.pos_y) == 0:
                    if (H_px - self.pos_x) > 0:
                        self.pos_x += 1
                    else:
                        self.pos_x -= 1

            else:
                if (H_px - self.pos_x) > 0:
                    self.pos_x += 1
                    self.moved_dig = True
                else:
                    self.pos_x -= 1
                    self.moved_dig = True

                if (H_py - self.pos_y) > 0:
                    self.pos_y += 1
                    self.moved_dig = True
                else:
                    self.pos_y -= 1
                    self.moved_dig = True

        else:
            pass # Dont move


        if self.last_tail:
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

    number_of_steps = len(chaser1.history)
    number_of_unique = len(set(chaser1.history))


    return number_of_unique

def print_test_grid(head, tail_list, start):
    test_grid = []
    xM = 26
    yM = 21

    for y in range(yM):
        row = []
        for x in range(xM):
            row.append(".")
        test_grid.append(row)

    test_grid[start[1]][start[0]] = 'S'

    count = 9
    for tail in tail_list:
        test_grid[tail.pos_y][tail.pos_x] = str(count)
        count -= 1

    test_grid[head.pos_y][head.pos_x] = 'H'

    for y in range(len(test_grid)-1, -1, -1):
        for x in range(0, len(test_grid[0])):
            if x != len(test_grid[0])-1:
                print(test_grid[y][x], end =" ")
            else:
                print(test_grid[y][x])

    print(" ")


def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    moves = []
    for line in lines:
        dir, speed = line.split(' ')
        new_move = step(dir, speed)
        moves.append(new_move)

    start = [0,0]
    start = [11,5]

    player1 = player(start[0], start[1])
    tail1   = Tail(start[0], start[1], False)
    tail2   = Tail(start[0], start[1], False)
    tail3   = Tail(start[0], start[1], False)
    tail4   = Tail(start[0], start[1], False)
    tail5   = Tail(start[0], start[1], False)
    tail6   = Tail(start[0], start[1], False)
    tail7   = Tail(start[0], start[1], False)
    tail8   = Tail(start[0], start[1], False)
    tail9   = Tail(start[0], start[1], True)
    # chaser1.history.append('00')

    for move in moves:
        for i in range(1, move.speed +1):
            # tail_list = [tail9, tail8, tail7, tail6, tail5, tail4, tail3, tail2, tail1]
            # print_test_grid(player1, tail_list, start)

            player1.save_pos()
            player1.move_player(move.dir)
            tail1.chase_player(player1)
            tail2.chase_player(tail1)
            tail3.chase_player(tail2)
            tail4.chase_player(tail3)
            tail5.chase_player(tail4)
            tail6.chase_player(tail5)
            tail7.chase_player(tail6)
            tail8.chase_player(tail7)
            tail9.chase_player(tail8)



    number_of_steps = len(tail9.history)
    number_of_unique = len(set(tail9.history))


    return number_of_unique

