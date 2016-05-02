sign_num = 0


def add_sign(filepath, aim_dic):
    global sign_num

    fp = open(filepath, "r")
    for line_in in fp:
        aim_dic[line_in.strip()] = sign_num
        sign_num += 1

ROWS, COLUMNS = 127, 67
row, col = 0, 0

signs = {}
add_sign(r"F:\PascalCompiler\terminal.txt", signs)
add_sign(r"F:\PascalCompiler\nonterminal.txt", signs)

grammars = {}
sign_num = 0
add_sign(r"F:\PascalCompiler\grammar_list.txt", grammars)

table_fp = open(r"lalrtable.htm", "r")
column_map = []

row_head = ""
for line in table_fp:
    line = line.strip()
    # print(str(row) + ' ' + str(col))
    if row == 0:
        if col == 0:
            column_map.append(-1)
        else:
            column_map.append(signs[line])
    else:
        if col == 0:
            row_head = line
            if row_head != str(row - 1):
                print("ERROR")
        elif len(line) != 0:
            print_str = row_head + " " + str(column_map[col]) + " "
            if line == "accept":
                print_str += "ACCEPT"
            else:
                if line.startswith("shift "):
                    line = line[6:]
                if line.startswith("reduce "):
                    line = line[7:]
                    print_str += "-" + str(grammars[line])
                else:
                    print_str += str(line)
            print(print_str)
    col += 1
    if col == COLUMNS:
        row, col = row + 1, 0
