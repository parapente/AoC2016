#!/usr/bin/python3

import hashlib

with open('05.dat') as f:
    data = f.read()
password = ''
i = 0
while(len(password) < 8):
    test_string = data + str(i)
    result = hashlib.md5(test_string.encode('utf-8'))
    if (result.hexdigest().startswith("00000")):
        password += result.hexdigest()[5]
    i += 1
    print('password:', password, 'i:', i, end='\r')

print('')
print(password)
