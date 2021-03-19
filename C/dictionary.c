// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// defines hashtable size (also from the reference for the hash function)
#define HASHTABLE_SIZE 1985

//Sets up pointer for linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

//Hash prototype
unsigned long hash(char *str);

//Set pointer to hash table
node *hashtable[HASHTABLE_SIZE];

//Counter for the words in size function
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // allocates memory for a lowercase version of the word (creates array to avoid mallocing)
    char word2[strlen(word) + 1];
    // adds end of string character to new string
    word2[strlen(word)] = '\0';
    // iterates over every letter of the word, and passes the lowered version into the new word
    for (int i =0; i < strlen(word); i++)
    {
        word2[i] = tolower(word[i]);
    }
    // gets an integer that is the hash bucket of the word
    int hv = hash(word2);
    // creates a node that is equal originally to the hashtable bucket
    node *cursor = hashtable[hv];
    // while the word has not been found in the linked list and the cursor has not reached the end, keep comparing
    while (cursor != NULL)
    {
        // for every node, compares the nodes word to the input word; if they match, the function returns true
        if (strcmp(cursor->word, word2) == 0)
        {
            return true;
        }
        // else, we move to the next node
        cursor=cursor->next;
    }
    // if no node was found, we return false
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char dword[LENGTH+1];
    // opens the file to read
    FILE *fp = fopen(dictionary, "r");
    // if the file is null, returns false
    if (fp == NULL)
    {
        return false;
    }
    // runs through the words in the file while a end of file has not been hit
    while(fscanf(fp, "%s\n", dword) != EOF)
    {
        // finds the bucket for the current word
        int bucket = hash(dword);
        // allocates memory for the new node
        node *new = malloc(sizeof(node));
        // if the node is null, then we return false
        if (new == NULL)
        {
            return false;
        }
        // if the linked list here has not begun yet, we store the new word in the hashtable bucket and set the buckets next to NULL
        if (hashtable[bucket] == NULL)
        {
            hashtable[bucket] = new;
            new->next=NULL;
        }
        // else we create a new node at the beginning of the linked list that points to the first element of the linked list and add the word to that new node
        else
        {
            new->next=hashtable[bucket];
            hashtable[bucket]=new;
        }
        // we copy the dictionary word into the new node
        strcpy(new->word, dword);
        // add one to the word count for size
        word_count++;
    }
    // close the file and return true
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // return the word count
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate over every bucket of the hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // create a cursor equal to the current bucket
        node* cursor = hashtable[i];
        // iterate over every node of the linked list, erasing them one by one
        while (cursor != NULL)
        {
            node* tmp = cursor;
            cursor=cursor->next;
            free(tmp);
        }
    }
    return true;
}


// Hash table that I got from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASHTABLE_SIZE;
}
