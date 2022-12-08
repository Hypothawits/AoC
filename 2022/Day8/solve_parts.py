import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines


class tree():
    def __init__(self, tree_size):
        self.size           = tree_size
        self.is_seen        = True
        self.on_edge        = False

        self.blocked_up     = False
        self.blocked_down   = False
        self.blocked_left   = False
        self.blocked_right  = False

        self.up_can_see     = 0
        self.down_can_see   = 0
        self.left_can_see   = 0
        self.right_can_see  = 0

def convol(board, x, y, range):
    tree_test = board[y][x]
    if tree_test.on_edge == True:
        return
    if tree_test.is_seen == False:
        return

    # Keep checks in bound of board

    y_U =  0 if y - range < 0 else y - range
    y_D =  len(board)-1 if y + range > len(board)-1 else y + range

    x_L = 0 if x - range < 0 else x - range
    x_R = len(board[0])-1 if x + range > len(board[0])-1 else x + range

    # Get the Tree
    tree_up    = board[y_U][x]
    tree_down  = board[y_D][x]
    tree_left  = board[y][x_L]
    tree_right = board[y][x_R]

    # Check blockage from each direction
    if tree_up.size >= tree_test.size:
        if tree_test.blocked_up != True:
            tree_test.blocked_up = True

    if tree_down.size >= tree_test.size:
        if tree_test.blocked_down != True:
            tree_test.blocked_down = True

    if tree_left.size >= tree_test.size:
        if tree_test.blocked_left != True:
            tree_test.blocked_left = True

    if tree_right.size >= tree_test.size:
        if tree_test.blocked_right != True:
            tree_test.blocked_right = True

    # check if total blockage
    if tree_test.blocked_up & tree_test.blocked_down & tree_test.blocked_left & tree_test.blocked_right:
        tree_test.is_seen = False

def convol2(board, x, y, range):
    tree_test = board[y][x]
    if tree_test.on_edge == True:
        return

    # Keep checks in bound of board

    y_U =  0 if y - range < 0 else y - range
    y_D =  len(board)-1 if y + range > len(board)-1 else y + range

    x_L = 0 if x - range < 0 else x - range
    x_R = len(board[0])-1 if x + range > len(board[0])-1 else x + range

    # Get the Tree
    tree_up    = board[y_U][x]
    tree_down  = board[y_D][x]
    tree_left  = board[y][x_L]
    tree_right = board[y][x_R]

    # Check blockage from each direction
    if tree_test.blocked_up != True:
        tree_test.up_can_see += 0 if y - range < 0 else 1
        if tree_up.size >= tree_test.size:
            tree_test.blocked_up = True

    if tree_test.blocked_down != True:
        tree_test.down_can_see += 0 if y + range > len(board)-1 else 1
        if tree_down.size >= tree_test.size:
            tree_test.blocked_down = True

    if tree_test.blocked_left != True:
        tree_test.left_can_see += 0 if x - range < 0 else 1
        if tree_left.size >= tree_test.size:
            tree_test.blocked_left = True

    if tree_test.blocked_right != True:
        tree_test.right_can_see += 0 if x + range > len(board[0])-1 else 1
        if tree_right.size >= tree_test.size:
            tree_test.blocked_right = True


    # check if total blockage
    if tree_test.blocked_up & tree_test.blocked_down & tree_test.blocked_left & tree_test.blocked_right:
        tree_test.is_seen = False

def scenic_score(tree_test):
    return  tree_test.up_can_see    * \
            tree_test.down_can_see  * \
            tree_test.left_can_see  * \
            tree_test.right_can_see




def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    board = []

    for line in lines:
        row = []
        track_row = []
        for tree_size in line:
            row.append(tree(int(tree_size)))
        board.append(row)

    # print(board)

    # Let the out edge to SEEN
    for x in [0, len(board[0])-1]:
        for y in range(len(board) ):
            board[y][x].on_edge = True

    for y in [0, len(board)-1]:
        for x in range(len(board[0]) ):
            board[y][x].on_edge = True


    sum_edges = 0
    for x in range(len(board[0]) ):
        for y in range(len(board) ):
            sum_edges += board[y][x].on_edge

    assert sum_edges == 4*len(board[0]) -4

    for search_range in range(1,len(board[0])):
        for x in range(len(board[0]) ):
            for y in range(len(board) ):
                convol(board, x, y, search_range)

    count = 0
    for x in range(len(board[0]) ):
        for y in range(len(board) ):
            count += board[y][x].is_seen

    return count

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    forest = []

    for line in lines:
        row = []
        track_row = []
        for tree_size in line:
            row.append(tree(tree_size))
        forest.append(row)

    # print(board)

    # Let the out edge to SEEN
    for x in [0, len(forest[0])-1]:
        for y in range(len(forest) ):
            forest[y][x].on_edge = True

    for y in [0, len(forest)-1]:
        for x in range(len(forest[0]) ):
            forest[y][x].on_edge = True


    sum_edges = 0
    for x in range(len(forest[0]) ):
        for y in range(len(forest) ):
            sum_edges += forest[y][x].on_edge

    assert sum_edges == 4*len(forest[0]) -4

    # check the trees
    for search_range in range(1,len(forest[0])):
        for x in range(len(forest[0]) ):
            for y in range(len(forest) ):
                convol2(forest, x, y, search_range)

    score_list = []
    for x in range(len(forest[0])):
        for y in range(len(forest)):
            score_list.append(scenic_score(forest[y][x]))

    return max(score_list)

