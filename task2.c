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
Dated: 04/09/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>

#define MAXCANDIDATES 20
#define MAXVOTES 99
#define MAXNAME 21
///////////////////////////////////////////////////////////////////////
int getword(char W[], int limit);
// add your other function prototypes here
void read_input(int *m_out, char names[][MAXNAME], int ballots[][MAXCANDIDATES], int *numvotes_out);
void print_eliminating_candidates(int m, int numvotes, char names[][MAXNAME], int ballots[][MAXCANDIDATES]);
/*

*/
///////////////////////////////////////////////////////////////////////



// main program provides traffic control
int
main(int argc, char *argv[]) {
// write your main program here

    int m, numvotes;
    char names[MAXCANDIDATES][MAXNAME];
    int ballots[MAXVOTES][MAXCANDIDATES];

    read_input(&m, names, ballots, &numvotes);
    printf("Stage 1\n=======\n");
    printf("read %d candidates and %d votes\n", m, numvotes);
    print_eliminating_candidates(m, numvotes, names, ballots);

    
    // all done, time to go home
printf("tadaa!\n");
return 0;
}
///////////////////////////////////////////////////////////////////////
// extract a single word out of the standard input, of not
// more than limit characters, argument array W must be
// limit+1 characters or bigger.
// function adapted from Figure 7.13 of Programming, Problem Solving,
// and Abstraction with C, by Alistair Moffat
//
int
getword(char W[], int limit) {
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
///////////////////////////////////////////////////////////////////////
void read_input(int *m_out, char names[][MAXNAME], 
    int ballots[][MAXCANDIDATES], int *numvotes_out){

    int m, i, j;
    if(scanf("%d", &m) != 1){
        printf("ERROR, failed to read m");
        exit(1);
        
    }
    *m_out = m;
    
    for(i = 0; i < m; i++){
        if (getword(names[i], MAXNAME) == EOF){
            printf("Not enough candidates");
        }
    }

    int voters = 0; //people who is voting 
    while (voters < MAXVOTES){
        int success = 1;
        for (j = 0; j < m; j++){
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

void print_eliminating_candidates(int m, int numvotes, char names[][MAXNAME], int ballots[][MAXCANDIDATES]){

    int eliminated[MAXCANDIDATES] = {0};
    int rounds = 0;

    while(1){
        rounds++;
        int count[MAXCANDIDATES] = {0};
        int active_cand = 0;
        

        //the first choice for non eliminated
        for (int voter = 0; voter < numvotes; voter++){
            for (int rank = 1; rank <= m; rank++){
                int exit = 0;
                for (int cand = 0; cand < m; cand ++){
                    if(!eliminated[cand] && ballots[voter][cand] == rank){
                        count[cand]++;
                        exit = 1;
                        break;
                    }
                }
                if(exit){
                    break;
                }
                }
            }
        
        //printing the rounds
        printf("round %d:\n", rounds);
        for(int cand = 0; cand < m; cand++){
            if(!eliminated[cand]){
                double percentage = (count[cand] * 100.0)/ numvotes;
                printf("%s has %d and the percentage is %.2f", names[cand], count[cand], percentage);
                active_cand++;
            }
        }



    }
}


/*
to begin with, i need a loop for the amount of rounds and that essentially is based of the voters
such that for(int rounds = 1; rounds <= m (candidates); rounds ++);
then i need to loop for each of the candidates and see if if they have anything that is the saem as the rounds.
{if (ballot[][]== rounds{something +1}}
*/
