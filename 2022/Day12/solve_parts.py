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

    START = 27
    END = 0

    map = []
    node_map = []
    for line in lines:
        row = []
        for a in line:
            row.append(a)
        map.append(row)
    for y in range(len(map)):
        row_n = []
        for x in range(len(map[0])):
            map[y][x] = "EabcdefghijklmnopqrstuvwxyzS".find(map[y][x])
            row_n.append(node(pos(y,x),0,0,0,0))
            if map[y][x] == START:
                STARTp = pos(y, x)
                map[y][x] = 1

            if map[y][x] == END:
                ENDp = pos(y,x)


        node_map.append(row_n)

    for y in range(len(map)):
        for x in range(len(map[0])):
            node_up, node_down, node_left, node_right = move_options( map, node_map[y][x].pos )
            if node_up:     node_map[y][x].node_up    = node_map[node_up.y   ][node_up.x   ]
            if node_down:   node_map[y][x].node_down  = node_map[node_down.y ][node_down.x ]
            if node_left:   node_map[y][x].node_left  = node_map[node_left.y ][node_left.x ]
            if node_right:  node_map[y][x].node_right = node_map[node_right.y][node_right.x]


    start_node = node_map[STARTp.y][STARTp.x]
    end_node = node_map[ENDp.y][ENDp.x]

    current_node = start_node
    path = []

    found = search_tree (end_node, current_node, path)


    result = len(path)
    print(result)
    return result

def search_tree (end_node, current_node, path):
    current_node.visited = 1
    path.append(current_node.pos)
    found = False

    if current_node == end_node:
        found = True
        return found

    if current_node.node_up and not found:
        if current_node.node_up.visited == 0:
            current_node = current_node.node_up
            found = search_tree (end_node, current_node, path)

    if current_node.node_down and not found:
        if current_node.node_down.visited == 0:
            current_node = current_node.node_down
            found = search_tree (end_node, current_node, path)

    if current_node.node_left and not found:
        if current_node.node_left.visited == 0:
            current_node = current_node.node_left
            found = search_tree (end_node, current_node, path)

    if current_node.node_right and not found:
        if current_node.node_right.visited == 0:
            current_node = current_node.node_right
            found = search_tree (end_node, current_node, path)


    if found == 0:
        # No end found, dead end, return to try a differet path
        path.pop(-1)
        return found
    else:
        # You've hopefully got a correct path now
        return found



def build_tree(map, tree):
    # Find possible connections
    print(str(tree.pos.x) + " " + str(tree.pos.y))
    node_up, node_down, node_left, node_right = move_options(map, tree.pos)

    # if a connect and not already known
    if node_up and not tree.node_up:
        tree.node_up = node(node_up,     0, tree, 0,0)
        build_tree(map, tree.node_up)

    if node_down and not tree.node_down:
        tree.node_down = node(node_down, tree, 0,0,0)
        build_tree(map, tree.node_down)

    if node_left and not tree.node_left:
        tree.node_left = node(node_left,  0,0,0, tree)
        build_tree(map, tree.node_left)

    if node_right and not tree.node_right:
        tree.node_right = node(node_right, 0,0, tree,0)
        build_tree(map, tree.node_right)




def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)



    return -1

