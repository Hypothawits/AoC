import math
from collections import Counter

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    # lines = f.read().splitlines()
    lines = f.readlines()
    return lines


def check_for_match(window):
    counter_obj = Counter(window)
    number_unique = len(counter_obj.keys())
    number_list = len(window)

    if number_unique < number_list:
        return True # there is a match


def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    for line in lines:
        for i in range(0, len(line), 1):
            a = line[i]
            b = line[i+1]
            c = line[i+2]
            d = line[i+3]

            check = check_for_match([a,b,c,d])
            if not check:
                break
    
    return i+1+3

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    for line in lines:
        for i in range(0, len(line), 1):
            window = []
            for x in range(14):
                window.append(line[i+x])
            check = check_for_match(window)
            # print(window)
            if not check:
                break
    
    return i+14
