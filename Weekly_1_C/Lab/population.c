#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // Prompt for initial population of llama

    int initial_population;
    do
    {
        initial_population = get_int("Start size: ");
    }
    while (initial_population < 9);

    // Prompt for final populationof llama

    int final_population;

    do
    {
        final_population = get_int("Final size: ");
    }
    while (final_population < initial_population);

    // I instantiate two variables, pop for population and diff for the difference between new births and deaths

    int pop;
    int diff;
    int y;

    pop = initial_population;
    y = 0;

    while (pop < final_population)
    {
        diff = (pop / 3) - (pop / 4);
        pop = pop + diff;
        y++;
    }

    // Print number of years
    printf("Years: %i\n", y);
}