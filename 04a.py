#!/usr/bin/python3

import re

def letter_frequency(name: str) -> list[tuple]:
    letters = dict()
    for letter in name:
        letters[letter] = (letters[letter] if letter in letters else 0) + 1
    result = []
    for key in letters.keys():
        result.append((key, letters[key]))
    return result

def calc_checksum(name: str) -> str:
    letters = letter_frequency(name.replace('-', ''))
    letters.sort(key=lambda x: (-x[1], x[0]))
    checksum = ''
    for letter in letters:
        checksum += letter[0]
    return checksum[:5]

with open('04.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
total = 0
for line in instruction_lines:
    m = re.match(r'(.+)-(\d+)\[(.{5})\]', line)
    if m:
        room_name = m.group(1)
        sector_id = m.group(2)
        checksum = m.group(3)
        if calc_checksum(room_name) == checksum:
            total += int(sector_id)
    else:
        print('Line not matched! (', line, ')')
print(total)
