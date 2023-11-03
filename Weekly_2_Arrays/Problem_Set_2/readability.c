#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int manual_round(float number);

int main(void)
{
    string text = get_string("Text: ");

    int count_l = count_letters(text);
    int count_w = count_words(text);
    int count_s = count_sentences(text);

    float L = (float) count_l / count_w * 100;
    float S = (float) count_s / count_w * 100;
    int index = manual_round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int count_l = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            count_l++;
        }
    }
    return count_l;
}

int count_words(string text)
{
    // Assuming there's at least one word

    int count_w = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            count_w++;
        }
    }
    return count_w;
}

int count_sentences(string text)
{
    int count_s = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_s++;
        }
    }
    return count_s;
}

int manual_round(float number)
{
    if (number >= 0)
    {
        return (int) (number + 0.5);
    }
    else
    {
        return (int) (number - 0.5);
    }
}
