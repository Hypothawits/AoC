import math

class board_c (object):
    def __init__(self, k_col, k_row, next):
        self.board = [ [0]*k_col for i in range (k_row)]

        self.next = next

def day4p1(b_test, pwd):
    if(b_test):
        f = open( pwd + "\\input\\test.txt","r")
    else:
        f = open(pwd + "\\input\\input.txt","r")
    
    lines = f.read().splitlines()
    # lines = f.readlines()

    bingo_input = lines[0]
    bingo_input = bingo_input.split(",")
    print(bingo_input[0])

    print("\n")
    
    Number_of_input_lines = len(lines) -1
    board_lines_size = 6 # 5 + 1 spacer
    number_boards = Number_of_input_lines / board_lines_size
    
    # split lines into number strings
    split_lines = []
    for i in range(len(lines)):
        split_lines.append(lines[i].split(" "))

    print("lines: " + str(Number_of_input_lines))
    print("board size: " + str(board_lines_size))
    print("Num boards: " + str(number_boards))

    #for i in range(2,len(lines),1):
    
    k_col = 5
    k_row = 5
    int_lines = [ [0]*k_col for i in range (k_row)]
    board_1 = board_c(k_col, k_row, None)
    board_row = 0
    for i in range(2, 7,1 ): # len(lines),1):
        col = 0
        for x in split_lines[i]:
            if x != '':
                int_lines[board_row][col] = int(x)
                board_1.board[board_row][col] = int(x)
                col = col+1
            else:
                col = col

        board_row = board_row + 1




    
    #board1.R0 = bingo_input[2]
    print(board_1)
    print(board_1.board[0])
    # val = []
    # count_pos_0 = 0
    # for i in range(0, len(lines)-1 ):
    #     x = int(lines[i+1])
    #     y = int(lines[i])
    #     result = x > y
    #     val.append( result )
    #     count_pos_0 = count_pos_0 + result

    #     print( str(x) + " > " + str(y) + " : " + str(result) + " : " + str(count_pos_0))

    # count_pos = 0
    # for i in val:
    #     count_pos = count_pos + i
        
    return bingo_input
   

