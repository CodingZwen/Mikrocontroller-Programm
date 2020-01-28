
/*
"Erstes" C Programm von Sven-Patrick Schulze
24.09.2019

************************************************************
*/


#include <stdio.h>
#include <c51rx2.h>

//Globals

unsigned char pwm_zaehler;
//unsigned char pwm_sollwert;
unsigned char pwm_sollwert[8]={10,20,30,40,50,60,100,200};


//______


/*
sfr at P2 LEDs;
sbit at P3_3 TA;
sbit at P3_2 TZ;
sbit at P1_7 SO; //schloss offen
sbit at P1_6 SS; //schloss schlossen
*/

sbit at P3_2 Taster; //pwm eingang
sbit at P3_3 Taster2; //pwm eingang

sbit at P2_0 led1;
sbit at P2_1 led2;
sbit at P2_2 led3;
sbit at P2_3 led4;
sbit at P2_4 led5;
sbit at P2_5 led6;
sbit at P2_6 led7;
sbit at P2_7 led8;


sfr at P2 LEDs;
sfr at P1 Sollwert;

void init_timer(void);

void main (void) 
{

    init_timer();
    LEDs = 0;

    while(1)
    {
     if(Taster)
         {pwm_sollwert[Sollwert & 0x07] = Sollwert & 0xf8;
         }
    }

}

void Timer_isr(void) interrupt 1
{       
   
    pwm_zaehler++;

    if(pwm_zaehler>=pwm_sollwert[0]) led1=0;
    else                              led1=1;
    if(pwm_zaehler>=pwm_sollwert[1]) led2=0;
    else                              led2=1;
    if(pwm_zaehler>=pwm_sollwert[2]) led3=0;
    else                              led3=1;
    if(pwm_zaehler>=pwm_sollwert[3]) led4=0;
    else                              led4=1;
    if(pwm_zaehler>=pwm_sollwert[4]) led5=0;
    else                              led5=1;
    if(pwm_zaehler>=pwm_sollwert[5]) led6=0;
    else                              led6=1;
    if(pwm_zaehler>=pwm_sollwert[6]) led7=0;
    else                              led7=1;


}



void init_timer(void) 
{
    TMOD =0x12;
    TH0 = 256-100;
    TR0=1;
    ET0 = 1;
    EA=1;
}

void anzeigen(int numbertoprint)
{
char buff[20];
sprintf(buf,"Zahl %2d ", numbertoprint);
}

/*

*/
