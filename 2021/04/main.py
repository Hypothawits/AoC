import time
import os
from day4p1 import *

print("Program Start")

current_day = "04"
test = 1

working_directory = os.getcwd()  + "\\2021\\" + current_day + "\\"

# start timer
start_clock = time.perf_counter()

# call function
result = day4p1(test, working_directory)

# end timer
stop_clock = time.perf_counter()

# print time
print(f" day took: {stop_clock - start_clock:0.6f} seconds")

# print answer
print("Result: ")
print(result)
