// Allocate memory in the heap using malloc()

// See notes in separate file for the differences between stack and heap


#include <stdlib.h>
int main(void){
    //! showMemory(start=272)
    int * intptr;
    double * doubleptr;
    intptr = (int *) malloc(sizeof(int));
    * intptr = 5;
    doubleptr = (double *) malloc(sizeof(double));
    * doubleptr = 9.0;
    return 0;
}
