// Branch inside loop
/*
You want to determine the number of cities 
in a given region that have a population 
strictly greater than 10,000. To do this, 
you write a program that first reads the 
number of cities in a region as an integer, 
and then the populations for each city one 
by one (also integers).
*/


#include <stdio.h>

int main(void)
{
    int i, numCities,Pop;
    int TCities = 0;
    scanf("%d",&numCities);
    
    for(i=0;i<numCities;i++)
    {
        scanf("%d",&Pop);
        if(Pop>10000)
        {
            TCities = TCities + 1;
        }
    }
    
    printf("%d",TCities);
    
    return 0;
}
