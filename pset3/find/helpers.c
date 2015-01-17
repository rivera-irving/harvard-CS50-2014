/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm: bubble sort
    for (int i = 0; i < n; i++)
        {
            for ( int j = i+1; j < n; j++)
            {    
                if (values[i] > values[j])
                {
                int swapvalue = values[j];
                values[j] = values[i];
                values[i] = swapvalue;
                }   
            }
            //printf("%i\n", values[i]);   
        }
    return;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm binary search
    if (n < 0)
    {
        return false;
    }     
    // call for sort in order to bs to work 
    sort(values, n);
    // index of inital positions
    int i0 = 0 , ii = n - 1, imid = 0;
    // tests to find the value      
    while (i0 <= ii)
    {   
       imid = i0 + (ii-i0) / 2;
       if (value < values[imid])
       {
            ii = imid -1;
       }   
       else if (value > values[imid])
       {
            i0 = imid +1;
       }
       else if (value == values [imid])
       {         
            return true; 
       }
       else 
       {
            return false;
       }        
    }
return 0;        
}
