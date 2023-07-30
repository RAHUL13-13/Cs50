from cs50 import get_int
from cs50 import get_string


def main():
    v = 1
    q = 0 
    r = 0 
    f = 0
    o_sum = 0
    sum = 0
    card_num = get_int("enter:")
    a = 1000000000000000
    b = 100000000000000
    c = 1000000000000
    d = 10000000000000
    n = card_num
    while (n > 9):
        m = n % 100
        o = n % 10
        p = m - o
        q = p // 10
        r = 2 * q
        if (r > 9):
            k = r % 10
            l = r // 10
            r = k + l
        sum += r
        n = n // 100
        v += 2
        f += 2
    
    n = card_num
    
    while (n > 0):
        t = n % 10
        o_sum += t
        n = n // 100
    u = sum + o_sum
    n = card_num

    # condition starts from here

    we = u % 10
    if we == 0:
        if f == 16:
            w = n // a
            x = n // b
            if (x > 50 and x < 56):
                print("MASTERCARD\n")
            elif w == 4:
                print("VISA\n")
            else:
                print("INVALID\n")
        elif f == 13:
            y = n // c
            if y == 4:
                print("VISA\n")
            else:
                print("INVALID\n")
        elif v == 15:
            z = n // d
            if z == 37 or z == 34:
                print("AMEX\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")


main()