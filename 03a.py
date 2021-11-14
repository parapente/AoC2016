#!/usr/bin/python3

import re

with open('03.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
triangles = 0
for line in instruction_lines:
    sides = re.sub(r'\s+', ' ', line).strip().split(' ')
    is_triangle = True
    for side in sides:
        other_sides = sides.copy()
        other_sides.remove(side)
        side_sum = sum([int(x) for x in other_sides])
        if side_sum <= int(side):
            is_triangle = False
            break
    if is_triangle:
        triangles += 1
print(triangles)
