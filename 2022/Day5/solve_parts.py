import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    found_end_of_board = -1
    for i in range( len(lines) ):
        if lines[i] == '':
            found_end_of_board = i
            break

    board = []
    board_input = []
    for i in range(found_end_of_board-1):
        board_input.append(lines[i])

    board_length = len(board_input[0])

    # Build and transpose board
    for x in range(1, board_length, +4):
        # print("x:" + str(x))
        board_line = []
        for y in range(found_end_of_board-2, -1, -1):
            # print("y:" + str(y))
            board_line.append(board_input[y][x])
        board.append(board_line)

    #remove ' ' charaters
    for board_line in board:
        while board_line[len(board_line)-1] == ' ':
            board_line.pop()

    # collect instructions
    instructions = []
    for i in range(found_end_of_board+1, len(lines) ):
        split_output = lines[i].split(' ')
        instructions.append([int(split_output[1]), int(split_output[3]), int(split_output[5])])

    # Run instructions
    # move N from X to Xn
    for instruction in instructions:
        N, X, Xn = instruction
        for i in range(N):
            board[Xn-1].append(board[X-1].pop())

    # Get answer out
    result = []
    for board_line in board:
        result.append(board_line.pop())
    result_str = ''.join(result)
    return result_str

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    found_end_of_board = -1
    for i in range( len(lines) ):
        if lines[i] == '':
            found_end_of_board = i
            break

    board = []
    board_input = []
    for i in range(found_end_of_board-1):
        board_input.append(lines[i])

    board_length = len(board_input[0])

    # Build and transpose board
    for x in range(1, board_length, +4):
        # print("x:" + str(x))
        board_line = []
        for y in range(found_end_of_board-2, -1, -1):
            # print("y:" + str(y))
            board_line.append(board_input[y][x])
        board.append(board_line)

    #remove ' ' charaters
    for board_line in board:
        while board_line[len(board_line)-1] == ' ':
            board_line.pop()

    # collect instructions
    instructions = []
    for i in range(found_end_of_board+1, len(lines) ):
        split_output = lines[i].split(' ')
        instructions.append([int(split_output[1]), int(split_output[3]), int(split_output[5])])

    # Run instructions

    # move N from X to Xn
    for instruction in instructions:
        N, X, Xn = instruction
        line_length = ( len(board[X-1]) )
        for i in range(N):
            index = line_length - N
            board[Xn-1].append(board[X-1].pop(index))



    # Get answer out
    result = []
    for board_line in board:
        result.append(board_line.pop())
    result_str = ''.join(result)
    return result_str
