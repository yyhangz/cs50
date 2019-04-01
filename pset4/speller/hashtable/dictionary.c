// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];
unsigned int wordcount = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Hashes the read word
        int i = hash(word);

        node *stored = malloc(sizeof(node));
        strcpy(stored->word, word);

        // Checks if first word of that particular alphabet has been filled yet
        if(hashtable[i] == NULL)
        {
            stored->next = NULL;
            hashtable[i] = stored;
        }

        // If filled, add to beginning of hashtable
        else
        {
            stored->next = hashtable[i];
            hashtable[i] = stored;
        }
        wordcount++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int charused = 0;
    // Check if dictionary is loaded
    for(int i = 0; i < N; i++)
    {
        if(hashtable[i])
        {
            charused++;
        }
    }

    // Return 0 if dictionary not loaded
    if(charused == 0)
    {
        return 0;
    }

    // Else return wordcount
    else
    {
        return wordcount;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Convert the word to all lowercase
    char lowerword[strlen(word) + 1];
    strcpy(lowerword, word);
    for(int i = 0, j = strlen(lowerword); i < j; i++)
    {
        lowerword[i] = tolower(lowerword[i]);
    }

    // Run through hashtable while using strcmp to determine if word exists in dictionary
    int startletter = hash(word);
    for(node *tmp = hashtable[startletter]; tmp != NULL; tmp = tmp->next)
    {
        // Return true if words are identical
        if(strcmp(tmp->word, lowerword) == 0)
        {
            return true;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free the linked list in each row of hashtable in alphabetical order
    for(int i = 0; i < N; i++)
    {
        node *current = hashtable[i];
        while(current)
        {
            node *next = current->next;
            free(current);
            current = next;
        }
    }
    return true;
}
