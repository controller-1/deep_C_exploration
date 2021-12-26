// While Loops: Monitoring a chemical experiment
/*
Your program should first read two integers representing the minimum and 
maximum safe temperatures. Next, your program should continuously read 
temperatures (integers) that are being provided by the device. Once the 
chemical reaction is complete the device will send a value of -999, 
indicating to you that temperature readins are done. For each recorded 
temperature that is in the correct range (it could also be equal to the 
min or max values), your program should display the text "Nothing to 
report". But as soon as a temperature reaches an unsafe level your 
program must display the text "Alert!" and stop reading temperatures 
(although the device may continue sending temperature values).
*/


#include <stdio.h>

int main(void){
    int temp, UpTemp, LoTemp;
    scanf("%d",&LoTemp);
    scanf("%d",&UpTemp);
    
    int Flag1 = 1;
    while(Flag1)
    {
        scanf("%d",&temp);
        if( (temp>=LoTemp) && (temp<=UpTemp) )
        {
            printf("Nothing to report\n");
        }
        else  
        {
            if(temp != -999)
            {
                printf("Alert!");
                Flag1 = 0;
            }
            else
            {
                Flag1 = 0;
            }
        }
    }
    
    return 0;
}
