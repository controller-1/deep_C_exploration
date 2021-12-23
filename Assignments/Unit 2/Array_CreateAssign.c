
// Arrays
/* 
Create an array with a static value and assign 
values to each cell via user input. 
*/

#include <stdio.h>

int main(void){
    int recipe[10];
    int i, quant;
    for(i=0;i<10;i++){
        scanf("%d",&quant);
        recipe[i] = quant;
    }
    
    int desired;
    scanf("%d",&desired);
    printf("%d",recipe[desired]);
    return 0;
}
