// Strings and repetition
/*
Write a C-program that prints out a word as many times as specified. 
The number of repetitions and the word should be given as input to 
the program. You may assume that the word has no more than 100 characters 
(be sure to also reserve space for the null terminator, \0, though!).
*/


#include <stdio.h>

int main(void){
    int repeat;
    char word[101]; // the last element is reserved for null terminator
    scanf("%d",&repeat);
    scanf("%s",word); //note that scanf("") does not use & for assignment
    for(int i=0;i<repeat;i++)
    {
        printf("%s\n",word);
    }
    return 0;
}
