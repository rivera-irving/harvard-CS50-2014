#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ask in command argument style
int main (int argc, string argv[])
{
    //validate input user
    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Retry you failed to input a valid cipher <key>\n");
        return 1;
    }   

     //stored key and get the plaintext
     int key = atoi(argv[1]);
     //printf("Please input your plain text:"\n");
     string plaintext = GetString ();
     
     //encrypt the plaintext to cyphertext
     for (int i = 0, n = strlen(plaintext); i < n; i++)
     {   
        //test and change [i] of the plaintext only to alpha char
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {   
                plaintext[i] = ((plaintext[i] - 'A' + key) %26) + 'A';
            } 
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            {   
                plaintext[i] = ((plaintext[i] - 'a' + key) %26) + 'a';                
            } 
        //leaves unchanged every other possible char   
     }
    // print the cyphertext
    printf("%s\n", plaintext);
    //the requested but unnecessary return 0
    return 0;
}
