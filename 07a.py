#!/usr/bin/python3

import functools

def is_abba(ip_part: str) -> bool:
    i = 0
    result = False
    while i < (len(ip_part) - 3):
        if ip_part[i] == ip_part[i+3] and ip_part[i+1] == ip_part[i+2] and \
           ip_part[i] != ip_part[i+1]:
           result = True
        i += 1
    return result

with open('07.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()

total = 0
for line in instruction_lines:
    i = 0
    results = []
    results_brackets = []
    for part in line.replace(']', '[').split('['):
        if i % 2 == 0:
            results.append(is_abba(part))
        else:
            results_brackets.append(is_abba(part))
        i += 1

    valid = functools.reduce(lambda x, y: x or y, results) and not \
            functools.reduce(lambda x, y: x or y, results_brackets)
    if valid:
        total += 1

print(total)