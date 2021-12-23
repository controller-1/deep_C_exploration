// Array with double variables
/*
Use an array to balance weights. Input number of boxcars and 
their individual weights. Output will array will display how much
to add/remove weight from each boxcar
*/


#include <stdio.h>

int main(void){
    int i, boxcars;
    double weight;
    double TWeight = 0;
    
    scanf("%d",&boxcars);
    
    double bc_weights[boxcars];
    for(i=0;i<boxcars;i++){
        scanf("%lf",&weight);
        bc_weights[i] = weight;
        
        TWeight = TWeight + weight;
    }
    
    // Compute average weight
    double AvgWeight = TWeight/boxcars;
    
    // Subtract each element from the average
    for(i=0;i<boxcars;i++){
        bc_weights[i] = AvgWeight - bc_weights[i];
        printf("%.1lf\n",bc_weights[i]);
    }
    
    return 0;
}
