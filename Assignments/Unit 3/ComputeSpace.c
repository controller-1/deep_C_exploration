// Compute Space exercise

/* 
Your program should first read an integer number indicating how many 
tracking codes you plan on entering. Next, for each successive tracking code 
your program should read in the integer length of code followed by a space 
and then the type of code ('i' for integer, 'd' for decimal, or 'c' for 
character). Finally your program should print the total amount of space 
required to store all of the tracking codes (in bytes). If the user enters 
an incorrect type for any tracking number, the program should print 
'Invalid tracking code type' and exit.
*/

#include <stdio.h>

int main(void)
{
    int numCodes = 0;
    scanf("%d",&numCodes);
    int space = 0;
    int i = 0;
    int numDigits = 0;
    char type = '\0';
    
    for(i=0;i<numCodes;i++)
    {
        scanf("%d",&numDigits);
        scanf(" %c",&type);
        
        if(type == 'i')
        {
            space = space + numDigits*sizeof(int);
        }
        else if(type == 'c')
        {
            space = space + numDigits*sizeof(char);
        }
        else if(type == 'd')
        {
            space = space + numDigits*sizeof(double);
        }
        else 
        {
            printf("Invalid tracking code type");
            return 0;
        }
    }
    
    printf("%d bytes",space);
    
    return 0;
}
