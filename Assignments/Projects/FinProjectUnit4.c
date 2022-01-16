// Project Unit 4: Tracking a fire using arrays

//You have been hired to assist firefighters locate wildfires in a large geographic 
//area. The area is divided into smaller zones. Each zone is scanned via satellite 
//for its average temperature. If a zone has an average temperature strictly greater 
//    than 1000°F, we assume there is a fire in that zone. If the temperature is 
//    between 100 degrees (included) and 1000 degrees (included), we have to further 
//    investigate, so it becomes a "zone to watch."
//
//The large geographic area you are watching is a rectangle with a certain length 
//and width, each given in terms of zones. For example, if the area to be scanned  
//has a length of 6 and width of 9 then it will be divided into 6*9 zones:
//
//----length = 6----
//[ ][ ][ ][ ][ ][ ]   |
//[ ][ ][ ][ ][ ][ ]   w
//[ ][ ][ ][ ][ ][ ]   i
//[ ][ ][ ][ ][ ][ ]   d
//[ ][ ][ ][ ][ ][ ]   t
//[ ][ ][ ][ ][ ][ ]   h
//[ ][ ][ ][ ][ ][ ]   =
//[ ][ ][ ][ ][ ][ ]   9
//[ ][ ][ ][ ][ ][ ]   |
//
//Because your program will be used for a variety of geographic areas (each with its 
//own length and width) your program needs to dynamically allocate the memory for 
//the number of zones it is to handle (vertically and horizontally).
//
//The inputs of the program are first the length, then the width of an area, then 
//the average temperatures of all zones, row by row.
//
//Please remember to free the memory you have allocated.
//
//The output should pinpoint the possible zones with fires with [X] and the watch 
//zone with a [*], the other zone are displayed with [ ].


#include <stdio.h>
#include <stdlib.h>

int ** allocateIntStarArray(int);
int * allocateIntArray(int);


int main(void)
{
    int length = 0;
    int width = 0;
    int ** temps;
    int i = 0;
    int j = 0;
    int tol1 = 100;
    int tol2 = 1000;
    scanf("%d",&length);
    scanf("%d",&width);

    // Initialize and allocate memory
    temps = allocateIntStarArray(width);
    for(i=0;i<width;i++)
    {
        *(temps + i) = allocateIntArray(length);
    }

    // Assign values
    for(i=0;i<width;i++)
    {
        for(j=0;j<length;j++)
        {
            scanf("%d",&temps[i][j]);
        }
    }

    for(i=0;i<width;i++)
    {
        for(j=0;j<length;j++)
        {
            if(temps[i][j]<tol1)
            {
                printf("[ ]");
            }
            else if((temps[i][j]>=tol1) && (temps[i][j]<=tol2))
            {
                printf("[*]");
            }
            else
            {
                printf("[X]");
            }
        }
        printf("\n");
    }


    free(temps);

    return 0;
}

// allocates an array of pointers. Each pointer points to an array of ints
int ** allocateIntStarArray(int num)
{
    int ** ptr = (int **) malloc(num * sizeof(int *));
    return ptr;
}


// allocates space required to store avg temps in one row
int * allocateIntArray(int num)
{
    int * ptr = (int *) malloc(num * sizeof(int));
    return ptr;
}
