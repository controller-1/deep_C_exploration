// "Guess my number" using while loop and if statements
/*
We would like you to develop a program capable of making a child 
play automatically the game of "more or less" -- the child must 
try to guess a secret number. The program should respond to each 
guess with "it is more" or "it is less" until the child finds the 
right number.

Your program must first read an integer indicating the number that 
the child will have to find during the game. Next the program should 
repeatedly read the player's guesses and display the text "it is more" 
if the child has submitted a smaller number or "it is less" if 
they have submitted a larger number. Once the correct number is 
reached, the program should print "Number of tries needed:" followed 
by a new line and the integer number of tries that it took the 
guesser.
*/


#include <stdio.h>

int main(void)
{
    int numSecret;
    int numTries = 0;
    scanf("%d",&numSecret);
    int guess = 0;
    
    while(guess != numSecret)
    {
        scanf("%d",&guess);
        numTries++;
        if(guess<numSecret)
        {
            printf("it is more\n");
        }
        if(guess>numSecret)
        {
            printf("it is less\n");
        }
        
    }
    printf("Number of tries needed:\n");
    printf("%d",numTries);
    return 0;
}
