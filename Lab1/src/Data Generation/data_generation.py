# This script generates all of the files that are needed for CS3353 Lab1

import csv
from pathlib import Path

folder = Path('files/')

cur_vals = []

def reverseSorted(num):
    i = num
    while i > 0:
        cur_vals.append(i)
        i -= 1

reverseSorted(10)

with open(folder / 'reversed-10.csv', mode='w') as cur_file:
    file_writer = csv.writer(cur_file, delimiter=',')

    for val in cur_vals:
        file_writer.writerow(val)