// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#define FALSE  0
#define TRUE 1
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int dict_size;
int word_length;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// number of buckets in hash table
const unsigned int hash_size = 186019;

// Hash table djb2, from - http://www.cse.yorku.ca/~oz/hash.html
node *table[hash_size];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int b = strlen(word);
    char words_upper[b];
    
    for (int j = 0; j <= b; j++)
    {
        char tmp = toupper(word[j]);
        words_upper[j] = tmp;
    }
    
    //getting hash value for word read from sample document to be checked.....
    int words_index = hash(words_upper);
    
    if (table[words_index] == NULL)
    {
        return false;
    }
    
    node *cursor; 
    
    for (cursor = table[words_index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % hash_size;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    int hash_index_number;
    char word[LENGTH + 1];
    FILE *dict = fopen(dictionary, "r");
     
    while (fscanf(dict, "%s", word) != EOF)
    {
        dict_size++;

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return FALSE;
        }
        
        //converting to uppercase for hash inputing......
        int b = strlen(word);
        for (int j = 0; j <= b; j++)
        {
            word[j] = toupper(word[j]);
        }
        
        strcpy(n->word, word);
        hash_index_number = hash(word);


        //idk what i am doing but it feels this way :(
        n->next = table[hash_index_number];
        table[hash_index_number] = n;
        
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *tmp;
    for (int j = 0; j < hash_size; j++)
    {
        node *cursor = table[j];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
