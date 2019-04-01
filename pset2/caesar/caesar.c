#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
// Prompts user for valid numerical key
    int key;
    if(argc == 2)
    {
        for(int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if(!(isdigit(argv[1][i])))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        key = atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
// Prompts user for plain text
    string p = get_string("plaintext: ");
// Encrypt the text and displays cipher text
    printf("ciphertext: ");
    for(int i = 0, n = strlen(p); i < n; i++)
    {
        if(islower(p[i]))
        {
            printf("%c", 'a'+ (p[i] + key - 'a') % 26);
        }
        else if(isupper(p[i]))
        {
            printf("%c", 'A' + (p[i] + key - 'A') % 26);
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}
