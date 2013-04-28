#!/usr/bin/python
file=open('inp/output', 'r')
string = ''
for line in file:
    line_list=line.split()
    if line_list==[]: continue
    string += line_list[5] + ', '
print string