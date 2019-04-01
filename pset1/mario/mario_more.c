#include <cs50.h>
#include <stdio.h>

void build(int);
void print_hexleft(int);
void print_space(int);
void print_hexright(int);

int main(void)
{
//Prompting height of pyramid and checking it
    int i;
    int check = 0;
    while(check != 1)
    {
        i = get_int("Enter an integer from 1 to 8: ");
        if(i < 1 || i > 8)
        {
            printf("Invalid input detected\n");
        }
        else
        {
            check = 1;
        }
    }    
    build(i);
}

void build(int i)
{
//Builds lines of pyramid with height i
    int n = 1;
    while(n <= i)
    {
        print_space(i-n);
        print_hexleft(n);
        print_hexright(n);
        n++;
    }
}

void print_space(int s)
{
//Creates s number of spaces in a line    
    int j = 0;
    while(j < s)
    {
        printf(" ");
        j++;
    }
}

void print_hexleft(int h)
{
//Creates h number of # in a line on the left, leaving 2 spaces at the end
    int k = 0;
    while(k < h)
    {
        if(k < h-1)
        {
            printf("#");
            k++;
        }
        else
        {
            printf("#  ");
            k++;
        }
    }
}

void print_hexright(int h)
{
//Creates h number of # in a line on the right,starting a new line at the end
    int k = 0;
    while(k < h)
    {
        if(k < h-1)
        {
            printf("#");
            k++;
        }
        else
        {
            printf("#\n");
            k++;
        }
    }
}
