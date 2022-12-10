import time
import os
import sys
from pathlib import Path
from solve_parts import part_one, part_two

print("Program Start")

CURRENT_DAY = "10"
RUN_TEST = 0
RUN_PART_TWO = 1

ANSWER_ONE = 14720
ANSWER_TWO = 'a' # no easy test answer today

TEST_ANSWER_ONE = 13140
TEST_ANSWER_TWO = 'a' # no easy test answer today


working_directory = os.getcwd()  + "\\2022\\Day" + CURRENT_DAY + "\\"

start_clock = time.perf_counter()

if RUN_TEST:
    file_path = working_directory + "input\\test.txt"
    test_result = part_one(file_path)

    if TEST_ANSWER_ONE == test_result:
        print("Part One Results Match!  :: " + str(test_result))
    else:
        print("Oops! you got it wrong! Expecting: " + str(TEST_ANSWER_ONE) \
                                   + " but I got: " + str(test_result))

    if RUN_PART_TWO:
        test_result_two = part_two(file_path)
        if TEST_ANSWER_TWO == test_result_two:
            print("Part Two Results Match!: " + str(test_result_two))
        else:
            print("Oops! you got it wrong! Expecting: " + str(TEST_ANSWER_TWO) \
                                       + " but I got: " + str(test_result_two))
    else:
        pass
else:
    file_path =  working_directory + "input\\input.txt"
    result = part_one(file_path)
    print("Part One Results: " + str(result))

    if ANSWER_ONE != 'a':
        print("Part One result correct: " + str(ANSWER_ONE == result) )

    if RUN_PART_TWO:
        result_two = part_two(file_path)
        print("Part Two Results: " + str(result_two))
        if ANSWER_TWO != 'a':
            print("Part Two result correct: " + str(ANSWER_TWO == result_two) )

    else:
        pass

stop_clock = time.perf_counter()

# print time
print(f"  Day took: {stop_clock - start_clock:0.6f} seconds")
# 801867 too low =(
