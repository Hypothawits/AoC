import math
from collections import Counter

def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.read().splitlines()
    return lines

def count_unique(obj_list):
    counter_obj = Counter(obj_list)
    number_unique = len(counter_obj.keys())
    return number_unique

def pos_to_XY(pos, W, H):
    x = pos % W
    temp = math.floor(pos/(W*H))
    y = math.floor(pos / W) - temp*H
    return [x,y]

class Pos():
    def __init__(self, y, x):
        self.x = x
        self.y = y

def mHat_dis(pos1, pos2):
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y)

def how_far_to_skip(pos1, sensor):

    found_pos = pos1
    pos2 = sensor.pos

    x_dif = abs(pos1.x - pos2.x)
    y_dif = abs(pos1.y - pos2.y)

    skip_x  = 'a'
    if pos1.x - pos2.x >= 0:
        skip_x = sensor.distance -x_dif -y_dif
    elif pos1.x - pos2.x < 0:
        skip_x = x_dif + sensor.distance -y_dif
    else:
        assert skip_x != 'a'

    return skip_x


class Sensor():
    def __init__(self, pos, beacon, distance, index = -1):
        self.index = index
        self.pos = pos
        self.beacon = beacon
        self.distance = distance

class Beacon():
    def __init__(self, pos, index = -1):
        self.index = index
        self.pos = pos

def print_grid(grid):
    grid_size_x = len(grid[0])
    grid_size_y = len(grid)
    for y in range(0, grid_size_y):
        for x in range(0, grid_size_x):
            if x != grid_size_x-1:
                print(str(grid[y][x]), end =" ")
            else:
                print(str(grid[y][x]))

def in_range(r_min, r_max, x):
    return (r_min <= x and x <= r_max)

def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    sensor_list = []

    for line in lines:
        split_lines = line.split(" ")
        sensor_x_part = split_lines[2]
        sensor_y_part = split_lines[3]

        beacon_x_part = split_lines[8]
        beacon_y_part = split_lines[9]

        sensor_x_part = int(sensor_x_part[2:len(sensor_x_part)-1])
        sensor_y_part = int(sensor_y_part[2:len(sensor_y_part)-1])
        beacon_x_part = int(beacon_x_part[2:len(beacon_x_part)-1])
        beacon_y_part = int(beacon_y_part[2:len(beacon_y_part)])

        bPos = Pos(beacon_y_part, beacon_x_part)
        sPos = Pos(sensor_y_part,sensor_x_part)

        distance = mHat_dis(sPos, bPos)

        new_beacon = Beacon(bPos)
        new_sensor = Sensor(sPos, new_beacon, distance, len(sensor_list))
        sensor_list.append(new_sensor)

    max_x , min_x = 0, 0
    max_y , min_y = 0, 0
    for sensor in sensor_list:
        max_x = max(max_x, sensor.pos.x, sensor.beacon.pos.x)
        max_y = max(max_y, sensor.pos.y, sensor.beacon.pos.y)
        min_x = min(min_x, sensor.pos.x, sensor.beacon.pos.x)
        min_y = min(min_y, sensor.pos.y, sensor.beacon.pos.y)

    print("x:" + str(max_x) + " " + str(min_x) + " y:" + str(max_y) + " " + str(min_y) )

    x_range = abs(max_x) + abs(min_x)
    y_range = abs(max_y) + abs(min_y)

    # debug = True
    debug = False
    if debug:
        print("I'm trying to make a graph!")
        grid = []
        for y in range(0, y_range+1):
            row = []
            for x in range(0, x_range+1):
                row.append('.')
            grid.append(row)

        for sensor in sensor_list:
            sPy = sensor.pos.y + abs(min_y)
            sPx = sensor.pos.x + abs(min_x)
            bPy = sensor.beacon.pos.y + abs(min_y)
            bPx = sensor.beacon.pos.x + abs(min_x)

            grid[sPy][sPx] = str(sensor.index)
            grid[bPy][bPx] = "B"

        print_grid(grid)

    row_num = 10 # y = 10
    # row_num = 2000000

    close_by_sensors = []

    # Does sensor range intersect with test row?
    for sensor in sensor_list:
        sPy = sensor.pos.y

        # is test_y in range sensor_y +- range
        test = in_range(sPy - sensor.distance, sPy + sensor.distance, row_num)
        if test:
            close_by_sensors.append(sensor)


    result_list = []
    for sensor in close_by_sensors:
        # each sensor will affect max +- range around pos.x
        # so test each x value in range*2 annd append to list x values
        # then count unique x values
        sPx = sensor.pos.x
        x_min = sPx - sensor.distance
        x_max = sPx + sensor.distance

        reached_end_at = 0
        for x in range(sPx, x_max+1):
            x_test = Pos(row_num, x)
            dis_2_sensor = mHat_dis(x_test, sensor.pos)

            if dis_2_sensor <= sensor.distance:
                result_list.append(x)
                # x_neg = x - (sPx-x)
                # result_list.append(x_neg)

            else:
                reached_end_at = x
                break # End reached

        # for x in range(sPx -(reached_end_at-sPx),sPx, 1):
        #     result_list.append(x)

        # Should be symetrical
        reached_end_at_2 = 0
        for x in range(sPx, x_min-1, -1):
            x_test = Pos(row_num, x)
            dis_2_sensor = mHat_dis(x_test, sensor.pos)

            if dis_2_sensor <= sensor.distance:
                result_list.append(x)
            else:
                reached_end_at_2 = x
                break # End reached

    #     print(".", end =" ")
    # print("")


    #Check is beacon is in way and over write x value

    beacons_in_way = []
    for sensor in sensor_list:
        # distance to sensor
        bPx = sensor.beacon.pos.x
        bPy = sensor.beacon.pos.y
        if bPy == row_num:
            beacons_in_way.append(sensor.beacon)

    for beacon in beacons_in_way:
        bX = beacon.pos.x
        debug = bX in result_list
        while bX in result_list:
            result_list.remove(bX)


    result = count_unique(result_list)

    return result


def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)


    BEACON_min_xy = 0
    # BEACON_max_xy = 20
    BEACON_max_xy = 4000000

    x_coord = -1
    y_coord = -1
    tuning_frew = x_coord * 4000000 + y_coord

    sensor_list = []

    for line in lines:
        split_lines = line.split(" ")
        sensor_x_part = split_lines[2]
        sensor_y_part = split_lines[3]

        beacon_x_part = split_lines[8]
        beacon_y_part = split_lines[9]

        sensor_x_part = int(sensor_x_part[2:len(sensor_x_part)-1])
        sensor_y_part = int(sensor_y_part[2:len(sensor_y_part)-1])
        beacon_x_part = int(beacon_x_part[2:len(beacon_x_part)-1])
        beacon_y_part = int(beacon_y_part[2:len(beacon_y_part)])

        bPos = Pos(beacon_y_part, beacon_x_part)
        sPos = Pos(sensor_y_part,sensor_x_part)

        distance = mHat_dis(sPos, bPos)

        new_beacon = Beacon(bPos)
        new_sensor = Sensor(sPos, new_beacon, distance, len(sensor_list))
        sensor_list.append(new_sensor)

    result = 0

    y = 0
    while y <= BEACON_max_xy:
        x = 0
        while x <= BEACON_max_xy:
            touched = False
            for sensor in sensor_list:
                sPx = sensor.pos.x
                x_min = sPx - sensor.distance
                x_max = sPx + sensor.distance

                x_test = Pos(y, x)
                dis_2_sensor = mHat_dis(x_test, sensor.pos)

                if dis_2_sensor <= sensor.distance:
                    touched = True
                    x += how_far_to_skip(x_test, sensor)
                    break
                # print("test")

            if touched == False:
                result =Pos(y, x)
                break
            x +=1
        #     print(".", end =" ")
        # print("")
        if result:
            break
        y +=1





    # for y in range(BEACON_min_xy, BEACON_max_xy):
    #     for x in range(BEACON_min_xy, BEACON_max_xy):
    #         touched = False
    #         for sensor in sensor_list:
    #             sPx = sensor.pos.x
    #             x_min = sPx - sensor.distance
    #             x_max = sPx + sensor.distance

    #             x_test = Pos(y, x)
    #             dis_2_sensor = mHat_dis(x_test, sensor.pos)

    #             if dis_2_sensor <= sensor.distance:
    #                 touched = True
    #                 break
    #             # print("test")

    #         if touched == False:
    #             result =Pos(y, x)
    #             break
    #     if result:
    #         break
    #     print(".", end =" ")
    # print("")

    print("found spot: x:" + str(result.x) + " y:" + str(result.y))

    return (result.x * 4000000) + result.y









    row_num_max = BEACON_max_xy

    result_grid = []
    for row_num in range(0, row_num_max+1):
        result_list = []
        for sensor in sensor_list:
            # each sensor will affect max +- range around pos.x
            # so test each x value in range*2 annd append to list x values
            # then count unique x values
            sPx = sensor.pos.x
            x_min = sPx - sensor.distance
            x_max = sPx + sensor.distance

            reached_end_at = 0
            for x in range(sPx, x_max+1):
                x_test = Pos(row_num, x)
                dis_2_sensor = mHat_dis(x_test, sensor.pos)

                if dis_2_sensor <= sensor.distance:
                    result_list.append(x)
                else:
                    reached_end_at = x
                    break # End reached

            reached_end_at_2 = 0
            for x in range(sPx, x_min-1, -1):
                x_test = Pos(row_num, x)
                dis_2_sensor = mHat_dis(x_test, sensor.pos)

                if dis_2_sensor <= sensor.distance:
                    result_list.append(x)
                else:
                    reached_end_at_2 = x
                    break # End reached

        #     print(".", end =" ")
        # print("")
        result_grid.append(result_list)

    print("")
    print("")
    debug = True
    if debug:
        print("I'm trying to make a graph!")
        grid = []
        for y in range(0, BEACON_max_xy+1):
            row = []
            for x in range(0, BEACON_max_xy+1):
                if x in result_grid[y]:
                    row.append('#')
                else:
                    row.append('.')
            grid.append(row)

        for sensor in sensor_list:
            sPy = sensor.pos.y + abs(min_y)
            sPx = sensor.pos.x + abs(min_x)
            bPy = sensor.beacon.pos.y + abs(min_y)
            bPx = sensor.beacon.pos.x + abs(min_x)

            if sPy <= BEACON_max_xy and sPx <= BEACON_max_xy:
                grid[sPy][sPx] = str(sensor.index)
            if bPy <= BEACON_max_xy and bPx <= BEACON_max_xy:
                grid[bPy][bPx] = "B"


        print_grid(grid)




    #Check is beacon is in way and over write x value

    # beacons_in_way = []
    # for sensor in sensor_list:
    #     # distance to sensor
    #     bPx = sensor.beacon.pos.x
    #     bPy = sensor.beacon.pos.y
    #     if bPy == row_num:
    #         beacons_in_way.append(sensor.beacon)

    # for beacon in beacons_in_way:
    #     bX = beacon.pos.x
    #     debug = bX in result_list
    #     while bX in result_list:
    #         result_list.remove(bX)











    return -1

