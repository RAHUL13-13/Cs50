from cs50 import get_int
from cs50 import get_string


def main():

    l = 0
    word = 1
    characters = 0
    sentence = 0
    s = get_string("input a string:")
    length = len(s)
    
    while (l < length):
    
        if ((s[l] >= 'a' and s[l] <= 'z') or (s[l] >= 'A' and s[l] <= 'Z')):
            characters += 1
        elif (s[l] == ' '):
            word += 1
        elif (s[l] == '!' or s[l] == '?' or s[l] == '.'):
            sentence += 1
        l += 1

    grade = 0.0588 * (100 * characters / word) - 0.296 * (100 * sentence / word) - 15.8
    rounded = round(grade)
    if (rounded >= 1 and rounded < 16):
        print("Grade ", rounded)
    elif (rounded < 1):
        print("Before Grade 1\n")
    else:
        print("Grade 16+\n")
        
        
main()