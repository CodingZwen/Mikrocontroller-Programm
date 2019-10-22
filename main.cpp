/* 2BKI21 INFP
 * Autor: Jan Freitag
 * Datum: 01.10.2019
 */
 
 

#include <c51rx2.h>
#include <stdio.h>
#include <lcd.h>
// ****************************************
sfr at P1 Schalter;     // 8 DIP-Schalter an P1
sfr at P2 Ampel;         // 8 LEDs am Port P2
sbit at P1_0 S0;
sbit at P1_1 S1;        // der 2.Schalter (einer!) an P1
sbit at P2_0 LED0;      // unterste LED an P2_0
sbit at P2_1 LED1;
sbit at P2_2 LED2;
sbit at P2_3 LED3;
sbit at P2_4 LED4;
sbit at P2_5 LED5;
sbit at P2_6 LED6;
sbit at P2_7 LED7;
sbit at P3_3 Ampeltaste;

// ****************************************
// Funktionsprototypen
// ****************************************
void delay1ms(void) ;
void delay(unsigned int Millisekunden);
void interiell_seriell(void);

// ****************************************
// Hauptprogramm
// ****************************************


#define PHASE1    0b10010100
#define PHASE2    0b11010100
#define PHASE3    0b00110100
#define PHASE4    0b01010100
#define PHASE5    0b10010100
#define PHASE6    0b10010110
#define PHASE7    0b10010001
#define PHASE8    0b10010010
#define PHASE9    0b10010100
#define PHASE10   0b10010100
#define TESTPHASE 0b11111111
#define WALKPHASE 0b10001100
#define MAXPHASES 10

unsigned char phasearray[MAXPHASES] = { 0b10010100,0b11010100,0b00110100,0b01010100,0b10010100,0b10010110,0b10010001,0b10010010,0b10010100,0b10010100 };


unsigned int count = 0;
bit fussgaengerbit = 0;


void TrafficLightLoop();
void Setup();

void main (void) 
{

    IT0=1;
    IE0=0;
    EX0 = 1;
    EA =1;
    
    while(1)   
    {
    TrafficLightLoop();
    }
     
 }


void Ex0_ESR() interrupt 0
{

IE0 = 0;
fussgaengerbit=1;
}

void Setup() //inits interrupt flags
{

    IT0=1;
    IE0=0;
    EX0 = 1;
    EA =1;
}


void TrafficLightLoop()
{
Ampel = phasearray[count % 10];


if((count % 10) ==0 && fussgaengerbit==1)
    {
        Ampel = WALKPHASE;
        fussgaengerbit=0;
    }else count++;

delay(500);

}

void delay1ms(void) 
{
    unsigned int k;
    for( k=125; k!=0; k--) {}
}

void delay(unsigned int Millisekunden) 
{
    unsigned int k;
    for(k=Millisekunden; k!=0; k--) 
        {
        delay1ms();
    }
}

void interiell_seriell(void)
{
PCON = PCON | 0x80;
BDRCON = 0x1F;
BRL = 217;
SCON = 0x52;
ES = 0;
}





   
 
  //old

/*


 delay(500);
		if (Bl_Taster == 1 && Merker == 0)
		{
			// Steigende Flanke erkannt 
			Merker = 1;
      
			LEDs++;
		}
		else
		{
			if (Bl_Taster == 1 && Merker == 1)
			{
				
			}
			else
			{
				if (Bl_Taster == 0 && Merker == 1)
				{
					// fallende Flanke erkannt 
					Merker = 0;
               LEDs--;
				}
				else
				{
					// Konstant 0-Pegel 
					;
				}
			}
*/
   








//  LEDs = LEDs << 1;      // Leds können einzeln hochgezählt werden


