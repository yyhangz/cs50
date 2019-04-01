#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Calculates how many of each coin is needed
int greedy(int, int);

int main(void)
{
// Prompts the user for change owed 
    float change;
    int check = 0;
    do
    {
        change = get_float("Change owed: ");
        if(change < 0)
        {
            printf("Invalid input detected\n");
        }
        else
        {
            check = 1;
        }
        
    }
    while(check == 0);
// Convert money to nearest penny
    int cents = round(change*100);
    int coins = 0;
    coins += greedy(25, cents);
    cents = cents - (greedy(25, cents)*25);
    coins += greedy(10, cents);
    cents = cents - (greedy(10, cents)*10);
    coins += greedy(5, cents);
    cents = cents - (greedy(5, cents)*5);
    coins += greedy(1, cents);
    printf("%i\n", coins);
}    
    
int greedy(int x, int cents)
{
    int coins = 0;
    int check = 1;
    while(check == 1)
    {
        if(cents >= x)
        {
            cents -= x;
            coins++;
        }
        else
        {
            check = 0;
        }
    }
    return coins;
}
