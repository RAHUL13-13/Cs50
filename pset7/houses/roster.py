# TODO
import cs50
import sys
from sys import argv
import sqlite3
import numpy

if len(argv) != 2:
    print("nop")
    exit(99)

db = cs50.SQL("sqlite:///students.db")


yoyo = numpy.array((db.execute(f"SELECT first,middle,last,birth FROM students WHERE house = '{argv[1]}' order BY last, first;")))

for j in range(len(yoyo)):
    print(yoyo[j]["first"], end=" ")
    if yoyo[j]["middle"] == None:
        del yoyo[j]["middle"]
    else:
        print(yoyo[j]["middle"], end=" ")

    print(yoyo[j]["last"], end=" ")

    print(f",born { yoyo[j]['birth']}")