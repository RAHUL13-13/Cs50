#include <stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>
int main()
{   
    int l = 0, rounded;
    float word = 1, characters = 0, sentence = 0, grade;
    string s = get_string("input a string:");
    int len = strlen(s);
    
    while (l < len)
    {
        if ((s[l] >= 'a' && s[l] <= 'z') || (s[l] >= 'A' && s[l] <= 'Z'))
        {
            characters++;
        }
      
        else if (s[l] == ' ')
        {   
            word += 1;
        }
        else if (s[l] == '!' || s[l] == '?' || s[l] == '.')
        {
            sentence += 1;
        }
        l++;
    }

    grade = 0.0588 * (100 * (float) characters / (float) word) - 0.296 * (100 * (float) sentence / (float) word) - 15.8;
    rounded = round(grade);
    if (rounded >= 1 && rounded < 16)
    {
        printf("Grade %d\n", rounded);
    }
    else if (rounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}