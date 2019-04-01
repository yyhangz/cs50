#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
#include <math.h>

// Learning pointers from test.c are as follows
// Define salt as char salt[3],and salt[2] = '\0' to get string
// Output of crypt() is a string
// password[i] = password[i] + 1 gives next letter if it isnt z

char build_pw(char);

int main(int argc, string argv[])
{
// Checks that there is one and only 1 hashed password
    if(argc != 2)
    {
        printf("Invalid hashed password\n");
        return 1;
    }
// Fill salt with first 2 chars of argv[1]
    char salt[3];
    salt[2] = '\0';
    strncpy(salt, argv[1], 2);
// Generate password and check if crypted password == argv[1] repeatedly
    char pw[6] = "\0\0\0\0\0";
    int check;
    string test;
// for loop with i indicates element 4, j = 3, k = 2, l = 1, m = 0
    for(int i = 0; i < 52; i++)
    {
        for(int j = 0; j < 52; j++)
        {
            for(int k = 0; k < 52; k++)
            {
                for(int l = 0; l < 52; l++)
                {
                    for(int m = 0; m < 52; m++)
                    {
                        pw[0] = build_pw(pw[0]);
                        test = crypt(pw, salt);
                        check = strcmp(test, argv[1]);
                        if(check == 0)
                        {
                            printf("%s\n", pw);
                            return 0;
                        }
                    }
                    pw[1] = build_pw(pw[1]);
                }
                pw[2] = build_pw(pw[2]);
            }
            pw[3] = build_pw(pw[3]);
        }
        pw[4] = build_pw(pw[4]);
    }
}
    
char build_pw(char ltr)
{
    if(ltr == '\0')
    {
        ltr = 'A';
    }
    else if(ltr == 'Z')
    {
        ltr = 'a';
    }
    else if(ltr == 'z')
    {
        ltr = 'A';
    }
    else
    {
        ltr = ltr + 1;
    }
    return ltr;
}
