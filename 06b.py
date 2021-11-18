#!/usr/bin/python3

with open('06.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
frequency = [dict() for _ in range(len(instruction_lines[0]))]
for line in instruction_lines:
    i = 0
    for character in line:
        if (character in frequency[i].keys()):
            frequency[i][character] = (frequency[i][character]) + 1
        else:
            frequency[i][character] = 1
        i += 1

for column in frequency:
    min = 9999
    character_min = None
    for character in column.keys():
        if column[character] < min:
            min = column[character]
            character_min = character
    print(character_min, end='')
print('')
