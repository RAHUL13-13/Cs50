#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])     //main function
{   
    {
        if (argc != 2)         // validation
        {
            return 1;
            
        }
        
    }
    string a = argv[1];
    int lenghtc = strlen(a);
    int i, j;
    if (argc == 2)
    {
        for (int y = 0 ; y <= lenghtc; y++)
        {
            for (int g = 0; g <= lenghtc; g++)
            {
                if (y != g)
                {
                    if (a[y] == a[g])
                    {
                        return 1;
                    }
                    else if (isdigit(a[y]) != 0)
                    {
                        return 1;
                    }
                }
            }
        }
        
        if (lenghtc == 0)
        {
            printf("Usage: ./substitution KEY\n");
            return 1;
        }
        if (lenghtc < 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        char match_string1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int match_lenght1 = strlen(match_string1);
        char match_string2[] = "abcdefghijklmnopqrstuvwxyz";
        int match_lenght2 = strlen(match_string2);
        
        string enter_string = get_string("Plaintext:  ");
        int lenght = strlen(enter_string);
        printf("ciphertext: ");
        for (i = 0; i <= lenght; i++)
        {   
            for (j = 0; j <= 25 ; j++)
            {
                if (enter_string[i] == match_string1[j])
                {
                    printf("%c", toupper(a[j]));
                    break;
                }
                
                else if (enter_string[i] == match_string2[j])
                {
                    printf("%c", tolower(a[j]));
                    break;
                }
            }
            if ((enter_string[i] != match_string2[j]) && (enter_string[i] != match_string1[j]))  
            {
                printf("%c", enter_string[i]);
            }
        }       
        printf("\n");
    }
}
    
