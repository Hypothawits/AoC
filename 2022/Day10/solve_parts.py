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

    # if pos >= W*H:
    #     print("need to overflow")

    x = pos % W
    temp = math.floor(pos/(W*H))
    y = math.floor(pos / W) - temp*H
    return [x,y]

def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    X = [1]
    cycle_count = 0
    sum_signal_score = 0
    for line in lines:
        command = line.split(' ')
        if len(command) == 2:
            code, data = command
        else:
            code = command[0]


        if code == "addx":
            X.append(X[cycle_count])
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)

            X.append(X[-1] + int(data))
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)

        elif code == "noop":
            X.append(X[cycle_count])
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)
        else:
            print("[ERROR]")

    return sum_signal_score

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    X = [1]
    cycle_count = 0
    sum_signal_score = 0
    for line in lines:
        command = line.split(' ')
        if len(command) == 2:
            code, data = command
        else:
            code = command[0]


        if code == "addx":
            X.append(X[cycle_count])
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)

            X.append(X[-1] + int(data))
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)

        elif code == "noop":
            X.append(X[cycle_count])
            cycle_count +=1
            sum_signal_score = check_score(sum_signal_score, cycle_count, X)
        else:
            print("[ERROR]")

    CRT_size = [40, 6] # width, height
    # draw left-to-right
    # 0 - 39
    # 1 pixel per cycle

    CRT = []
    for y in range(0, CRT_size[1]):
        row = []
        for x in range(0, CRT_size[0]):
            row.append('.')
        CRT.append(row)

    # X hold horizontal position of ### on cycle (middle)

    for CRT_pos in range(0, len(X)):
        x,y = pos_to_XY(CRT_pos, CRT_size[0], CRT_size[1])

        sprite_pos = X[CRT_pos]
        # in theory, sprite pos can got off side ans still be visible,
        # so <=
        assert sprite_pos <= 40

        draw = False
        if sprite_pos-1 <= x and x <= sprite_pos+1:
            draw = True
            CRT[y][x] = int(draw) * 0
        # else:
        #     draw = False
            # CRT[y][x] = '.'


    for y in range(0, CRT_size[1]):
        for x in range(0, CRT_size[0]):
            if x != CRT_size[0]-1:
                print(CRT[y][x], end =" ")
            else:
                print(CRT[y][x])



    return 1

