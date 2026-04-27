/* Program to implement Australian House of Representatives preferential
voting and determine election outcomes from vote preference orderings.
Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
August 2025, with the intention that it be modified by students
to add functionality, as required by the assignment specification.
All included code is (c) Copyright University of Melbourne, 2025
Student Authorship Declaration:
(1) I certify that except for the code provided in the initial skeleton
file, the program contained in this submission is completely my own
individual work, except where explicitly noted by further comments that
provide details otherwise. I understand that work that has been
developed by another student, or by me in collaboration with other
students, or by non-students as a result of request, solicitation, or
payment, may not be submitted for assessment in this subject. I
understand that submitting for assessment work developed by or in
collaboration with other students or non-students constitutes Academic
Misconduct, and may be penalized by mark deductions, or by other
penalties determined via the University of Melbourne Academic Honesty
Policy, as described at https://academicintegrity.unimelb.edu.au.
(2) I also certify that I have not provided a copy of this work in either
softcopy or hardcopy or any other form to any other student, and nor will
I do so until after the marks are released. I understand that providing
my work to other students, regardless of my intention or any undertakings
made to me by that other student, is also Academic Misconduct.
(3) I further understand that providing a copy of the assignment
specification to any form of code authoring or assignment tutoring
service, or drawing the attention of others to such services and code
that may have been made available via such a service, may be regarded as
Student General Misconduct (interfering with the teaching activities of
the University and/or inciting others to commit Academic Misconduct). I
understand that an allegation of Student General Misconduct may arise
regardless of whether or not I personally make use of such solutions or
sought benefit from such actions.
Signed by: Arthur Tang 1760368
Dated: 10/09/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>

#define MAXCANDIDATES 20
#define MAXVOTES 999
#define MAXNAME 21
#define FOUND 1
#define NOTFOUND -1
#define MAJORITYPERCENTAGE 0.5

///////////////////////////////////////////////////////////////////////
// Initialising funcitons:
// Stage 1
void print_last_voter_preferences(int num_candidate, int numvotes, 
    char candidate_names[][MAXNAME], int ballots[][MAXCANDIDATES]);

// Stage 2
int getword(char W[], int limit);

void read_input(int *num_candidate_out, char candidate_names[][MAXNAME], 
    int ballots[][MAXCANDIDATES], int *numvotes_out);

void count_votes(int num_candidate, int numvotes, 
    int ballots[][MAXCANDIDATES], int eliminated[], int vote_count[]);

void print_round (int num_candidate, char candidate_names[][MAXNAME], 
    int vote_count[], int eliminated[], int round, int numvotes);

int check_winner(int num_candidate, int vote_count[], 
    int eliminated[], int numvotes);

int eliminate_candidate(int num_candidate, int vote_count[], int eliminated[]);

int last_remaining (int num_candidate, int eliminated[]);

// Stage 3
void print_round_sorted (int num_candidate, char candidate_names[][MAXNAME], 
    int vote_count[], int eliminated[], int round, int numvotes);

int handle_round_output(int num_candidate, int vote_count[], 
    int eliminated[], int numvotes, int *rounds, 
    char candidate_names[][MAXNAME]);
///////////////////////////////////////////////////////////////////////



// main program provides traffic control
int
main(int argc, char *argv[]) {
Instructor
| 10/01 at 5:43 pm
Grading comment:
Your program structure could could be improved by abstracting most of logic in this main function into run_stage_1(...) , run_stage_2(...), run_stage_3(...) helper functions.

The main function should be treated as a controller which directs the flow of your program, delegating the logic of the computations and the printing of outputs to helper functions where possible. I have not made a deduction, as your main function is still a reasonable length.

    
    //initialise the variables
    int num_candidate, numvotes;
    char candidate_names[MAXCANDIDATES][MAXNAME];
    int ballots[MAXVOTES][MAXCANDIDATES];
    int eliminated[MAXCANDIDATES] = {0};
    int vote_count[MAXCANDIDATES] = {0};
    int rounds = 1;


    read_input(&num_candidate, candidate_names, ballots, &numvotes);
    printf("\n");

    // Stage 1
    printf("Stage 1\n=======\n");
    printf("read %d candidates and %d votes\n", num_candidate, numvotes);
    print_last_voter_preferences(num_candidate, 
        numvotes, candidate_names, ballots);
    printf("\n");


Instructor
| 10/01 at 5:57 pm
Grading comment:
White space should be used consistently throughout your code to increase its readability and general aesthetic appeal. Separating major computational blocks of code with single newlines is a good idea to improve readability, however double newlines should really be avoided inside the bodies of functions, and you should definitely not swap between double and single newlines!

    // Stage 2
    printf("Stage 2\n=======\n");

    while(1){
        count_votes(num_candidate, numvotes, ballots, eliminated, vote_count);

        print_round(num_candidate, candidate_names, 
            vote_count, eliminated, rounds, numvotes);

        if(handle_round_output(num_candidate, vote_count, 
            eliminated, numvotes, &rounds, candidate_names) == FOUND){
            break;
        }
    }
    printf("\n");

    // Resetting the arrays and variable for Stage 3
    for (int i = 0; i < num_candidate; i++) {
        eliminated[i] = 0;
        vote_count[i] = 0;
    }
    rounds = 1;


    // Stage 3
    printf("Stage 3\n=======\n");
    while(1){
Instructor
| 10/01 at 5:47 pm
Grading comment:
Lines 137-148 are almost an exact duplicate of lines 114-124. These should be abstracted into a single general function. [-0.5]

        count_votes(num_candidate, numvotes, ballots, eliminated, vote_count);

        // The only difference between Stage 2 and Stage 3
        print_round_sorted(num_candidate, candidate_names, 
        vote_count, eliminated, rounds, numvotes);
Instructor
| 10/01 at 5:46 pm
Grading comment:
Wrapped lines of code should be indented to make clear that they are part of the same statement (which you did well on line 118).


        if(handle_round_output(num_candidate, vote_count, 
            eliminated, numvotes, &rounds, candidate_names) == FOUND){
            break;
        }
    }


    // all done, time to go home
    // algorithms are fun
    printf("tadaa!\n");
    return 0;
}
///////////////////////////////////////////////////////////////////////
// extract a single word out of the standard input, of not
// more than limit characters, argument array W must be
// limit+1 characters or bigger.
// function adapted from Figure 7.13 of Programming, Problem Solving,
// and Abstraction with C, by Alistair Moffat

int getword(char W[], int limit) {
    int c, len=0;
    /* first, skip over any non alphabetics */
    while ((c=getchar())!=EOF && !isalpha(c)) {
        /* do nothing more */
    }
    if (c==EOF) {
        return EOF;
    }
    /* ok, first character of next word has been found */
    W[len++] = c;
    while (len<limit && (c=getchar())!=EOF && isalpha(c)) {
        /* another character to be stored */
        W[len++] = c;
    }
    /* now close off the string */
    W[len] = '\0';
    return 0;
}

// Extracts the input, of not more than limit characters,
// Into the arrays for further computation
void read_input(int *num_candidate_out, char candidate_names[][MAXNAME], 
    int ballots[][MAXCANDIDATES], int *numvotes_out){


    // An error occurs if the input format is wrong
    // Stores the number of candidates
    int num_candidate, i, j;
    if(scanf("%d", &num_candidate) != 1){
        printf("ERROR, failed to read num_candidate");
        exit(1);
        
    }
    *num_candidate_out = num_candidate;
    
    // Starts reading and storing candidate names
    for(i = 0; i < num_candidate; i++){
        if (getword(candidate_names[i], MAXNAME) == EOF){
            printf("Not enough candidates");
            exit(1);
        }
    }

    // Stores voters preferences
    // The success flag helps to end loop when all voters has been read
    int voters = 0;
    while (voters < MAXVOTES){
        int success = 1;
        for (j = 0; j < num_candidate; j++){
            if(scanf("%d", &ballots[voters][j]) != 1){
                success = 0;
                break;
            }
        }
        if(!success) break;
        voters++;
    }
    *numvotes_out = voters;
}

// Count votes by assigning each voter’s preference to the highest-ranked
// Candidate who has not been eliminated.
void count_votes(int num_candidate, int numvotes, 
    int ballots[][MAXCANDIDATES], int eliminated[], int vote_count[]){
    
    for (int cand_id = 0; cand_id < num_candidate; cand_id++) {
    vote_count[cand_id] = 0;
    }
    
    // Looping through each voter and finding the first rank preference
    // An exit flag was used to help exit the loop
    for (int voter_id = 0; voter_id < numvotes; voter_id++){
        for (int rank = 1; rank <= num_candidate; rank++){
            int found_preference = 0;
            for (int cand_id = 0; cand_id < num_candidate; cand_id++){
                if(!eliminated[cand_id] && ballots[voter_id][cand_id] == rank){
                    vote_count[cand_id]++;
                    found_preference = 1;
                    break;
                }
            }
            if(found_preference){
                break;
            }
        }
    }
}

// Prints out the rounds, the remaining candidates and their
// Respective votes and percentages
void print_round(int num_candidate, char candidate_names[][MAXNAME], 
    int vote_count[], int eliminated[], int round, int numvotes){

    printf("round %d...\n", round);

    for(int cand_id = 0; cand_id < num_candidate; cand_id++){
        if(!eliminated[cand_id]){
            double percentage = (vote_count[cand_id] * 100.0)/ numvotes;
            printf("    %-10s          :%4d votes,%6.1f%c\n",
                candidate_names[cand_id], vote_count[cand_id], percentage,'%');
            
        }
    }
}

// Determines the winner by percentage over 50
// Returns either the index of the winner or NOTFOUND
int check_winner(int num_candidate, int vote_count[], 
    int eliminated[], int numvotes){
    for (int cand_id = 0; cand_id < num_candidate; cand_id++){
        if(!eliminated[cand_id] && vote_count[cand_id] > numvotes * 
            MAJORITYPERCENTAGE){
            return cand_id;
        }
    }
    return NOTFOUND;
}

// Eliminates the candidate with the least vote
// Either returns the index of the candidate that will be eliminated
// Or NOTFOUND
int eliminate_candidate(int num_candidate, int vote_count[], int eliminated[]){
    
    int min_cand = NOTFOUND;
    int min_vote = MAXVOTES + 1;
    // If there is a tie, it eliminates the candidate that appears first
    for (int cand_id = 0; cand_id < num_candidate; cand_id++){
        if(!eliminated[cand_id] && vote_count[cand_id] < min_vote){
            min_vote = vote_count[cand_id];
            min_cand = cand_id;
        }
    }

    if (min_cand != NOTFOUND){
        eliminated[min_cand] = 1;
        return min_cand;
    }

    return NOTFOUND;
}

// Check for the last candidate remaining
int last_remaining (int num_candidate, int eliminated[]){
    int remaining = 0;
    int remaining_cand;

    for (int cand_id = 0; cand_id < num_candidate; cand_id++){
        if(!eliminated[cand_id]){
            remaining++;
            remaining_cand = cand_id;
        }
    }

    if (remaining == 1){
        return remaining_cand;
    } else {
        return NOTFOUND;
    }
        
}

// Finds and prints the last voter preference in ranking
void print_last_voter_preferences(int num_candidate, int numvotes, 
    char candidate_names[][MAXNAME], int ballots[][MAXCANDIDATES]){
    
    int last_voter = numvotes -1;   
    printf("voter %d preferences...\n", numvotes);
    
    
    for(int rank = 1; rank <= num_candidate; rank++){
        for(int cand = 0; cand < num_candidate; cand++){
            if( rank == ballots[last_voter][cand]){
                printf("    rank %2d: %s\n", rank, candidate_names[cand]);
            }
        }
    }
}

// Modified version of Print_round, it now prints the sorted version
// From decreasing votes, and alphabetically if there is a tie
void print_round_sorted(int num_candidate, char candidate_names[][MAXNAME], 
Instructor
| 10/01 at 5:52 pm
Grading comment:
This function has a lot of repeated code with your earlier print_round(...) function. These should be combined into a more general function that can handle the round printing for both stages 2 and 3.

    int vote_count[], int eliminated[], int round, int numvotes){
    
    // Creates an indicies array, so the order is stored 
    // In indices instead of the original index
    int indices[MAXCANDIDATES];
    for( int i = 0; i< num_candidate; i++){
        indices[i] = i;
    }


    // Modified version of insertion sort
    // Sorts the indices based on votes and 
    // Alphabetical order if votes are ties
    for (int i = 1; i < num_candidate; i++){
Instructor
| 10/01 at 5:51 pm
Grading comment:
Insertion sort could be neatly abstracted into its own sort_candidates(...) function, which would reduce the length and complexity of this function and improve the overall program structure. This would also make it easier to see how you could combine the round printing logic for stages 2 and 3 into a single function to eliminate the duplicate code segments. [-0.5]


        int key = indices[i];
        int j = i-1;
        // it will only enter the loop if:
        // votes ties && name is not in order
        // j >= 0 && vote < key
        while(j >= 0 && 
            (vote_count[indices[j]] < vote_count[key] || 
            (vote_count[indices[j]] == vote_count[key] && 
            strcmp(candidate_names[indices[j]], candidate_names[key]) > 0))){

            indices[j+1] = indices[j];
            j = j-1;
            
        }
        indices[j+1] = key;

    }

    printf("round %d...\n", round);
    // It prints the round with the sorted indices
    for(int cand_id = 0; cand_id < num_candidate; cand_id++){
        if(!eliminated[indices[cand_id]]){
            double percentage = (vote_count[indices[cand_id]] * 100.0)/
            numvotes;
            printf("    %-10s          :%4d votes,%6.1f%c\n",
                candidate_names[indices[cand_id]], 
                vote_count[indices[cand_id]], percentage,'%');
            
        }
    }
}


// This is a helper funciton that handles everything after printing the round
int handle_round_output(int num_candidate, int vote_count[], 
    int eliminated[], int numvotes, int *rounds, 
    char candidate_names[][MAXNAME]){
    

Instructor
| 10/01 at 5:53 pm
Grading comment:
See my earlier comment regarding consistent use of whitespace.

    


    int winner = check_winner(num_candidate, 
        vote_count, eliminated, numvotes);

    int the_last_rem = last_remaining(num_candidate, eliminated);

    int is_eliminated = eliminate_candidate(num_candidate, 
        vote_count, eliminated);

    (*rounds)++;
    printf("%8s\n", "----");

    // Checks if there is a winner by having majority of the votes
    if (winner != NOTFOUND){
        printf("    %s is declared elected\n", candidate_names[winner]);
        printf("\n");
        return FOUND;
    }

    // Checks if there is only one candidate remaining
    if (the_last_rem != NOTFOUND){
        printf("    %s is declared elected\n", 
            candidate_names[the_last_rem]);
        printf("\n");
        return FOUND;
    }
    
    // Checks if any candidate has been eliminated
    if (is_eliminated != NOTFOUND){
        printf("    %s is eliminated and votes distributed\n", 
            candidate_names[is_eliminated]);
    }

    printf("\n");
    return NOTFOUND;
    }

    