// Final Project Unit 3

/*
Write a function isReverse() that checks whether a given word is the reverse of another given word. 
More precisely, the function should take as inputs two words (null-terminated arrays of characters) 
and return an integer. If indeed the second word is the reverse of the first then the function should 
return the integer 1, otherwise it should return a 0.

Your main() function should read two words from the user input (you can assume that neither word 
has more than 99 characters) and then call the function isReverse, passing both words to this 
function. The function should return an integer as described above and your main program needs to 
print out a sentence, indicating whether indeed, the first word is the reverse of the second word 
(see below examples).

Note: The name of the function needs to be isReverse.

Here are two sample runs:

Input:

stressed
desserts

Output:

stressed is the reverse of desserts

*/

#include <stdio.h>

int isReverse(char *, char *);

int main(void)
{
    char word1[100];
    char word2[100];
    scanf("%s",word1);
    scanf("%s",word2);

    int isreverse = 0;
    isreverse = isReverse(word1,word2);

    if(isreverse)
    {
        printf("%s is the reverse of %s",word1,word2);
    }
    else
    {
        printf("%s is not the reverse of %s",word1,word2);
    }


    return 0;
}


int isReverse(char *word1,char *word2)
{
    //first get num of characters
    int len1 = 0;
    int len2 = 0;
    int i = 0;
    int isreverse = 1;
    int cond;

    while(*(word1 + len1) != '\0')
    {
        len1++;
    }
    while(*(word2 + len2) != '\0')
    {
        len2++;
    }

    //Check first that lengths match to start
    if(len1 != len2)
        return 0;

    //Now check if reversed
    for(i=0;i<len1;i++)
    {
        cond = *(word1 + i) == *(word2 + (len1-1-i));
        if(!cond)
            isreverse = 0;
    }
    return isreverse;
}



/*  SOLUTION
#include <stdio.h>

int isReverse(char *w1, char *w2);
int strlength(char *w);

int main(void) {
    char w1[100];
    char w2[100];
    
    //printf("Please enter first word: ");
    scanf("%s", w1);
    //printf("Please enter second word: ");
    scanf("%s", w2);
    
    if (isReverse(w1, w2)) {
        printf("%s is the reverse of %s\n", w1, w2);
    } else {
        printf("%s is not the reverse of %s\n", w1, w2);
    }
    
    return 0;
}

int isReverse(char *w1, char *w2) {
    int i, l1, l2;
    int rev = 1;
    
    l1 = strlength(w1);
    l2 = strlength(w2);
    if (l1!=l2) {
        rev=0;
    } else {
        for (i=0; i<l1; i++) {
            if (w1[i] != w2[l1-i-1]) {
                rev = 0;
            }
        }
    }
    return rev;
}

int strlength(char *w) {
    int i = 0;
    while (w[i]!='\0') {
        i++;
    }
    return i;
}

*/
