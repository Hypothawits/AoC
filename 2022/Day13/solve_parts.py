import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines


def check_score(score, cycle, X):
    if not (( (cycle+1) +20 ) % 40):
        score+=(cycle+1) * (X[-1])
        # print( str(cycle+1) + " : " + str( (cycle+1) * X[-1]) )
        return score
    return score


def pos_to_XY(pos, W, H):
    x = pos % W
    temp = math.floor(pos/(W*H))
    y = math.floor(pos / W) - temp*H
    return [x,y]

class item():
    def __init__(self, worry_level):
        self.worry_level = worry_level

    def update_worry(self, x):
        self.worry_level = x

class pos():
    def __init__(self, y, x):
        self.x = x
        self.y = y

class Player():
    def __init__(self, name):
        self.name = name
        self.pos = 1
        self.goal = 1
        self.path = []
        self.have_been = []


class node():
    def __init__(self, position, node_up, node_down, node_left, node_right):
        self.pos        = position
        self.node_up    = node_up
        self.node_down  = node_down
        self.node_left  = node_left
        self.node_right = node_right
        self.visited = False







def move_options(map, npos):
    max_x = len(map[0])
    max_y = len(map)

    current = map[npos.y][npos.x]


    can_move_u = False
    can_move_d = False
    can_move_l = False
    can_move_r = False


    if npos.x -1 < 0: # cant move off map
        can_move_l = False
    else:
        is_lower   = map[npos.y][npos.x-1] <= current
        can_higher = (map[npos.y][npos.x-1] - current) == 1
        can_move_l = is_lower or can_higher


    if npos.y -1 < 0:# cant move off map
        can_move_u = False
    else:
        is_lower   = map[npos.y-1][npos.x] <= current
        can_higher = (map[npos.y-1][npos.x] - current) == 1
        can_move_u = is_lower or can_higher

    if npos.x +1 >= max_x: # cant move off map
        can_move_r = False
    else:
        is_lower   = map[npos.y][npos.x+1] <= current
        can_higher = (map[npos.y][npos.x+1] - current) == 1
        can_move_r = is_lower or can_higher


    if npos.y +1 >= max_y: # cant move off map
        can_move_d = False
    else:
        is_lower   = map[npos.y+1][npos.x] <= current
        can_higher = (map[npos.y+1][npos.x] - current) == 1
        can_move_d = is_lower or can_higher

    # check if visited before


    if can_move_u: can_move_u = pos(npos.y-1, npos.x)
    if can_move_d: can_move_d = pos(npos.y+1, npos.x)
    if can_move_l: can_move_l = pos(npos.y, npos.x-1)
    if can_move_r: can_move_r = pos(npos.y, npos.x+1)

    return [can_move_u, can_move_d, can_move_l, can_move_r]


def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    return -1

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    return -1

