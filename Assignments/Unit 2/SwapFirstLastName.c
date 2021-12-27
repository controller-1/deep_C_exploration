// Swap First/Last Name using char variables
/*
Your program should first read the total number of names (an integer) 
in order to know how many index cards need to be processed altogether. 
Next,  for each index card, your program should read a patron's first 
name and last name and then display these names correctly, that is on 
one line, the last name followed by one space, followed by the first 
name.  Your program should print the reversed name immediately after 
reading the patron's names (ie, it should not wait until it has read 
all of the index cards to begin printing). 

Note that, for ease of viewing, the example below shows all of the 
inputs in one block and all of the outputs in another block, despite 
the fact that programmatically these will be interspersed.  
*/


#include <stdio.h>

int main(void)
{
    int i, numCards;
    char fName[101];
    char lName[101];
    
    scanf("%d",&numCards);
    
    for(i=0;i<numCards;i++)
    {
        scanf("%s",fName);
        scanf("%s",lName);
        
        printf("%s %s\n",lName,fName);
    }

    return 0;
}
