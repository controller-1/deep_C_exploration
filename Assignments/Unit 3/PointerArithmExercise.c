//Suppose you have made the following declarations:

int array[] = {4, 6, 12, -5, -7, 3, 1, 0, -10};
int *ptr1, *ptr2;
ptr1 = array+2;
ptr2 = &ptr1[5];

//What is the value of *(ptr1+1)?  -5
//What is the value of *(ptr2-3)?  -7


// Why?? 
/*
ptr1 = array+2;     //The ptr1 is given the address "array+2", or "&array[2]" (third address of the array if you prefer). 
ptr2 = &ptr1[5];    // The ptr2 is given the address of "&ptr1[5]", or "ptr1 + 5" (sixth address of the new array ptr1 (as array <=> pointer))
The ampersand before ptr1[5] is needed to tell that it is the address, not the the value, that you want.
*/
