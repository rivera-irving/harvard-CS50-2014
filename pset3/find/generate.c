/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: Validates the user proper inputs for the command line making sure him inputs the quantity of random numbers desire. If the user fails to comply it will prompt again for the right input.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // TODO: It tells the program, to read “transform” the second command argument in the input as an integer and to store it value in variable “n”.
    int n = atoi(argv[1]);

    // TODO: It tells the program, that when the command lines have 3 arguments to use that third argument as the seed value for desire random generations of numbers. And in the case of not give a seed “third input’ use as the int format of NULL value of time.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // TODO: This loop generates the ask amount of random numbers and printed them out one per line making sure they are between 0 and the LIMIT 65536, thanks to the modulus operator.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // that's all folks
    return 0;
}
