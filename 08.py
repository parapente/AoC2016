#!/usr/bin/python3

import re

def parse_command(line: str) -> tuple[callable, list[int]]:
    match = re.match(r'rect (\d+)x(\d+)', line)
    if match:
        return (rect, [int(match.group(1)), int(match.group(2))])
    match = re.match(r'rotate row y=(\d+) by (\d+)', line)
    if match:
        return (rotate_row, [int(match.group(1)), int(match.group(2))])
    match = re.match(r'rotate column x=(\d+) by (\d+)', line)
    if match:
        return (rotate_column, [int(match.group(1)), int(match.group(2))])
    

def rect(args: list[int], screen: list[list[str]]) -> None:
    width, height = args
    for x in range(width):
        for y in range(height):
            screen[y][x] = '#'

def rotate_row(args: list[int], screen: list[list[str]]) -> None:
    row, offset = args
    for _ in range(offset):
        item = screen[row].pop()
        screen[row].insert(0, item)

def rotate_column(args: list[int], screen: list[list[str]]) -> None:
    column, offset = args
    for _ in range(offset):
        prev = screen[0][column]
        for y in range(len(screen)):
            keep = screen[(y+1)%len(screen)][column]
            screen[(y+1)%len(screen)][column] = prev
            prev = keep

def print_screen(screen: list[list[str]]) -> None:
    for row in screen:
        for pixel in row:
            print(pixel, end='')
        print('')

with open('08.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()

screen = [['.']*50 for _ in range(6)]

for line in instruction_lines:
    print("Parsing line '", line, "'", sep='')
    cmd, args = parse_command(line)
    cmd(args, screen)
    print_screen(screen)

total = 0
for line in screen:
    for pixel in line:
        if pixel == '#':
            total += 1
print('Pixels lit:', total)