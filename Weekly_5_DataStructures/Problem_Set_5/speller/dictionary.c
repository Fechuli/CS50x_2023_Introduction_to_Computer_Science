// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

unsigned int counter = 0;

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 500;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int indice = hash(word);
    node *pippo = table[indice];

    while (pippo != 0)
    {
        if (strcasecmp(word, pippo->word) == 0)
        {
            return true;
        }
        pippo = pippo->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int f = 0;
    unsigned int pilen = strlen(word);
    for (int i = 0; i < pilen; i++)
    {
        f += tolower(word[i]);
    }
    return f % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *act_dictionary = fopen(dictionary, "r");
    if (act_dictionary == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(act_dictionary, "%s", word) != EOF)
    {
        node *pap = malloc(sizeof(node));

        if (pap == NULL)
        {
            return false;
        }

        strcpy(pap->word, word);
        pap->next = NULL;
        int indice2 = hash(word);
        pap->next = table[indice2];
        table[indice2] = pap;
        counter++;
    }
    fclose(act_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *dmmy = table[i];
        while (dmmy != NULL)
        {
            node *dmmy2 = dmmy;
            dmmy = dmmy->next;
            free(dmmy2);
        }
    }
    return true;
}
