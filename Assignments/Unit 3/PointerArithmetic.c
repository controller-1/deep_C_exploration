// Intro to pointer arithmetic: arrays, addresses and pointers

#include <stdio.h>
int main() {
    //! showMemory(start=65520)
    int arr[3] = {15, 16, 17};
    printf("%p\n",arr);  // prints address of first element in arr
    int * ptr = arr;      // since arr is already an address we can assign it to a pointer variable without using &
    * ptr = 2; // * arr   0R  arr[0]
    * (ptr + 1) = 3; // * (arr + 1)   OR  arr[1]     // This syntax will point to the address of the second element of arr
    * (ptr + 2) = 5;// * (arr + 2)   OR arr[2]        // This will point to Third element of arr. 
    
    return 0;
}


/*
The default address of an array will always be the address of its first element.  when doing pointer arithmetic, such as * (ptr + 1),
the +1 will automatically add on the correct number of bytes corresponding to the data type declaration of the pointer variable ptr, which
in this case is type 'int' so it will add on 4 bytes for this system. 
*/
