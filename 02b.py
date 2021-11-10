#!/usr/bin/python3

keypad = [[-1,  -1,   1,  -1, -1],
          [-1,   2,   3,   4, -1],
          [ 5,   6,   7,   8,  9],
          [-1, 'A', 'B', 'C', -1],
          [-1,  -1, 'D',  -1, -1]]

with open('02.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
coord = [0, 2]
for line in instruction_lines:
    for instruction in line:
        match instruction:
            case 'R':
                if coord[0] < (len(keypad[coord[1]]) - 1) and keypad[coord[1]][coord[0] + 1] != -1:
                    coord[0] += 1
            case 'L':
                if coord[0] > 0 and keypad[coord[1]][coord[0] - 1] != -1:
                    coord[0] -= 1
            case 'U':
                if coord[1] > 0 and keypad[coord[1] - 1][coord[0]] != -1:
                    coord[1] -= 1
            case 'D':
                if coord[1] < (len(keypad) - 1) and keypad[coord[1] + 1][coord[0]] != -1:
                    coord[1] += 1
    print(keypad[coord[1]][coord[0]], end='')
