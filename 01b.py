#!/usr/bin/python3

headings = [[0, 1], [1, 0], [0, -1], [-1, 0]]

def add_matrix(m1, m2):
    return [m1[0] + m2[0], m1[1] + m2[1]]
    
def mul_matrix(m1, num):
    return [m1[0] * num, m1[1] * num]

with open('01.dat') as f:
    data = f.read()
instructions = data.split(', ')
visited_coords = [[0,0]]
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
    newcoord = add_matrix(coord, mul_matrix(headings[heading], steps))
    if (coord[0] == newcoord[0]):
        for i in range(abs(newcoord[1] - coord[1])):
            if i != 0:
                temp_coord = [coord[0], coord[1] + i * headings[heading][1]]
                if (temp_coord in visited_coords):
                    newcoord = temp_coord
                    break
                visited_coords.append(temp_coord)
    if (coord[1] == newcoord[1]):
        for i in range(abs(newcoord[0] - coord[0])):
            if i != 0:
                temp_coord = [coord[0] + i * headings[heading][0], coord[1]]
                if (temp_coord in visited_coords):
                    newcoord = temp_coord
                    break
                visited_coords.append(temp_coord)
    coord = newcoord
    if (coord in visited_coords):
        break
    visited_coords.append(coord)
print(coord[0]+coord[1])