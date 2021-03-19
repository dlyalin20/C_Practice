#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    int j = 0;
    if (argc == 2)
    {
        // iterates over every character of the input
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // checks whether is a digit
            if (isdigit(argv[1][i]))
            {
                j++;
            }
            else
            {
                // if j is zero, then realizes that input is wrong
                j = 0;
            }
        }
        // if it counted right, then j should have counted for every char of the input
        if (j == strlen(argv[1]))
        {
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // gets input
    string plaintext = get_string("plaintext: ");
    // will input letter by letter
    printf("ciphertext: ");
    // converts argv[1] from a string to an integer, and uses variable
    int n = atoi(argv[1]);
    // variable for string length on input
    int s = strlen(plaintext);
    // iterates over every letter of the plaintext
    for (int i = 0;  i < s; i++)
    {
        // checks for whether character
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                // formula for converting with looping
                printf("%c", (((plaintext[i] - 97) + n) % 26) + 97);
            }
            if (isupper(plaintext[i]))
            {
                printf("%c", (((plaintext[i] - 65) + n) % 26) + 65);
            }
        }
        // else blank or punct - do nothing
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    // finish line
    printf("\n");
    return 0;
}