#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    /*---------------------------------------------------------------
            Strcmp help me to verify all the votes.
            This function records only each voter.
            It also goes through the list of candidates and checks
            whether the given name matches any candidate.
            If it finds a match, voters and the assigned category
            record their preferences in the proposal process.
    ---------------------------------------------------------------*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    /*---------------------------------------------------------------
           The tabulate function counts the votes of the remaining
           candidates after some candidates are eliminated.
           It goes through the preferences of each voter and looks
           at who wasn’t made for the highest office.
           It then increases that candidate’s vote count.
    ---------------------------------------------------------------*/
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int preference = preferences[i][j];
            if (!candidates[preference].eliminated)
            {
                candidates[preference].votes++;
                /*------------------
                    Next voter.
                ------------------*/
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    /*---------------------------------------------------------------
        This function determines that there is a clear winner
         who has received more than half of the total votes cast.
         Based on the number of votes cast, it calculates a
         majority threshold and determines whether a candidate’s
         vote exceeds that threshold.
   ---------------------------------------------------------------*/
    int maggioranza = voter_count / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maggioranza)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    /*--------------
        No winner.
    --------------*/
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    /*--------------------------------------------------
         The find_min function finds the
         minimum number of votes in the random list.
         It also goes through candidates
         and maintains a minimum vote.
    --------------------------------------------------*/
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    /*--------------------------------------------------
        This function checks whether the vote is linked
        to all remaining unregistered users.
        Determine whether the total number of votes
        for these candidates is equal to the
        minimum number of votes.
    --------------------------------------------------*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    /*--------------------------------------------------
    The eliminate function eliminates the candidate(s)
    with the lowest number of votes.
    It also goes through the candidates,
    marking the lowest vote-getters as "eliminated."
    --------------------------------------------------*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}