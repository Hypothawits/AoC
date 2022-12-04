import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    count = 0
    for line in lines:
        # 2-4,6-8
        first_elf, second_elf = line.split(',')
        first_elf = first_elf.split('-')
        second_elf = second_elf.split('-')

        first_start = int(first_elf[0])
        first_end   = int(first_elf[1])

        second_start = int(second_elf[0])
        second_end   = int(second_elf[1])

        if first_start <= second_start and first_end >= second_end:
            count += 1
        elif first_start >= second_start and first_end <= second_end:
            count += 1
        else:
            pass


    return count

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    count = 0
    for line in lines:
        # 2-4,6-8
        first_elf, second_elf = line.split(',')
        first_elf = first_elf.split('-')
        second_elf = second_elf.split('-')

        first_start = int(first_elf[0])
        first_end   = int(first_elf[1])

        second_start = int(second_elf[0])
        second_end   = int(second_elf[1])


        if first_start <= second_start and first_end >= second_end:
            count += 1
        elif first_start >= second_start and first_end <= second_end:
            count += 1
        elif first_start <= second_start and second_start<= first_end:
            count += 1
        elif first_start <= second_end and second_end<= first_end:
            count += 1
        else:
            pass


    return count
