/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef struct trie
{
    bool word;
    //27 hash index 26 letter + apostrophe (but it leaks memory, how do I free the childrens???)
    struct trie* children[27]; 
} 
trie;

trie* root;

// wordcount
int wordcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    int a = (int)'a';
    int z = (int)'z';

    trie* node = root;

	int i = 0;
	while(word[i] != '\0')
    {
        char s = word[i];
        
        // check apostrophes
        if (word[i] == '\'')
        {
            s = z + 1;
        }

        int index = tolower(s) - a; 	
       
        if (node->children[index] != NULL)
        {
            node = node->children[index];
            i++;
	    }
	      
        else
        {
            return false;
         } 
    }
    
    if (node->word == true)
    {
        return true;
    }
    
	else
	{
    return false;
	}
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    int a = (int)'a';
    int z = (int)'z';
    
    FILE *fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        return false;
    }

    root = malloc(sizeof(trie));

    trie* node = NULL;
    int letter = 0;
    while(fgetc(fp) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        node = root;

        for (letter = fgetc(fp); letter != '\n'; 
                letter = fgetc(fp))
        {    
            // take care of apostrophes
            if (letter == '\'')
            {
                letter = z + 1;
            }

            if (node->children[letter - a] == NULL)
            {
                node->children[letter - a] = malloc(sizeof(trie));
                node = node->children[letter - a];
	        }
	        
	        else 
            {
                node = node->children[letter - a];
	        }
	    }

        node->word = true;
        wordcount++;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordcount;
}

/**
 * Unloads dictionary from memory
*/
bool unload(void)
{
    // TODO
	//still leaks memory donot know how to free the childrens of the childrens
    for(int j = 0; j < 27; j++)
    {
		trie* node = root;
		
        if (node->children[j] != NULL)
        {
            free(node->children[j]);
            //free(root);
            //free(trie); 
            //free(node);
        }      
	}
    return true;
}
