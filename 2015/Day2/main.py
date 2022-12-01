import time
import os
import sys
from pathlib import Path
from solve_parts import part_one, part_two

print("Program Start")

CURRENT_DAY = 2
RUN_TEST = 0
RUN_PART_TWO = 1

TEST_ANSWER_ONE = 58 + 43
TEST_ANSWER_TWO = 48

ANSWER_ONE = 1606483
ANSWER_TWO = 3842356


working_directory = os.getcwd()  + "\\2015\\Day" + str(CURRENT_DAY) + "\\"

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
            print("Part Two Results Match!  :: " + str(test_result_two))
        else:
            print("Oops! you got it wrong! Expecting: " + str(TEST_ANSWER_TWO) \
                                       + " but I got: " + str(test_result_two))
    else:
        pass
else:
    file_path =  working_directory + "input\\input.txt"
    result = part_one(file_path)
    print("Part One Results: " + str(result))

    if ANSWER_ONE:
        assert result == ANSWER_ONE

    if RUN_PART_TWO:
        result_two = part_two(file_path)
        print("Part Two Results: " + str(result_two))
        if ANSWER_TWO:
            assert result_two == ANSWER_TWO
                
    else:
        pass

stop_clock = time.perf_counter()

# print time
print(f" day took: {stop_clock - start_clock:0.6f} seconds")
