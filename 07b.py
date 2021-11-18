#!/usr/bin/python3

def get_aba_bab(ip_part: str) -> list[str]:
    i = 0
    result = []
    while i < (len(ip_part) - 2):
        if ip_part[i] == ip_part[i+2] and ip_part[i] != ip_part[i+1]:
           result.append(ip_part[i:i+3])
        i += 1
    return result

def check_ssl(supernet: list[str], hypernet: list[str]) -> bool:
    result = False
    for aba in supernet:
        bab = aba[1]+aba[0]+aba[1]
        if bab in hypernet:
            result = True
    return result

with open('07.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()

total = 0
for line in instruction_lines:
    i = 0
    supernet = []
    hypernet = []
    for part in line.replace(']', '[').split('['):
        if i % 2 == 0:
            supernet.extend(get_aba_bab(part))
        else:
            hypernet.extend(get_aba_bab(part))
        i += 1

    valid = check_ssl(supernet, hypernet)
    if valid:
        total += 1

print(total)