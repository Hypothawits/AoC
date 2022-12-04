import math


def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def search_bags(bag1, bag2, bag3):
    for item_b1 in bag1:
            for item_b2 in bag2:
                if item_b1 == item_b2:
                    for item_b3 in bag3:
                        if item_b1 == item_b2 and item_b2 == item_b3:
                            return item_b1

def part_one(file_path):
    """ Day one part one solution """

    lines = open_file(file_path)

    # First half string = compartment 1
    # second half string = compartment 2

    score_codes = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'    
    common_items = []

    for line in lines:
        begin = 1
        middle = int(len(line)/2)
        end = len(line)
        compartment_one = line[begin -1: middle]
        compartment_two = line[middle : end]

        #Find common part       
        for item in compartment_one:
            if compartment_two.find(item) != -1:
                common_items.append(item)
                break

    print(common_items)
        
    total_score = 0
    for item in common_items:
        score = score_codes.find(item) +1
        total_score += score


    return total_score

def part_two(file_path):
    """ Day one part two solution """

    lines = open_file(file_path)

    common_items = []

    for i in range(0, len(lines), 3):
        print(i)

    for i in range(0, len(lines), 3):
        bag1 = lines[i]
        bag2 = lines[i+1]
        bag3 = lines[i+2]

        # B is alowed in all three, but the symbol is broke, so find it
        # at most two bags will have any other items

        #Find common part       
        common_items.append(search_bags(bag1, bag2, bag3))
        

    print(common_items)
    score_codes = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'    
    
    total_score = 0
    for item in common_items:
        score = score_codes.find(item) +1
        total_score += score

    return total_score
