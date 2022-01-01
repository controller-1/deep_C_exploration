// Introduction to Pointers

#include <stdio.h>
int main(){
    //! showMemory(start=65520)   // Codecast specific command
    int a = 42;
    double d = 58.394;
    char c = 'r';
  
  /* 
  We will assign the address of each of the variables above to a new variable. How do we declare and intiliaze this variable?
  First specify the data type of the variable we want the address. Then follow it by an asterisk, which is the special notation
  for specifying that the new variable we are creating will contain an address, in other words a pointer. Specify the name of this
  new variable containing the address. To initialize and assign an address use the & symbol followed immediately by the variable we
  want the address of. The printf() format specified is %p. The addresses are in form of hexadecimal and will be displayed as such. For 
  a 32 bit system, the pointer variable will take up 4 bytes, which corresponds to 32 bits. 
  */
    int * addressOfA = &a;  
    printf("address of a: %p\n", addressOfA);
    double * addressOfD = &d;
    printf("address of d: %p\n", addressOfD);
    char * addressOfC = &c;
    printf("address of c: %p\n", addressOfC);
    return 0;
}
