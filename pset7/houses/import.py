import sys
import csv
import cs50
from sys import argv

# TODO
if len(argv) != 2:
    print("nop")
    exit(99)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as first:
    reader = csv.DictReader(first, delimiter=",")
    for row in reader:
        birth = int(row["birth"])
        house = row["house"]
        splited = row["name"].split(" ")

        if len(splited) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", splited[0], splited[1],
                       splited[2], house, birth)

        if len(splited) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", splited[0], splited[1], house,
                       birth)

        elif len(splited) == 1:
            db.execute("INSERT INTO students (first, house, birth) VALUES(?, ?, ?)", splited[0], house, birth)