#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int first;
    int second;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count ;
int candidate_count;
int helper = 0;
int un_sorted[MAX];
int sorted[MAX];
int mix[MAX];
int revlocked[MAX][MAX];
int points[MAX];
int whowin[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
   int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i],name) == 0)
        {
         ranks[i] = rank;
     //    printf("ranks i = %i\n",ranks[i]);
        }

    }
    return name;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // need to somehow put it here preferences[MAX][MAX];
    // probably need to put rank and ranks



    for(int i = 0; i < candidate_count; i++)
    {

            preferences[helper][i] = ranks[i];
       //    printf("ranks %i candidates i = %s\n", ranks[i],candidates[i]);
        //   printf(" preferences [%i][%i] = %i\n", helper , i ,preferences[helper][i]);
    }
    helper++;


    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //The function should add all pairs of candidates where one candidate is preferred to the pairs array.
    //A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
    //The function should update the global variable pair_count to be the number of pairs of candidates.
    //(The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
    pair_count = candidate_count*(candidate_count-1)/2;
    int x = 0;


   // printf("Value of first %i and second %i\n",preferences[0][0] , preferences[0][1]);
    for(int y = 0; y < helper; y++)
    {
        x = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            for(int j = 0; j < candidate_count; j++)
            {
                if( i!=j && i < j)
                 {
                     if (preferences[y][i] < preferences[y][j])
                        {
                        pairs[x].first = i;
                        pairs[x].second = j;
                        pairs[x].winner++;

                       // printf("goes top with x = %i\n", x);
                      //  printf("i %i j %i\n", i , j);
                        x++;
                        }
                        else if (preferences[y][i] > preferences[y][j])
                        {
                        pairs[x].first = i;
                        pairs[x].second = j;
                        pairs[x].loser++;

                      //  printf("goes bottom with x = %i\n", x);
                     //   printf("i %i j %i\n", i , j);
                     //   printf("first candidate value %i and second candidate value %i\n",preferences[y][j] , preferences[y][i]);
                        x++;
                        }
                 }
            }

        }
    }


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int gaper = - 1;
    int sub = 50;
    int mixhelper = 0;

    for(int i = pair_count-1;i >= 0;i--)
    {
    un_sorted[i] = (pairs[i].winner - pairs[i].loser);
    sorted[i] = un_sorted[i];
    }

    // I need to go thru array and find the largest
    // store it in sorted array beginin and restart the sorter untill everything is sorted

    for(int i = 0; i < pair_count; i++)
    {
        mix[i] = i;
        if(sorted[i]<0)
        {
        whowin[i] = 0;
        sorted[i] = sorted [i] * (-1);
        }else if (sorted[i] > 0)
        whowin[i] = 1;
        else
        {
        whowin[i] = 2;
        }
     //   printf("%i\n",whowin[i]);
    }



    while (gaper != 0)
    {
        gaper = 0;
        for(int i = 0; i < pair_count-1;i++)
        {
           if (sorted[i] < sorted[i + 1])
           {
            gaper++;
            sub = sorted[i];
            sorted[i] = sorted[i + 1];
            sorted[i + 1] = sub;

            mixhelper = mix[i];
            mix[i] = mix[i + 1];
            mix[i + 1] = mixhelper;
           }
        }
    }




    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int reversal[MAX][MAX];
    int pair_count1 = 0;


    for(int i = 0; i < pair_count ; i++)
    {
       // printf("unsorted %i\n",un_sorted[i]);
        if(un_sorted[i] < 0)
        {
        locked[i][un_sorted[i]] = false;
        revlocked[i][un_sorted[i]] = true;
       // printf("went up < 0  %i\n",locked[i][un_sorted[i]]);
        }
        else if (un_sorted[i] > 0)
        {
        locked[i][un_sorted[i]] = true;
        revlocked[i][un_sorted[i]] = false;
       // printf("went down > 0  %i\n",locked[i][un_sorted[i]]);
        }
        else
        {
            locked[i][un_sorted[i]] = false;
            revlocked[i][un_sorted[i]] = 0;
        }
    }
    //filling points to zero
    for(int i = 0; i < candidate_count; i++)
    {
        points[i] = 0;
    }

    // check paircount
    for(int i = 0; i < candidate_count;i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(i == j)
            {
                reversal[j][i] = 0;
                reversal[i][j] = 0;

            }
            else if(i < j)
            {

                reversal[i][j] = locked[pair_count1][un_sorted[pair_count1]];
                reversal[j][i] = revlocked[pair_count1][un_sorted[pair_count1]];
                pair_count1++;
            }
        }
    }



    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(reversal[i][j] == 1)
            {
                points[i]++;
            }

        }
    }



        return;

}

// Print the winner of the election
void print_winner(void)
{
    int edge[MAX];
    int edgecounter = 0;
    int k = 0;
    bool cycle = false;
    int j = 0;
    for(int i = 0; i < candidate_count; i++)
    {
        edge[i] = 0;
    }

    for(int i = 0; i < pair_count; i++)
    {
        if(points[i] == candidate_count-1)
        printf("The winner is %s\n",candidates[i]);
        else
        {
            do
            {

                if (whowin[mix[k]] == 0)
                {
                edge[pairs[mix[k]].first] = 1;
            //    printf("edge[%i] = 1 --- did this value was %i\n",pairs[mix[k]].first ,edge[pairs[mix[k]].first]);
                }
                else if(whowin[mix[k]] == 1)
                {
                edge[pairs[mix[k]].second] = 1;
           //     printf("edge[%i] = 1 --- did this value was %i\n",pairs[mix[k]].second ,edge[pairs[mix[k]].second]);
                }

                k++;
                edgecounter = 0;
                for( j = 0; j < candidate_count; j++)
                {
                    if (edge[j] == 1)
                    edgecounter++;
                }
            //    printf("edgecounter is = %i and k is = %i\n",edgecounter ,k);

            }
            while(k >= pair_count || edgecounter != candidate_count-1);

            for(int h = 0 ; h < candidate_count; h++)
            {
                if(edge[h] == 0)
                printf("The winner is %s\n",candidates[h]);

            }
            break;

        }
        break;
    }

    return;

}