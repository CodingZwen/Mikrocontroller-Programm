#include <c51rx2.h>
#include <lcd.h>
#include <stdio.h>
#include <adda.h>

sfr at P2 LEDs;

void printlcd(const  char *str,int numbertoprint);
void initTimer(void);

void main(void)
{
    unsigned char ADWert;
    while(1)
    {
        ADWert = ain(0); //wir bekommen wert abhängig von spannung 0-5V -> 0-255
        LEDs = ADWert; 
        aout(ADWert);
    }

}






void printlcd(const char *eingabe,int number)
{

   unsigned char buffer[30];
   sprintf(buffer,"Ausgabe: %s  : %d",eingabe,number);
   textlcd(buffer,1);

}


void initTimer(void)
{

//ET0 = 1;    //
//EA=1; //interrupt

EA = 0;

}

void initall(void)
{

initlcd();
   loeschenlcd();
   
}

//ET0 = 1 // interrupt timer
//EX0 = 1 //interrupt 
