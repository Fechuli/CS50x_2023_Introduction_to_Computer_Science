#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(const char *str);
char rotate(char c, int key);

int main(int argc, string argv[])
{

    // I verify that there is at least one topic in addition to the program name

    if ((argc != 2) || (!only_digits(argv[1])))
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }

    string text = get_string("plaintext:  ");

    int key = atoi(argv[1]);

    printf("ciphertext:  ");
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", rotate(text[i], key));
    }
    printf("\n");
}

// I need this function to verify that the argument passed to the main actually consists of only numbers.

bool only_digits(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return (false);
        }
    }
    return (true);
}

// I need this function to check if the character I am going to convert is actually alphabetic.
// In case it is not it returns it without applying the key to it.

char rotate(char c, int key)
{
    if (isalpha(c))
    {
        char base = isupper(c) ? 'A' : 'a';
        return (c - base + key) % 26 + base;
    }
    return (c);
}