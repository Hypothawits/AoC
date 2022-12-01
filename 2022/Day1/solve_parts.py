import math

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def sort_into_bags(input):
    elf_bags = [0]
    elf_id = 0
    for line in input:
        if line == '':
            elf_id +=1
            elf_bags.append(0)
        else:
            elf_bags[elf_id] += int(line)
    return elf_bags

def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    elf_bags = sort_into_bags(lines)

    max_bag = max(elf_bags)

    return max_bag

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    elf_bags = sort_into_bags(lines)

    elf_bags.sort(reverse=True)
    
    result = elf_bags[0] + elf_bags[1] + elf_bags[2]

    return result

