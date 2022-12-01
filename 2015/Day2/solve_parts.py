import math

def open_file(file_path):
    """Open the file and return the lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def find_surface_area(L, W, H):
    return 2*(W*(L + H) + H*L)

def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    total_paper = 0
    for line in lines:
        split_line = line.split('x')
        L = int(split_line[0])
        W = int(split_line[1])
        H = int(split_line[2])

        # min_side = L if L < W else W
        LW = L*W
        WH = W*H
        HL = H*L

        min_side =  min(LW, WH, HL)

        prez_surface = find_surface_area(L, W, H)
        total_paper += prez_surface + min_side

    return total_paper

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    total_ribbon = 0
    for line in lines:
        split_line = line.split('x')
        L = int(split_line[0])
        W = int(split_line[1])
        H = int(split_line[2])

        LW = L+W
        WH = W+H
        HL = H+L
        ribbon = min(LW, WH, HL ) * 2
        bow = L*W*H

        sub_total = ribbon + bow
        total_ribbon += sub_total

    return total_ribbon
