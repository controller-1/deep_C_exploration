// Nested For loop
/*
Create a program that displays on the screen 
a square of n x n stars, with the integer n given 
as an input.
*/


#include <stdio.h>

int main(void)
{
    int numStar;
    scanf("%d",&numStar);
    
    for(int i=0;i<numStar;i++)
    {
        for(int j=0;j<numStar;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    
    return 0;
}
