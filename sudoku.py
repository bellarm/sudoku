#!/usr/bin/env python3.5
import sys

""" SUDOKU
    will need:
        - THE GRID -> 9x9 array
        - Solve function

class Sudoku(object):
    def __init__(self):
        self.box = None
    def solve(self):
        pass
"""
LINE = "+-------+-------+-------+"

def print_puzzle():
    print(LINE)
    for i in range(0, 9):
        for j in range(0, 9):
            if (j) % 3 == 0:
                sys.stdout.write('| ')
            if given[i][j]:
                sys.stdout.write("\x1b[1;33m")
            sys.stdout.write("%c \x1b[0m" % (test[i][j]))
        print('|')
        if i % 3 == 2:
            print(LINE)

def solve_puzzle(row, col):
    if row > 8:
        return True
    while given[row][col]:
        if col < 8:
            next_row = row;
            next_col = col + 1;
        else:
            next_row = row + 1;
            next_col = 0;        
        row = next_row;
        col = next_col;
        if row > 8:
            return True

    if col < 8:
        next_row = row;
        next_col = col + 1;
    else:
        next_row = row + 1;
        next_col = 0;

    a = '1'
    while True:
        if compare_col(a, col) and compare_row(a, row) and compare_reg(a, col, row):
            test[row][col] = a
            if solve_puzzle(next_row, next_col):
                return True
        a = chr(ord(a)+1)
        if a == ':':
            test[row][col] = '0'
            return False
    return True

def compare_col(a, col):
    for i in range(0, 9):
        if test[i][col] == a:
            return False
    return True

def compare_row(a, row):
    for i in range(0, 9):
        if test[row][i] == a:
            return False
    return True

def compare_reg(a, col, row):
    start_row = row//3*3
    start_col = col//3*3
    for i in range(start_row, start_row+3):
        for j in range(start_col, start_col+3):
            if test[i][j] == a:
                return False
    return True

test = []
given = []
for line in sys.stdin:
    nums = list(line.rstrip())
    test.append(nums)
    give = []
    for num in nums:
        if num == '0':
            give.append(0)
        else:
            give.append(1)
    given.append(give)
solve_puzzle(0,0)
print_puzzle()