// Scope and Functions in C: scope of variables when using functions

/*
#include <stdio.h>
int main(){
    //! showMemory(start=65520) (Command specifically for Codecast package)
    int a = 10;
    int b = 11;
    {
        int c = 12;
        int d = 13;
        int e = a + c;
        c = b + d;
        printf("c: %d\n", c);
        printf("e: %d\n", e);
    }
    int f = 14;
    int g = 15;
    printf("f: %d\n",f);
    printf("g: %d", g);
}
*/

// Previously used above to show scope of variables when using a block
// within a block. Now we take the inner block and make it into its own 
// function defined outside. See below:


#include <stdio.h>
void doSomething(int);
int main(){
    //! showMemory(start=65520)
    int a = 10;
    int b = 11;
    int f = 14;
    int g = 15;
    doSomething(b);
    printf("f: %d\n",f);
    return(0);
}

void doSomething(int h)
{
        int a = 20;

        int c = 12;
        int d = 13;
        int e = a + c;
        c = h + d;
        printf("c: %d\n",c);
        printf("e: %d\n",e);
}

/* Comments:
now the function block, unlike the inner block from up top, does not have
access to the variables in main(). Additionally, when calling a function and 
giving it a parameter the parameter is stored in a new variable in memory and 
is for use within the function block. 
