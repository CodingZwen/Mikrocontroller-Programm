#include <c51rx2.h>
#include <lcd.h>
#include <stdio.h>
#include <adda.h>

sfr at P2 LEDs;
sbit at P2_7 LED7;

//code lässt variable im programmspeicher(eprom) und nicht im ram

code unsigned char seg7Code [] = {0x7e,0x12,0xbc,0xd2,0xe6,0xee,
0xfe,0xf6,0xfb,0xcf};

void printlcd(const  char *str,int numbertoprint);
void initTimer(void);
void p (char ausgabe);
unsigned char getNumber(unsigned char voltage);

void main(void)
{
    
 unsigned char ADWert;
initTimer();    
while(1)
    {
        ADWert = ain(0); //wir bekommen wert abhängig von spannung 0-5V -> 0-255
       
        LEDs =seg7Code[ getNumber(ADWert)];
        
        aout(ADWert); // analoge ausgabe über voltmeter Aout
        
    }

}






void printlcd(const char *eingabe,int number)
{

   unsigned char buffer[30];
   sprintf(buffer,"Ausgabe: %s  : %d",eingabe,number);
   textlcd(buffer,1);

}

void p (char number)
{
   unsigned char buffer[30];
   sprintf(buffer,"Ausgabe: %c",number);
   textlcd(buffer,1);

}

void timer_isr(void)
{
TL0 = (65535 - 50000) % 256;
TH0 = (65535 - 50000) / 256;



}

unsigned char getNumber(unsigned char voltage)
{

if(voltage >51 && voltage <=102)
    return 0x1;
if(voltage >102&& voltage <=153)
    return 0x2;
if(voltage >153&& voltage <=203)
    return 0x3;
if(voltage >203&& voltage <=255)
    return 0x4;
else
    return 0;


}


void initTimer(void)
{

//ET0 = 1;    //
//EA=1; //interrupt
TMOD = 0b00010001;
TR0 = 1;
ET0 = 1;
EA = 0;

LED7 = 0;
LEDs = 0;

}

void initall(void)
{

initlcd();
   loeschenlcd();
   
}

//ET0 = 1 // interrupt timer
//EX0 = 1 //interrupt 
