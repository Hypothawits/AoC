import math

class file():
    def __init__(self, name, size):
        self.name = name
        self.size = size


class folder():
    def __init__(self, name, parent_folder):
        self.name = name
        self.parent_folder = parent_folder
        self.size = 0
        self.file_list = []
        self.folder_list = []


def open_file(file_path):
    """Open the file and return the split lines"""
    f = open( file_path, "r")
    lines = f.readlines()
    return lines

def open_folder_from_list(folder_list, search_name, root_folder):
    if search_name == "/":
        return root_folder

    for folder in folder_list:
        if folder.name == search_name:
            return folder
    else:
        return -1

def open_folder_from_tree(root_folder, search_name):
    if search_name == "/":
        return root_folder

    for folder in root_folder.folder_list:
        if folder.name == search_name:
            return folder
        else:
            found_folder = open_folder_from_tree(folder, search_name)
            if found_folder != -1:
                return found_folder

    return -1

def calculate_size (current_folder):
    for folder in current_folder.folder_list:
        calculate_size (folder)

    total_file_size = 0
    for file in current_folder.file_list:
        total_file_size += file.size

    total_folder_size = 0
    for folder in current_folder.folder_list:
        total_folder_size += folder.size

    current_folder.size = total_file_size + total_folder_size

def find_smallish_dir (current_folder, threshhold, answer_list, answer_size):
    for folder in current_folder.folder_list:
        find_smallish_dir(folder, threshhold, answer_list, answer_size)
        if folder.size <= threshhold: # at most threshhold
            answer_list.append(folder.name)
            answer_size.append(folder.size)

def find_space_dir (current_folder, threshhold, answer_list, answer_size):
    for folder in current_folder.folder_list:
        find_space_dir(folder, threshhold, answer_list, answer_size)
        if folder.size >= threshhold: # at most threshhold
            answer_list.append(folder.name)
            answer_size.append(folder.size)

def parse_line(input_lines, input_index, current_folder, root_folder):

    if input_index == len(input_lines):
        return

    current_line = input_lines[input_index]

    if current_line[0] == "$":
        if current_line[2] == "c":      # cd
            folder_name = current_line.split(" ")[2]
            # Move to folder

            # Get folder obj from folder tree
            if folder_name == "..": # gp up a level
                parse_line(input_lines, input_index+1, current_folder.parent_folder, root_folder)
            else:
                next_folder = open_folder_from_list(current_folder.folder_list, folder_name, root_folder)
                assert next_folder != -1
                # Parse line at another folder level
                parse_line(input_lines, input_index+1, next_folder, root_folder)

        elif current_line[2] == "l": # ls
            # Show the contents of directory
            # aka, do nothing, next line
            parse_line(input_lines, input_index+1, current_folder, root_folder)
        else:
            print("[ERROR]")
    elif current_line[0] == "d": # dir
        # Folder contains directory
        folder_name = current_line.split(" ")[1]
        new_folder = folder(folder_name, current_folder)
        # add new folder to list of current dir
        current_folder.folder_list.append(new_folder)
        parse_line(input_lines, input_index+1, current_folder, root_folder)
    elif current_line[0] == "": # dir
        # End of File
        return
    else: # file
        file_size, file_name = current_line.split(" ")
        # add file to file list of current dir
        new_file = file(file_name, int(file_size))
        current_folder.file_list.append(new_file)
        parse_line(input_lines, input_index+1, current_folder, root_folder)

    return



def part_one(file_path):
    """ Day n part one solution """

    lines = open_file(file_path)

    root_folder = folder("/", "/")

    parse_line(lines, 0, root_folder, root_folder)

    calculate_size (root_folder)

    answer_list = []
    answer_size = []
    find_smallish_dir (root_folder, 100000, answer_list, answer_size)

    result = sum(answer_size)
    return result

def part_two(file_path):
    """ Day n part two solution """

    lines = open_file(file_path)

    total_disk_space = 70000000
    space_needed     = 30000000

    root_folder = folder("/", "/")
    parse_line(lines, 0, root_folder, root_folder)

    calculate_size (root_folder)

    print("root size:     " + str(root_folder.size))

    free_space = total_disk_space - root_folder.size
    total_needed_delete = space_needed - free_space


    print("Free Space:    " + str(free_space))
    print("delete needed: " + str(total_needed_delete))

    answer_list = []
    answer_size = []
    find_space_dir (root_folder, total_needed_delete, answer_list, answer_size) # we ignore deleting the root drive lol

    result = min(answer_size)

    return result
