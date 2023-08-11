
#include<stdio.h>
#include<math.h>
#include<cs50.h>
int main()
{
    long long card_num, a, b, c, d, e, n, m, o, p, q = 0, r = 0, s, t, u, f = 0, v = 1, w, x, y, z, k, l, o_sum = 0, sum = 0;
    /*variables*/
    card_num = get_long("enter:");
    a = 1000000000000000;
    b = 100000000000000;
    c = 1000000000000;
    d = 10000000000000;
    n = card_num;
    /*loop one*/
    while (n > 9)
    {
        m = n % 100;
        o = n % 10;
        p = m - o;
        q = p / 10;
        r = 2 * q;
        if (r > 9)
        {
            k = r % 10;
            l = r / 10;
            r = k + l;
        }
        sum += r;
        n = n / 100;
        v += 2;
        f += 2;
        
    }
    
    n = card_num;
    /*loop two*/    
    while (n > 0)
    {
        t = n % 10;
        o_sum += t;
        n = n / 100;
    }
    u = sum + o_sum;
    n = card_num;
    /*condition starts from here*/
    if (u % 10 == 0)
    {
        if (f == 16)
        {
            w = n / a;
            x = n / b;
            if (x > 50 && x < 56)
            {
                printf("MASTERCARD\n");
            }
            else if (w == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");

            }
        }
        else if (f == 13)
        {
            y = n / c;
            if (y == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");

            }
        }
        else if (v == 15)
        {
            z = n / d;
            if (z == 37 || z == 34)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}