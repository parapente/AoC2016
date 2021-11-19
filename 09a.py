#!/usr/bin/python3

class State:
    copy = 1
    marker_start = 2
    decompress = 3
    marker_what = 4
    marker_how_many = 5
    marker_end = 6

class Marker:
    times = 0
    chars = 0

with open('09.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()

decompressed_buffer = []
current_state = State.copy
temp_buffer = []
current_marker = Marker()

for line in instruction_lines:
    for character in line:
        if current_state == State.copy:
            if character == '(':
                current_marker = Marker()
                current_state = State.marker_start
            elif character.isprintable():
                decompressed_buffer.append(character)
        elif current_state == State.marker_start:
            temp_buffer += character
            current_state = State.marker_what
        elif current_state == State.marker_what:
            if character == 'x':
                current_marker.chars = int("".join(temp_buffer))
                temp_buffer = []
                current_state = State.marker_how_many
            else:
                temp_buffer.append(character)
        elif current_state == State.marker_how_many:
            if character == ')':
                current_marker.times = int("".join(temp_buffer))
                temp_buffer = []
                current_state = State.marker_end
            else:
                temp_buffer.append(character)
        elif current_state == State.marker_end:
            temp_buffer.append(character)
            current_marker.chars -= 1
            if current_marker.chars == 0:
                for _ in range(current_marker.times):
                    decompressed_buffer.extend(temp_buffer)
                temp_buffer = []
                current_state = State.copy

print(len(decompressed_buffer))