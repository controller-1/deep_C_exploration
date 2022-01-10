// Working with arrays of pointers

#include <stdio.h>
int main(void){
     //! showMemory(cursors=[a, arrays[0], b, arrays[1], c, arrays[2]], start=65520)
    short a[3] = {234,655, 843};
    short b[2] = {12, 62};
    short c[4] = {3456, 3467, 23, 276};
    short * arrays[3] = {a, b, c};
    * arrays[0] = 5;
    arrays[0][0] = 0;
    * (arrays[0] + 1) = 6;    // These two lines are equivalent
    arrays[0][1] = 0;         // --
    * (arrays[0] + 2) = 7;
    arrays[0][2] = 0;
    * arrays[1] = 3;
    arrays[1][0] = 0;
    * (arrays[1] + 1) = 4;
    arrays[1][1] = 0;
    return 0;
}
