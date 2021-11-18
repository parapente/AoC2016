#!/usr/bin/python3

import hashlib
import random

with open('05.dat') as f:
    data = f.read()
password = list('________')
i = 0
chars_found = 0
while(chars_found < 8):
    test_string = data + str(i)
    result = hashlib.md5(test_string.encode('utf-8'))
    if (result.hexdigest().startswith("00000")):
        position = int(result.hexdigest()[5], base=16)
        if position < 8 and password[position] == '_':
            password[position] = result.hexdigest()[6]
            chars_found += 1
    i += 1
    fancy_password = password
    for char in fancy_password:
        if char == '_':
            print(hex(random.randint(0, 16))[2], end='')
        else:
            print(char, end='')
    print('', end='\r')

print('')
