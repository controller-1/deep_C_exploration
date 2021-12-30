// Memory Usage displayed
/*
Your job is to write a program that shows, in human-readable form 
(see below for specifics), how much memory a set of variables of a certain 
type will use. Your program should read a character that identifies the data 
type ('i' for int, 's' for short, 'c' for char, 'd' for double). Next it should 
read an integer that indicates how many variables of the given type you wish to 
store.

Your program should then calculate the amount of memory required to store the 
given variables. Your program needs to be written in such a way that it would 
also perform correctly on other computers. In other words, rather than 
hard-coding specific sizes for the different variable types, your program 
needs to use the "sizeof()" function to determine how much memory an individual 
variable of a given type needs.

Finally, you need to output the amount of space required by your variables to 
the screen. You need to make sure you provide this output in a form that is 
easy to read for humans. 
*/


#include <stdio.h>

int pretty(int);

int main(void)
{
    int numVar = 0;
    char type = '\0';
    int spaceNeed = 0;
    scanf("%c %d",&type,&numVar);
    
    if(type == 'i')
    {
        spaceNeed = numVar*sizeof(int);
    }
    else if(type == 'c')
    {
        spaceNeed = numVar*sizeof(char);
    }
    else if(type == 'd')
    {
        spaceNeed = numVar*sizeof(double);
    }
    else if(type == 's')
    {
        spaceNeed = numVar*sizeof(short);
    }
    pretty(spaceNeed);
    return 0;
}

int pretty(int bytes)
{
    // input total bytes and output formatted space requirements
    int mill = 0;
    int thou = 0;
    int hund = 0;
    if(bytes <= 999)
    {
        printf("%d B",bytes);
    }
    else if((bytes > 999) && (bytes <= 999999))
    {
        printf("%d KB and %d B",bytes/1000,bytes%1000);
    }
    else if((bytes>999999) && (bytes<=999999999))
    {
        hund = bytes%1000;
        thou = (bytes/1000)%1000;
        mill = (bytes/1000000);
        printf("%d MB and %d KB and %d B",mill,thou,hund);
    }
    return 0;
}
