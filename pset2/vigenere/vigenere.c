#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int shift(char);

int main(int argc, string argv[])
{
// Check if there is only 1 key and if it is entirely alphabetical
    if(argc == 2)
    {
        for(int i=0, n = strlen(argv[1]); i < n; i++)
        {
            if(!(isalpha(argv[1][i])))
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
    }    
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
// Prompt user for plain text
    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    int j = 0, k = strlen(argv[1]);
    for(int i = 0, n = strlen(p); i < n; i++)
    {
        if(islower(p[i]))
        {
            printf("%c", 'a'+ (p[i] + shift(argv[1][j % k]) - 'a') % 26);
            j++;
        }
        else if(isupper(p[i]))
        {
            printf("%c", 'A' + (p[i] + shift(argv[1][j % k]) - 'A') % 26);
            j++;
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    return 0;
}

// Calculate the shift in letters using the key given
int shift(char c)
{
    int d;
    if(islower(c))
    {
        d = ((int) c - 'a');
    }
    else
    {
        d = ((int) c - 'A'); 
    }
    return d;
}
