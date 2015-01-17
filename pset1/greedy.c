#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float h;
    printf("Let's make cents\n");
        
    //ask for the change owed
    do 
    {
        printf("How much change is owed?\n Please input a decimal'0.00' amount greater than 0.00\n Change:");
        //ask for the cents...
        h = GetFloat(); 
        // test for vaild cents
        if (h < 0 )
        //request retry for vaild input
        {
            printf ("Please retry invalid input: Change must be greater than 0.00\nRetry:");
            h = GetFloat();
        }       
    }
    while (h < 0);
    
    //coins counting loops
    int coins, dollars, cents; 
    coins = 0;
    dollars = h;
    // solving imprescision get cents amount
    cents = round ( (h - dollars ) * 100); 
    
    //it counts # of coins for the cents amout
    do 
    {
        //quarters  
        while (cents >= 25)
        {
        cents = cents - 25;
        coins++;
        }
    
        //dimes
        while (cents >= 10)
        {
        cents = cents - 10;
        coins++;
        }
        
        //nickels
        while (cents >= 5)
        {
        cents = cents - 5;
        coins++;
        }
        
        //pennies
        while (cents >= 1)
        {
        cents = cents - 1;
        coins++;
        } 
    }
    while (cents > 0);
    
    // greedly solves # quarters that it will issue for the dollar amount
    coins = coins + 4 * dollars;
    
    //numbers of coins answer
    printf("%d\n", coins);
             
}
