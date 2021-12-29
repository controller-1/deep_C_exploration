// Function to find min
/*
The goal of this problem is to find the smallest integer in a list of numbers.

To help you with this task, please write a function called min() that finds and 
returns the smallest amongst two integers (be sure to also write a prototype 
for this function). The function thus takes two integers as input and returns 
the smallest of the two. This function will use an if statement with a 
condition that contains either "less than" or "greater than".

Next, please use min() in your main function to work your way through an 
entire list of numbers in order to find its minimum. The first number you 
read gives the number of elements in the list of integers under consideration. 
You will then read the integer values, using min() to keep only the smallest 
integer read at each step. In the end, please print out the smallest integer 
in the list.
*/


#include <stdio.h>

int min(int,int);

int main(void)
{
    int numElements = 0;
    scanf("%d",&numElements);
    int nums[numElements];
    int i = 0;  
    int minimum = 0;
    
    // read in values to nums array
    for(i=0;i<numElements;i++)
    {
        scanf("%d",&nums[i]);
    }
    
    // return minimum of array
    minimum = nums[0]; // initialize min to first element in nums
    for(i=0;i<numElements;i++)
    {
        minimum = min(minimum, nums[i]); // compares min, which is initialized to some 
        // value contained in the array, to all elements in the array and keeps
        // the lowest value 
    }
    
    printf("%d",minimum);
    
    return 0;
    
}

int min(int a,int b)
{
    // Returns lowest number between a and b
    if(a>b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

