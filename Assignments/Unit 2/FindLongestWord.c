// Find longest word in text
/*
Your job is to find the length of the longest word in a text with no 
punctuation or special characters of any kind - only contains words. 
To do so, please write a C-program that takes as a input first the number 
of words in a text, followed by all of the words in the text. The output 
of your program should be the length of the longest word in the text.

To simplify your program, you can assume that the longest word will not 
exceed 100 characters.
*/


#include <stdio.h>

int main(void){
    char word[101];
    int numWords;
    int maxChar = 0;

    scanf("%d",&numWords);
    
    int l = 0;   
    for(int i=0;i<numWords;i++)
    {
        // read word from sentence
        scanf("%s",word);
        
        // Count number of characters in word
        l = 0;
        while(word[l] != '\0')
        {
            l++;
        }
        
        // Store max length
        if(l>maxChar)
        {
            maxChar = l;
        }
    }
    
    printf("%d",maxChar);
    
    return 0;
}
