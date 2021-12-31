// Scope and Blocks in C: scope of variables when using blocks


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

/* Comments: This code was presented during the lecture for introducing
scopes and blocks. There are two blocks above defined by the set of 
curly brackets. The key concept is that the variables defined and initialized
within the inner block are not available outside of it, however, from the inner
block the variables defined outside (in the main block) are available for use
in the inner. What do I mean by available? The codecast command provides a 
useful visualization of what happens in memory (or the stack). Essentially,
when inside the inner block the variables are written and stored in memory like
usual but once the program exits the inner block it then clears the variable
in memory but the value of the variable can still remain in memory at the address
it was stored at. the program will then reuse this memory later if needed. 
*/
