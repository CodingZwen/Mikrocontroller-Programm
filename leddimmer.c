
/*
"Erstes" C Programm von Sven-Patrick Schulze
24.09.2019

************************************************************
*/


#include <stdio.h>
#include <c51rx2.h>

//Globals

unsigned char pwm_zaehler;
unsigned char pwm_sollwert;


//______


/*
sfr at P2 LEDs;
sbit at P3_3 TA;
sbit at P3_2 TZ;
sbit at P1_7 SO; //schloss offen
sbit at P1_6 SS; //schloss schlossen
*/

sbit at P3_2 Taster; //pwm eingang
sbit at P2_0 led;
sfr at P2 LEDs;
sfr at P1 Sollwert;

void init_timer(void);

void main (void) 
{

    init_timer();
    

    while(1)
    {
        if(Taster)pwm_sollwert = Sollwert;
    }
}

void Timer_isr(void) interrupt 1
{

    pwm_zaehler++;

    if(pwm_zaehler>=pwm_sollwert)
    {led=0;}
    else
    {led=1;}

  
}

//    (pwm_zaehler>=pwm_sollwert) ? led =0 : led=1;  

void init_timer(void)
{

LEDs  = 0;
TMOD =0x12; //8bit timer
TH0 =256-100;
TR0=1;
ET0=1;
EA=1;

}
