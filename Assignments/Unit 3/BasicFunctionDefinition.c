//Define a simple function

#include <stdio.h>
// Function definition in between #include and main()
// first "int" defines the data type of what is to be returned
// The arguments must also be defined with data types.
// 
// ** note that sum() is defined above main() but its also possible to define below by using a prototype function. See below.
int sum(int x, int y){ // Here x and y are called PARAMETERS
    int compute;
    printf("Starting the computation!\n");
    compute = x+y;
    printf("Finished the computation successfully!\n");
    return compute;
}
int main(void) {
    int a,b;
    int result;
    printf("Please enter two numbers: ");
    scanf("%d%d", &a, &b);
    printf("You entered %d and %d.\n", a, b);
    result = sum(a, b); // Here a and b are called ARGUMENTS. These get copied to the parameters when the function is ran
    printf("Result of the sum = %d.\n", result);
    return 0;
}



// According to Instructor: the below style is better practice

/*
#include <stdio.h>
int sum(int, int); //function PROTOTYPE. specifies data types only so that compiler is stays happy and is aware that it will be defined later
int main(void) {
    int a, b;
    int result;
    printf("Please enter two integers: ");
    scanf("%d%d", &a, &b);
    printf("You entered %d and %d.\n", a, b);
    result = sum(a, b); //copies of the VALUES of the ARGUMENTS a and b
    printf("Result of the sum = %d.\n", result);
    return 0;
}
// Function DEFINITION
int sum(int x, int y){ //values are copied into PARAMETERS x and y
    int compute;
    printf("Starting the computation!\n");
    compute = x + y;
    printf("Finished the computation successfully!\n");
    return compute;
}
*/
