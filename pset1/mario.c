#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Let's play Mario\n");
    
    int h;
    
    //ask for the half-pryramid height
    
    do 
    {
        printf("Please challenge Mario with a height greater than 0 and less than 23\nHeight:");
        //ask for the height
        h = GetInt();
        // test for vaild height
        if (h < 0 || h > 23)
        //request retry for vaild input
        {
        printf ("Please retry invalid input: height must be greater than 0 and less than 23\nRetry:");
        h = GetInt();
        }       
    }
    while (h < 0 || h > 23);
    
    //create pryramid  
    for ( int i = 0; i < h; i++)
    {
        //printf spaces
        for ( int sp = h - i; sp > 1; sp--)
            {
            printf(" ");
            }
        //printf hashess
        for ( int hash = 0; hash - 2 < i  ; hash++)
            {
            printf ("#");
            }
        //printf new line
        printf("\n");
    }
           
}
