#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>
#include <stdlib.h>

#define MAX 9

void print_winner(void);
int candidate_count;
bool vote(string name);

typedef struct
{
    string name;
    int votes;
} candidate;
candidate candidates[MAX];

int candidate_count;


bool vote(string name);
void print_winner(void);

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}



int main(int argc, string argv[])
{
   
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_counts = get_int("Number of voters: ");


    for (int i = 0; i < voter_counts; i++)
    {
        string name = get_string("Vote: ");

       
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Update vote totals 

void print_winner(void)
{
    
    int HIGHEST = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > HIGHEST)
        {
            HIGHEST = candidates[i].votes;
        }
    }
   
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == HIGHEST)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
