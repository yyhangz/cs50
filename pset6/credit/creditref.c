#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    long card = get_long("Number: ");
    long card_copy = card;
// Calculate zerosum
    int sum = 0;
    card_copy /= 10;
    int digit_count = 0;
// Calculate sum of product of digits of every other digit * 2
    while(card_copy > 0)
    {
        if((card_copy % 10) * 2 < 10)
        {
            sum += (card_copy % 10) * 2;
            card_copy /= 100;
        }
        else
        {
            sum += ((card_copy % 10) * 2) % 10 + 1;
            card_copy /= 100;
        }
        digit_count++;
    }
// Add to sum the digits that were not multiplied by 2
    card_copy = card;
    while(card_copy > 0)
    {
        sum += (card_copy % 10);
        card_copy /= 100;
        digit_count++;
    }
    if(sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if(digit_count == 15 && (floor(card / pow(10, 13)) == 34 || floor(card / pow(10, 13)) == 37))
    {
        printf("AMEX\n");
    }
    else if(digit_count == 13 && floor(card / pow(10, 12)) == 4)
    {
        printf("VISA\n");
    }
    else if(digit_count == 16)
    {
        if(floor(card / pow(10, 15)) == 4)
        {
            printf("VISA\n");
        }
        else if(floor(card / pow(10, 14)) >= 51 && floor(card / pow(10, 14)) <= 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}