// Intro to dereferencing using pointers

// Dereferencing is basically using the address and special pointer notation to obtain the value stored at that address. Think of
// it sort as an array of values and if you want a particular value then you specify the location (or address in this case) and then 
// you can get that value. In C, to get the value stored at a particular address the syntax is the following :  * variable

#include <stdio.h>
int main(){
    //! showMemory(start=65520)
    double a = 42.98;
    double * addressOfA = &a;  // Normal declaration and assingment of a pointer variable
    printf("At the address %p there is the value %.2lf\n",addressOfA,* addressOfA); //
    char c = 'm';
    char * addressOfC = &c;
    char d = * addressOfC;
    * addressOfA = 32;
    * addressOfA = * addressOfA + 1;
    printf("At the address %p there is the value %.2lf\n",addressOfA,* addressOfA);
    return 0;
}
