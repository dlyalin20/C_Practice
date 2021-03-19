#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // iterates over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // compares voters name against the candidates
        if (strcmp(candidates[i].name, name) == 0)
        {
            // if they match, the candidate gains a vote
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int a = 0; // will be used to log candidate that's doing best
    string b; // will be used to log name of best candidate
    int m = 1; // will be used to print name of every candidate if there is a tie
    string c = NULL; // used if there is a two-way tie
    // iterates over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //checks if the number of votes of this candidate is equal to number of votes of other candidates
        if (candidates[i].votes == a)
        {
            // increases m
            m++;
            // used in two-way ties
            c = candidates[i].name;
        }
        // if this candidate is doing better than the previous one
        else if (candidates[i].votes > a)
        {
            // replaces values to those of best candidate
            a = candidates[i].votes;
            b = candidates[i].name;
        }
    }
    // if the number of tied candidates equals m
    if (m == candidate_count)
    {
        // iterates over every candidate to print a tie
        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    // if there is a two-way tie
    else if (c != NULL)
    {
        printf("%s\n%s\n", b, c);
    }
    // print the best candidate
    else
    {
        printf("%s\n", b);
    }
}
