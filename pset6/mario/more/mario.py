from cs50 import get_int


def yo():
    num = get_int("Height: ")
    m(num)
    
    
def m(num):
    if (num <= 0):
        yo()
    elif(num > 8):
        yo()
    else:
        for i in range(1, num + 1):
            for j in range(1, num - i + 1):
                print(" ", end="")
            for k in range(1, i + 1):
                print("#", end="")
            print("  ", end="")
            for k in range(1, i + 1):
                print("#", end="")
            print("")
            
            
yo()