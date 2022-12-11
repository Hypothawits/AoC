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

class item():
    def __init__(self, worry_level):
        self.worry_level = worry_level

    def update_worry(self, x):
        self.worry_level = x

class Monkey():
    def __init__(self, name):
        self.name = name
        self.items = []                 # list in order of "inspection"
        self.op_inst = []               # How item worry changes as item inspected
        self.div_test_val = 1           # Test to see which monkey will recive item next
        self.div_test_result = False
        self.true_monkey = -1           # True monkey
        self.false_monkey = -1          # False monkey
        self.inspect_count = 0
        self.common_div = 0

    def inspect(self):
        self.inspect_count +=1
        # input_0 = self.op_inst[0]
        op_code = self.op_inst[1]
        input_1 = self.op_inst[2]

        input_0 = self.items[0].worry_level
        if input_1 == "old":
            input_1 = self.items[0].worry_level
        else:
            input_1 = int(input_1)

        if op_code == "+":
            val = input_0 + input_1
            self.items[0].update_worry(val)

        if op_code == "*":
            val = input_0 * input_1
            self.items[0].update_worry(val)

    def bored(self):
        val = math.floor(self.items[0].worry_level / 3)
        self.items[0].update_worry(val)

    def bored_p2(self):
        val = math.floor(self.items[0].worry_level) % self.common_div
        self.items[0].update_worry(val)

    def test_item(self):
        div = self.items[0].worry_level % self.div_test_val
        val = not bool(div)
        self.div_test_result = val

    def throw_item(self):
        if self.div_test_result:
            self.true_monkey.items.append(self.items.pop(0))
        else:
            self.false_monkey.items.append(self.items.pop(0))


def fix_numbers(number_list):
    result_list = []
    for number in number_list:
        result_list.append( int(number.split(",")[0]) )
    return result_list


def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    found_end_of_monkey = -1
    monkey_list = []
    for line in lines:
        line_split = line.split(" ")

        #remove '' charaters
        if len(line_split) > 1:         # test if empty line
            while line_split[0] == '':
                line_split.pop(0)

        if line_split[0] == "Monkey":
            #found new monkey
            name = line_split[1].split(":")[0]
            new_monkey = Monkey(int(name))
            monkey_list.append(new_monkey)
        else:
            if line_split[0] == "Starting":
                line_split.pop(0)
                line_split.pop(0)

                number_list = fix_numbers(line_split)
                item_list = []
                for i in number_list:
                   item_list.append(item(i))
                monkey_list[-1].items = item_list

            elif line_split[0] == "Operation:":
                line_split.pop(0)
                line_split.pop(0)
                line_split.pop(0)
                monkey_list[-1].op_inst = line_split
                pass

            elif line_split[0] == "Test:":
                monkey_list[-1].div_test_val = int(line_split[-1])

            elif line_split[0] == "If":
                if line_split[1] == "true:":
                    monkey_list[-1].true_monkey = int(line_split[-1])
                else: # "false:"
                    monkey_list[-1].false_monkey = int(line_split[-1])

            elif line_split[0] == '':
                pass # new line do nothing

            else:
                print("[ERROR] Unknown Monkey Line")

    # update index to actual objects... probably
    common_div = 1
    for monkey in monkey_list:
        monkey.true_monkey  = monkey_list[monkey.true_monkey ]
        monkey.false_monkey = monkey_list[monkey.false_monkey]
        common_div *= monkey.div_test_val

    for monkey in monkey_list:
        monkey.common_div = common_div
    # Monkey inspect item
    # My worry div by 3, Floored
    # Object thrown, item added to end of monkey list
    # Moves onto next item in list

    num_rounds = 20
    for round in range(num_rounds):
        for monkey in monkey_list:
            while len(monkey.items) >0:
                monkey.inspect()
                monkey.bored()
                monkey.test_item()
                monkey.throw_item()

    inspect = []
    for monkey in monkey_list:
        inspect.append(monkey.inspect_count)

    inspect.sort(reverse = True)
    result = inspect[0] * inspect[1]

    return result

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    found_end_of_monkey = -1
    monkey_list = []
    for line in lines:
        line_split = line.split(" ")

        #remove '' charaters
        if len(line_split) > 1:         # test if empty line
            while line_split[0] == '':
                line_split.pop(0)

        if line_split[0] == "Monkey":
            #found new monkey
            name = line_split[1].split(":")[0]
            new_monkey = Monkey(int(name))
            monkey_list.append(new_monkey)
        else:
            if line_split[0] == "Starting":
                line_split.pop(0)
                line_split.pop(0)

                number_list = fix_numbers(line_split)
                item_list = []
                for i in number_list:
                   item_list.append(item(i))
                monkey_list[-1].items = item_list

            elif line_split[0] == "Operation:":
                line_split.pop(0)
                line_split.pop(0)
                line_split.pop(0)
                monkey_list[-1].op_inst = line_split
                pass

            elif line_split[0] == "Test:":
                monkey_list[-1].div_test_val = int(line_split[-1])

            elif line_split[0] == "If":
                if line_split[1] == "true:":
                    monkey_list[-1].true_monkey = int(line_split[-1])
                else: # "false:"
                    monkey_list[-1].false_monkey = int(line_split[-1])

            elif line_split[0] == '':
                pass # new line do nothing

            else:
                print("[ERROR] Unknown Monkey Line")

    # update index to actual objects... probably
    common_div = 1
    for monkey in monkey_list:
        monkey.true_monkey  = monkey_list[monkey.true_monkey ]
        monkey.false_monkey = monkey_list[monkey.false_monkey]
        common_div *= monkey.div_test_val

    for monkey in monkey_list:
        monkey.common_div = common_div

    # Monkey inspect item
    # My worry div by 3, Floored
    # Object thrown, item added to end of monkey list
    # Moves onto next item in list

    num_rounds = 10000
    for round in range(num_rounds):
        for monkey in monkey_list:
            while len(monkey.items) >0:
                monkey.inspect()
                monkey.bored_p2()
                monkey.test_item()
                monkey.throw_item()
        # if not (round % 1000) :
        #     print("round: " + str(round))

    inspect = []
    for monkey in monkey_list:
        inspect.append(monkey.inspect_count)

    inspect.sort(reverse = True)
    result = inspect[0] * inspect[1]

    return result

