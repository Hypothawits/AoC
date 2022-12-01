import math

def open_file(file_path):
    """Open the file and return the lines"""
    f = open( file_path, "r")
    lines = f.read()
    return lines


def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    sum = 0

    for c in lines:
        if c == '(':
            sum += 1
        else:
            sum -= 1

    return sum

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    sum = 0
    pos = 0
    for c in lines:
        pos += 1
        if c == '(':
            sum += 1
        else:
            sum -= 1

        if sum == -1:
            return pos

    return -1
