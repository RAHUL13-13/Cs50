#include<stdio.h>
#include<cs50.h>
void c_ode_(int k);
int main()
{ 
    int m;
    m = get_int("enter height:");
    if (m < 9 &&  m > 0)
    {
        c_ode_(m);
    }
    else
    {
        main();

    }
}
void c_ode_(int k)
{
    int n, j, i ;
    for (i = 1; i <= k; i++)
    {
        for (n = (k - i); n > 0; n--)
        {
            printf(" ");
        }
        for (j = 1; j <= i; j ++)
        {
            printf("#");
        }
        printf("  ");
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
        
    }
}
