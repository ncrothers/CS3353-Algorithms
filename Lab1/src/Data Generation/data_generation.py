# This script generates all of the files that are needed for CS3353 Lab1

import random
import csv
from pathlib import Path

folder = Path('Data Generation/files/')

file_amts = [10, 1000, 10000, 100000]

cur_vals = []

# Writes the cur_vals array to a filename passed into this function
def write_to_file(filename):
    with open(folder / filename, mode='w', newline='') as cur_file:
        file_writer = csv.writer(cur_file, delimiter=',')

        for val in cur_vals:
            file_writer.writerow([val])
    cur_vals.clear()


# Randomly shuffles values in cur_vals array
def shuffle_array(num):
    max = num
    while max > 0:
        swap_val = random.randint(0, max)
        temp = cur_vals[max - 1]
        cur_vals[max - 1] = cur_vals[swap_val]
        cur_vals[swap_val] = temp
        max -= 1


# Produces an array with num values in descending order
def reverse_sorted(num):
    i = num
    while i > 0:
        cur_vals.append(i)
        i -= 1


# Produces an array with random values
def random_vals(num):
    for i in range(0, num):
        cur_vals.append(i)
    
    shuffle_array(num)


# Produces an array with 20% unique values
def semi_unique(num):
    for count in range(0, 5):
        for i in range(0, int(num/5)):
            cur_vals.append(i)

    shuffle_array(num)


# Produces an array with 30% of values in random order
def semi_random(num):
    vals_to_randomize = []
    for i in range(0, num):
        vals_to_randomize.append(i)
        cur_vals.append(i)
    
    max = num
    while max > 0:
        swap_val = random.randint(0, max)
        temp = vals_to_randomize[max - 1]
        vals_to_randomize[max - 1] = vals_to_randomize[swap_val]
        vals_to_randomize[swap_val] = temp
        max -= 1
    
    for i in range(0, int(0.15 * num)):
        temp = cur_vals[vals_to_randomize[i]]
        cur_vals[vals_to_randomize[i]] = cur_vals[num - vals_to_randomize[i] - 1]
        cur_vals[num - vals_to_randomize[i] - 1] = temp


# These for loops create the data files of each type and amount of values
for i in range(0, 4):
    reverse_sorted(file_amts[i])

    filename = 'reversed-' + str(file_amts[i]) + '.csv'

    write_to_file(filename)

for i in range(0, 4):
    random_vals(file_amts[i])

    filename = 'random-' + str(file_amts[i]) + '.csv'

    write_to_file(filename)

for i in range(0, 4):
    semi_unique(file_amts[i])

    filename = 'semi-unique-' + str(file_amts[i]) + '.csv'

    write_to_file(filename)

for i in range(0, 4):
    semi_random(file_amts[i])

    filename = 'semi-random-' + str(file_amts[i]) + '.csv'

    write_to_file(filename)