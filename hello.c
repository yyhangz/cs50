#include <stdio.h>
#include <cs50.h>

// Code displays "hello, <name of user>"

void prompt_name(int);

int main(void)
{
    prompt_name(1);
}

//Prompts and displays name of user for stated amount of times
void prompt_name(int n)
{
    int i = 0;
    do
    {
        string name = get_string("What is your name?\n") ;
        printf("hello, %s\n", name);
        i++;
    }
    while(i < n);
}
