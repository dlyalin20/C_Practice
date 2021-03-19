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
}
candidate;

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
    // indexes over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if the inputted name equals the name of one of the candidates, then the voter's rank choice is that candidate's index
        if (strcmp(candidates[i].name, name) == 0)
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
    // indexes over every votes
    for (int i = 0; i < voter_count; i++)
    {
        // indexes over every candidate
        for (int b = 0; b < candidate_count; b++)
        {
            // if that candidate has not been eliminated, increases their votes by one
            if (!candidates[preferences[i][b]].eliminated)
            {
                candidates[preferences[i][b]].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // creates a double to store to the number of voters such that multiplying by 0.5 causes no rounding
    double count = voter_count;
    // indexes over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if that candidate has the majority of the vote and is still in the race, they are declared the winner
        if ((candidates[i].votes > (0.5 * count)) && (candidates[i].eliminated == false))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // creates a variable to stroe the minimum
    int minimum;
    // sets minimum to the first candidate still in the race
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            minimum = candidates[i].votes;
            break;
        }
    }
    // indexes over every candidate, and, by comparing them against the minimum, constantly adjusts the value to match the current lowest number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes < minimum) && (candidates[i].eliminated == false))
        {
            minimum = candidates[i].votes;
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // x stores the number of candidates with the minimum number of votes
    int x = 0;
    // y stores the number of candidates still in the race
    int y = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == min) && (candidates[i].eliminated == false))
        {
            x++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            y++;
        }
    }
    // if the number of candidates in the race equals the number of candidates with the minimum, then there is a tie
    if (y == x)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // indexes over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has not been eliminated and has the minimum, they are eliminated
        if ((candidates[i].eliminated == false) && (candidates[i].votes == min))
        {
            candidates[i].eliminated = true;
        }
    }
}
