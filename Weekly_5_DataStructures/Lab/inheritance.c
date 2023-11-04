// Simulate genetic inheritance of blood type

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------
   Person Structure
---------------------*/
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

/*---------------
    Consts
---------------*/
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

/*-------------------------
    Functions Prototypes
-------------------------*/
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *children = (person *) malloc(sizeof(person));
    if (children == NULL)
    {
        printf("Memory allocation failed.\n");
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        /*---------------------------------------------
             Set parent pointers for current person
        ---------------------------------------------*/
        children->parents[0] = parent0;
        children->parents[1] = parent1;

        /*------------------------------------------------------------------------------------
             Randomly assign current person's alleles based on the alleles of their parents
        ------------------------------------------------------------------------------------*/
        children->alleles[0] = parent0->alleles[rand() % 2];
        children->alleles[1] = parent1->alleles[rand() % 2];
    }

    // If there are no generations left to create
    else
    {
        /*--------------------------------
            Set parent pointers to NULL
        --------------------------------*/
        children->parents[0] = NULL;
        children->parents[1] = NULL;

        /*-----------------------------------
            Randomly assign alleles
        -----------------------------------*/
        children->alleles[0] = random_allele();
        children->alleles[1] = random_allele();
    }

    return children;
    return NULL;
}

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
