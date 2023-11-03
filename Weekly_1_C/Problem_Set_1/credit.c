#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    int sum = 0;
    int isSecond = 0;

    // Credit card number
    number = get_long("Number: ");

    long originalNumber = number;

    // Counter for digits of number
    int count = 0;
    while (originalNumber > 0)
    {
        count++;
        originalNumber /= 10;
    }

    // Reset
    originalNumber = number;

    // Luhn's Algorithm
    while (number > 0)
    {
        int digit = number % 10;

        if (isSecond)
        {
            digit = digit * 2;
            if (digit > 9)
            {
                digit = digit - 9;
            }
        }

        sum += digit;
        isSecond = !isSecond;
        number /= 10;
    }

    // Check the first two digits (or the first digit in the case of VISA) of the original number
    while (originalNumber >= 100)
    {
        originalNumber /= 10;
    }

    if (sum % 10 == 0)
    {
        if ((originalNumber >= 40 && originalNumber < 50) && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if ((originalNumber >= 51 && originalNumber <= 55) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((originalNumber == 34 || originalNumber == 37) && count == 15)
        {
            printf("AMEX\n");
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