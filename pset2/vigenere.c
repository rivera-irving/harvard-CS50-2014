#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ask in command argument style
int main (int argc, char *argv[])
{
    //validate input user for only one keyword
    if (argc != 2)
    {
        printf("Retry you failed to input only 1 valid cipher <keyword>\n");
        return 1;
    }
    //validate input user for only alpha char in the keyword
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {   
         if (!isalpha(argv[1][i]))
         {
         printf("Retry you failed to input only alph char for a valid cipher <keyword>\n");
         return 1;
         }
    }
     //ask for the plaintext
     //printf("Please input your plain text:\n");
     string plaintext = GetString();
     int k = strlen(argv[1]); 
         
     //encrypt the plaintext to cyphertext
     for (int i = 0, j= 0, n = strlen(plaintext);i < n; i++, j++)
     {   
        //recycle the use keyword
        if (j == k)
        {
            j = 0;
        }
        //test and change [i] of the plaintext only to alpha char
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {   
            if (argv[1][j] >= 97 && argv[1][j] <= 122) //the math I came up in order to program uppercases in the keyword
            {
                plaintext[i] = ((plaintext[i] - 'A' + argv[1][j]-97) %26) + 'A';
            }
            else if (argv[1][j] >= 65  && argv[1][j] <= 90) //the math I came up in order to program uppercases in the keyword
            {
                plaintext[i] = ((plaintext[i] - 'A' + argv[1][j]-65) %26) + 'A';
            }
        }     
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
             if (argv[1][j] >= 97 && argv[1][j] <= 122) //the math I came up in order to program uppercases in the keyword
             {
                plaintext[i] = ((plaintext[i] - 'a' + argv[1][j]-97) %26) + 'a';
             }
             else if (argv[1][j] >= 65  && argv[1][j] <= 90) //the math I came up in order to program uppercases in the keyword
             {  
                plaintext[i] = ((plaintext[i] - 'a' + argv[1][j]-65) %26) + 'a';
             }              
        }    
        //leaves unchanged every other possible char by skipping it                   
        else j= j-1;
    }
    // print the cyphertext
    printf("%s\n", plaintext);
    //the requested but unnecessary return 0
    return 0;
}
