// Epidemic example using While loop
/*
In order to be able to better fight various epidemics in a region, 
the department of medicine of a major university has launched a large 
study. Researchers are interested in how fast an epidemic spreads, 
and therefore the speed at which health measures must be put in place.
Your program should first read an integer representing the total 
population of the area. Knowing that a person was infected on day 1 
and that each infected person contaminates two new people every day, 
you must calculate the day at which the entire population of the area 
will be infected.

For a total population of 100 inhabitants, on day 1 a single person 
is infected. This is followed by 2 new people on the second day for 
a total of 3 infected people. On the third day,  6 new people are 
infected for a total of 9 infected people. On the fourth day, 18 new 
people are infected, for a total of 27 people. On the fifth day, 
27 new people infect 54 people for a total of 81 people infected. 
On the sixth day, the last of the 100 people will be infected 
(though the 81 people have the potential to contaminate 162 people) 
so your program shuld output '6'.
*/


#include <stdio.h>

int main(void)
{
    int numInfected = 1;
    int TInfected = numInfected;
    int numPop;
    int day = 1;
    scanf("%d",&numPop);
    
    while(TInfected < numPop)
    {
        day++;
        numInfected = TInfected*2;
        TInfected = TInfected + numInfected;
    }
    printf("%d",day);
    return 0;
}
