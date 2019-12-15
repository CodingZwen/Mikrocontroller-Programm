#include <c51rx2.h>
#include <lcd.h>
#include <stdio.h>

sbit at P3_2 timerbutton;
sbit at P2_0 LED0;
sbit at P2_1 LED1;
sfr at P2 LED;

unsigned long getmillis(void);
void initTimer(void);
void interiell_seriell(void);


unsigned long ms;
unsigned long ausschalten;
char buffer[20];


typedef struct {

    unsigned int sekunden;
    unsigned int minuten;
    unsigned int stunden;

}uhr;

uhr u;

void main (void) 
{
  
    u.sekunden =0;
    u.minuten = 0;
    u.stunden = 0;

    initTimer();
    initlcd();
    interiell_seriell();
    while(1)
    {
        if(timerbutton)
        {
         LED0=1;
         ausschalten = getmillis() + 10000;
        }
    
        if(getmillis() == ausschalten)
        {
            LED0 =0;
        }
       
           
    }
}




void initTimer(void)
{

TMOD = 0x11; //timerspezifikation auswaehlen 10001
ET0 = 1;    //
EA=1; //interrupt
TR0 =1;
LED = 0b00000000;

}



unsigned long getmillis(void)
{
    unsigned long temp;
    EA=0; //interrupt stoppen damit uns beim low oder highbyte reinschieben hier nichts passiert
    temp = ms;
    EA=1;

    return temp;
}

void Timer0_isr(void) interrupt 1
{
    TL0 = (65536-50000)%256; //high & low byte setzen
    TH0 = (65536-50000)/256;
    ms++; //20 inkrementiert ist 1s
    
    if(ms % 20 == 0){
        
    u.sekunden++;
    
    sprintf(buffer,"%d", u.sekunden);
    textlcd(buffer,1);
    }
}

void interiell_seriell(void)
{
PCON = PCON | 0x80;//PCON CPU-Register SMOD 1 = doppelte Baudtrate für serielle Schnittestelle | SMOD0 | - | POF | GF1 | GF0 | PD | IDL
BDRCON = 0x1F;
BRL = 217;
SCON = 0x52; // 8bit uart Empfang TI setzen
ES = 0; //no serial input
}
