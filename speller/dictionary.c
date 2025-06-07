// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 10007;

// Hash table
node *table[N];
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if (word != NULL)
    {
        unsigned int index = hash(word);
        node *cursor = table[index];

        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function: djb2 by Daniel J. Bernstein
    // Source: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    if (word == NULL || *word == '\0')
    {
        return 0; // Return 0 for empty or NULL words
    }

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; // (hash * 33) + c
    }

    return (unsigned int) (hash % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char src[LENGTH + 1];
    // Read each word in the file
    while (fscanf(file, "%s", src) != EOF)
    {
        node *dst = malloc(sizeof(node));
        if (dst == NULL)
        {
            fclose(file);
            unload();
            return false;
        }
        dst->next = NULL;
        // Hash index for each word
        unsigned int index = hash(src);

        // Copy the word into node
        strncpy(dst->word, src, LENGTH);
        dst->word[LENGTH] = '\0'; // Make sure destination is null-terminated

        // Add each word to the hash table
        if (table[index] != NULL)
        {
            dst->next = table[index];
        }
        table[index] = dst;
        count++;
    }

    // Close the dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }
    return true;
}
