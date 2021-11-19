#!/usr/bin/python3

import re

with open('03.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
triangles = 0
counter = 0;
candidates = [[] for _ in range(3)]
for line in instruction_lines:
    counter += 1
    sides = re.sub(r'\s+', ' ', line).strip().split(' ')
    for key, value in enumerate(sides):
        candidates[key].append(value)

    if counter % 3 == 0:
        for candidate in candidates:
            is_triangle = True
            for side in candidate:
                other_sides = candidate.copy()
                other_sides.remove(side)
                side_sum = sum([int(x) for x in other_sides])
                if side_sum <= int(side):
                    is_triangle = False
                    break
            if is_triangle:
                triangles += 1
        for i, _ in enumerate(candidates):
            candidates[i] = []
print(triangles)
