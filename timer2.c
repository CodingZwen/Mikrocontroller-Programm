
/*
"Timer für Mikrocontroller
24.09.2019

************************************************************
*/

#include <stdio.h>
#include <c51rx2.h>

sfr at P2 leds;

void delay(unsigned int sekunden);
void delay1ms(void);


void main (void) 
{
  
    leds = 0;

    TMOD = 0b00010001; //wir nehmen beide timer aber aktivieren nur einen davon
    TR1 = 1; //Timer 1 auswaehlen
    TL1 =(65535-65531)%256; // Timerlength -> Timerlow
    TH1 =(65535-65531)/256; // Timerhigh
   
    while(1)
    {
        
    if(TF1)
       { // f=88Hz => T=1/f = 11,36ms = 11363us => Timer soll halbe Zeit erzeugen = 5681
       
        TL1 =(65535-5681)%256; // Timerlength -> Timerlow
        TH1 =(65535-5681)/256; // Timerhigh

       TF1=0;
       P2_1= ~P2_1;
       }
        
     }
}

void delay(unsigned int count)
{
    unsigned int k = count;
    for(;k>0;k--){
    delay1ms();
    }

}

void delay1ms(void)
{

    int k = 125;
    for(;k>0;k--){;}
}
