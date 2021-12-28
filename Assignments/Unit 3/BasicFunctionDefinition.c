//Define a simple function

#include <stdio.h>
// Function definition in between #include and main()
// first "int" defines the data type of what is to be returned
// The arguments must also be defined with data types.
// 
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
