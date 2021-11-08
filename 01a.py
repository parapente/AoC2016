#!/usr/bin/python3

headings = [[0, 1], [1, 0], [0, -1], [-1, 0]]

def add_matrix(m1, m2):
    return [m1[0] + m2[0], m1[1] + m2[1]]
    
def mul_matrix(m1, num):
    return [m1[0] * num, m1[1] * num]

with open('01.dat') as f:
    data = f.read()
instructions = data.split(', ')
coord = [0, 0]
heading = 0
for instruction in instructions:
    command = instruction[0]
    steps = int(instruction[1:])
    if command == 'R':
        heading += 1
        if heading >= len(headings):
            heading = 0
    else:
        heading -= 1
        if heading < 0:
            heading = len(headings) - 1
    coord = add_matrix(coord, mul_matrix(headings[heading], steps))
print(coord[0]+coord[1])