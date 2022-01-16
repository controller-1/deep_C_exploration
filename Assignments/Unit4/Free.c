// Deallocate memory using free()


// Once you free a variable you lose control over that memory location and it can be freely overwritten by any other
// command if the computer needs it. In the lecture video, the code below is an example of allocating and storing a 
// variable a to which it is then free() and subsequently the same memory location is used to store c.


#include <stdio.h>
#include <stdlib.h>
int main(void) {
    //! showMemory(start=438, cursors=[a,b,c])
    int *a, *b, *c;
    a = (int *) malloc(sizeof(int));
    *a = 1;
    printf("I stored %d at memory location %p.\n", *a, a);
    b = (int *) malloc(sizeof(int));
    *b = 2;
    free(a);
    c = (int *) malloc(sizeof(int));
    *c = 3;
    printf("Can I still access a?\n");
    printf("I stored %d at memory location %p.\n", *a, a);
    free(b);
    free(c);
    return 0;
}
