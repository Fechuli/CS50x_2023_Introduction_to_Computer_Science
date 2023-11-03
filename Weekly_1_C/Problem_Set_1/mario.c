#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int heigth;
    int blocks;
    int spaces;

    // User's request for the height, only if greater than 0 and less than 8.
    do
    {
        heigth = get_int("Heigth: ");
    }
    while (heigth < 1 || heigth > 8);

    // For loop that repeats as many times as the height is.
    for (int i = 0; i < heigth; i++)
    {
        // For loop that create the spaces.
        for (spaces = 0; spaces < heigth - i - 1; spaces++)
        {
            printf(" ");
        }
        // For loop that create the first stairs of blocks
        for (blocks = 0; blocks <= i; blocks++)
        {
            printf("#");
        }
        // Space between stairs.
        printf("  ");
        // Second for loop for stairs
        for (blocks = 0; blocks <= i; blocks++)
        {
            printf("#");
        }
        printf("\n");
    }
}