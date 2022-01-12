// Example of using pointers of an array of pointers and using dereferencing


#include <stdio.h>

void setToZero(short **);  // Function prototype. Note double star indicating we are passing in a pointer to pointers

int main(){
     //! showMemory(cursors=[t, t[0], t[1]],start=65520)     (Codecast specific tool)
    short a[3] = {1245, 1924, 234};
    short b[2] = {24, 256};
    short * t[2] = {a,b};
    setToZero(t);
    return 0;
}
void setToZero(short ** t) // Many ways to write execute the same thing
{
    *(*t) = 0;        //t[0][0]  OR  *(t[0] + 0)
    *((*t) + 1) = 0;  //t[0][1]  OR *(t[0] + 1)
    *((*t) + 2) = 0;  //t[0][2]  OR *(t[0] + 2)
    *(*(t+1)) = 0;    //t[1][0]  OR *(t[1] + 0)
    *(*(t+1)+1) = 0;  //t[1][1]  OR *(t[1] + 1)
}
