// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Variable for number of words loaded
unsigned int totalwords = 0;

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Defines all self-created function prototypes
int hash(char);
node * storeletter(int, node *, bool);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    int hashval = 0;
    node *current = root;
    bool lastword = false;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        current = root;
        lastword = false;

        // hash each char and store it into trie
        for(int i = 0, wordlen = strlen(word); i < wordlen; i++)
        {
            if(i == wordlen - 1)
            {
                lastword = true;
            }
            hashval = hash(word[i]);
            current = storeletter(hashval, current, lastword);
        }

        totalwords++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Check if at least 1 of the first branch is filled
    node *tmp = root;
    for(int i = 0; i < N; i++)
    {
        if(tmp->children[i])
        {
            return totalwords;
        }
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initialize check system
    node *current = root;
    unsigned int wordlen = strlen(word);
    int hashval = 0;

    // Check whether each char has an allocation, and check bool of last word
    for(int i = 0; i < wordlen; i++)
    {
        hashval = hash(word[i]);
        if(!current->children[hashval])
        {
            return false;
        }
        current = current->children[hashval];

        // Check if last char constitutes a word
        if(i == wordlen - 1)
        {
            return current->is_word;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *current = root;
    bool root_exists = true;

    // Scan branch; if got children, go to children, else free branch
    while(root_exists)
    {
        current = root;
        node *previous = root;
        int countchild = 0, val = 0;
        bool branch_exists = true;
        while(branch_exists)
        {
            if(current->children[countchild])
            {
                previous = current;
                val = countchild;
                current = current->children[val];
                countchild = 0;
            }
            else
            {
                countchild++;
            }

            if(countchild >= N)
            {
                free(current);
                if(current == root)
                {
                    root_exists = false;
                    break;
                }
                else
                {
                    previous->children[val] = NULL;
                    countchild = 0;
                    branch_exists = false;
                }
            }
        }
    }
    return true;
}

// Define hash function
int hash(char letter)
{
    int hashed;
    if(isalpha(letter))
    {
        hashed = tolower(letter) - 'a';
    }
    else if(letter == '\'')
    {
        hashed = 26;
    }
    else
    {
        hashed = 27;
    }
    return hashed;
}

// Stores a letter into branch, creating one if it doesnt exist
node * storeletter(int hashval, node *tmp, bool lastword)
{

    // Set is_word to true if last word, create new branch if not yet created, and move down
    if(!tmp->children[hashval])
    {
        tmp->children[hashval] = malloc(sizeof(node));
        node *clearchild = tmp->children[hashval];
        clearchild->is_word = false;
        for(int i = 0; i < N; i++)
        {
            clearchild->children[i] = NULL;
        }
    }
    tmp = tmp->children[hashval];
    if(lastword)
    {
        tmp->is_word = true;
    }
    return tmp;
}