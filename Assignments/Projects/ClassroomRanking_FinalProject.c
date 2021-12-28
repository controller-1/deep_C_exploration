// UNIT 2 FINAL PROJECT

/*
You just computed final scores for all of the students in your classroom and 
would like to tell each student their ranking when compared to the other 
students in your class. For example, if Remi's score is 14, Yan's score is 2 
and Maria's score is 20 then Remi's ranking is 2 since he has the second 
highest score, Yan's ranking is 3 since he has the lowest score and Maria's 
ranking is 1 since she has the highest score amongst the three students.

You'll be given the following inputs: first the number of students, then all 
of the students' final scores, then finally, all of the students' names. Be 
sure to look at the example below.

Your output should be one line per student, with each line displaying the 
student's name followed by "rank is" followed by the student's rank.

The order in which names are displayed in the output should be the same as 
the order given in the input. The ranking starts at 1 (meaning this student 
has the highest score), 2 for the second highest grade etc...

Note that no name has more than 50 characters and there are no more than 30 
students.

Example:

Input

3
14
2
20
Remi
Yan
Maria

Output

Remi rank is 2
Yan rank is 3
Maria rank is 1
*/


// MY SOLUTION
#include <stdio.h>

int main(void)
{
    int i = 0;
    int j = 0;
    int swap;
    int found = 0;
    int item;
    int numPeeps;
    scanf("%d",&numPeeps);      // read number of people/scores
    int scores[numPeeps];
    int scoresSort[numPeeps];   // copy of scores array
    char names[numPeeps][51];   // initialize array of strings for name storage
    int rank[numPeeps];

    // read individual scores and initialize rank array
    for(i=0;i<numPeeps;i++)
    {
        scanf("%d",&scores[i]);
        scoresSort[i] = scores[i]; // Copy scores to sort later
    }
    
    //read names and store in 2D array
    for(i=0;i<numPeeps;i++)
    {
        scanf("%s",names[i]);
    }

    // Sort scores from highest to lowest
    // produces a naturally ranked list of the input scores
    for(i=0;i<numPeeps-1;i++)
    {
        for(j=0;j<numPeeps-1;j++)
        {
            if(scoresSort[j]<scoresSort[j+1])
            {
                swap = scoresSort[j];
                scoresSort[j] = scoresSort[j+1];
                scoresSort[j+1] = swap;
            }
        }
    }
    
    // Linear Search algo
    // Match items from sorted score list and original score list and assign 
    // rank number to rank array using index value of sorted score list
    for(i=0;i<numPeeps;i++)
    {
        found = 0;
        j = 0;
        item = scoresSort[i];
        while(!found && j<numPeeps)
        {
            if(item == scores[j])
            {
                found = 1;
                rank[j] = i+1;
            }
            else
            {
                j++;
            }
        }
    }
    
    for(i=0;i<numPeeps;i++)
    {
        printf("%s rank is %d\n",names[i],rank[i]);   
    }

    
    return 0;
}


// INSTRUCTOR SOLUTION

/*
#include <stdio.h>
int main(void)
{
    int nbStudents;
    char name[51];
    int grade[30];
    int ranking[30];
    int i,j;
    int rank=0;

    scanf("%d", &nbStudents);
        
    for(i=0;i<nbStudents; i++) {
        scanf("%d", &grade[i]);
    }


    **Comments: Clever. Compare a single grade to all others and if it is greater in 
    comparison then add a point to rank. Iterate over all grades and repeat 
    comparison to all others. 
    
    for(i=0;i<nbStudents; i++) {
       rank=0;
       for(j=0;j<nbStudents; j++) { 
         if(grade[i]<grade[j]){
           rank++;
         }
         ranking[i]=rank+1;
       }
    }
    **Comments: Performed ranking computation before reading student names. 
    The pros I see with this is not having to store names. However, the problem
    clearly made it seem that all names had to be read first and then the ouput
    is a neat list of names and rankings in terminal just like in the example.

    for(i=0;i<nbStudents; i++) {
        scanf("%s", name);
        printf("%s rank is %d\n",name,ranking[i]);
    }

    return 0;
}
*/


