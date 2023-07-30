import sys
import csv
import numpy
import pandas as pd
from csv import reader


def my_boy_splits(n):
    return [char for char in n]


# opening DNA database to be compared from
database_dna1 = open(sys.argv[1], "r")

reade_csv = csv.reader(database_dna1)
data = list(reade_csv)

database_dna2 = open(sys.argv[1], "r")

# taking in dna majors
dna_major = database_dna2.readline().split(',')

# calculating length to converted into an array
line = database_dna2.readline().split(',')
length_csv = len(line)
print(line)
# made an array from database provided
array_data = numpy.loadtxt(sys.argv[1], delimiter=",", skiprows=1, usecols=range(1, length_csv))
array_data_int = array_data.astype(int)

# opening DNA to be tested
dna_sample = open(sys.argv[2], "r")

# reading and spliting input DNA so that i can compare
dna = dna_sample.readline()
dna_length = len(dna)

array = [0,0,0,0,0,0,0,0]

for i in range(1, length_csv):  # length_csv is dna sequences to bed counter
    sample = dna_major[i]  # checking for first database dna ....dna major is dna in first database colum
    sample = sample.replace('\n', '')  # removing \n if read by readline in csv....sample

    protien_length = len(sample)

    l = 0
    max = 0
    longest_chain = 0

    for j in range(0, dna_length + 1):
        if j == l:
            if dna[j:j + protien_length] == sample:
                max += 1
                l = j + protien_length

                if longest_chain <= max:
                    longest_chain = max
            if dna[j:j + protien_length] != sample:
                l = l + 1
                max = 0
    array[i-1] = longest_chain

k = 0
i = 0

while k <= len(array_data_int)-1:
    if len(array_data_int) <= 3:
        if array_data_int[k][i] == array[i] and array_data_int[k][i+1] == array[i+1] and array_data_int[k][i+2] == array[i+2]:
            print(data[k+1][0])
            exit(0)
        elif k == len(array_data_int) - 1:
            print("No match")
            exit(0)
    if len(array_data_int) >= 3:
        if array_data_int[k][i] == array[i] and array_data_int[k][i+1] == array[i+1] and array_data_int[k][i+2] == array[i+2] and array_data_int[k][7] == array[7]:
            print(data[k+1][0])
            exit(0)
        elif k == len(array_data_int) - 1:
            print("No match")
            exit(0)

    k += 1