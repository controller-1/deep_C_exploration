// Using pointers in functions

/*
Motivation: Recall previous lecture on the scope of blocks and functions. When defining a function it does not see or operate on any 
variables in main(). Additionally, any operations within the function done on the variables passed into the function are not done on the
original variables but rather COPIES of those variables. For this reason pointers are used inside functions when we want to operate
on any variables external of the function definition. See below for an example. 
*/


#include <stdio.h>
void swap(int *,int *);
int main() {
     //! showMemory(start=65520)
     int a = 9;
     int b = 1;
     swap(&a,&b);
     printf("%d %d\n",a,b);
    return 0;
}
void swap(int * a, int * b){ // pass in the addresses of the variables that we want to operate on 
    int tmp = * a;
    * a = * b;
    * b = tmp;
}
