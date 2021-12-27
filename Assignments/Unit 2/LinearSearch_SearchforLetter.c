// Linear Search: is there a 't'?
/*
You are conducting a linguistic study and are interested in finding 
words that contain the letter 't' or 'T' in the first half of the word 
(including the middle letter if there is one). Specifically, if the 
first half of the word does contain a 't' or a 'T', your program 
should output a 1. If the first half does not contain the letter 't' 
or 'T', but the second half does, then your program should output a 2.
Otherwise, if there is no 't' or 'T' in the word at all, your 
program's output should be -1. You may assume that the word entered 
does not have more than 50 letters.
*/


#include <stdio.h>

int main(void) {
    char word[51];
    int i = 0;
    int j = 0;
    int length = 0;
    int found = 0;
    int stopInd = 0;
    
    // Read word and compute length
    scanf("%s",word);
    while(word[i] != '\0')
    {
        length++;
        
        //Compute index for first/second half
        stopInd = length/2;
        if(length%2 != 0)
        {
            stopInd = length/2 + 1;
        }
        i++;
    }
    
    // Linear search
    while((!found) && (word[j] != '\0') )
    {
        if((word[j] == 'T') || (word[j] == 't'))
        {
            found = 1;
        }
        else
        {
            j++;
        }
    }
    
    // Print in which half the character lives (if at all)
    if(j<=stopInd)
    {
        printf("%d",1);
    }
    else if(found == 0)
    {
        printf("%d",-1);
    }
    else
    {
        printf("%d",2);
    }
	return 0;
}


/* Solution:
#include <stdio.h>
int main(void)
{
	char word[51];
	int length = 0;
	int i,found, maxindex;

	scanf("%s", word);
	
	while (word[length]!='\0')
	    length++;
	if (length%2==0)
	    maxindex = length/2-1;
	else
	    maxindex = length/2;
	
	i = 0;
	found = 0;
	while (!found && i < length) {
		if (word[i]=='t' || word[i]=='T') found++;
		else i++;
	}

	if (!found) 
	    printf("-1");
	else if (i <= maxindex) printf("1");
	else printf("2");

	return 0;
}
*/
