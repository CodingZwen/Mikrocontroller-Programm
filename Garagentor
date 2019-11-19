
/*
"Automat" C Programm von Sven-Patrick Schulze
24.09.2019

************************************************************
*/


#include <stdio.h>
#include <c51rx2.h>


sfr at P2 LEDs;
sbit at P3_3 TA;
sbit at P3_2 TZ;
sbit at P1_7 SO; //schloss offen
sbit at P1_6 SS; //schloss schlossen

 void  delay1ms(void);
 void Garagentor(void);
 void close(void);
void showinput(unsigned int state);
void delay(unsigned int);

int Zustand;
int zaehler = 0;
unsigned char Ausgabe ='A';

enum {isOPEN,CLOSING,isCLOSED,OPENING};



void main (void) 
{
   Zustand = isCLOSED;


   LEDs = 0b111111111;

   while(1){
    
   Garagentor();
   delay(100);
   
 
   

   }
 


}




//enum  {isOPEN,CLOSING,isCLOSED,OPENING};




void Garagentor(void)
{

    switch(Zustand)
    {
    case isOPEN :  if(TZ) Zustand = CLOSING  ;break;    
        case CLOSING :  if(SS)Zustand = isCLOSED;break;
            case isCLOSED : if(TA)Zustand = OPENING;   break;
                case OPENING: if(SO)Zustand = isOPEN;break;
        default: Zustand = isCLOSED;break;
    
    
    }


showinput(Zustand);


}


void close(void)
{

    
    LEDs = 0b00000001;
    
 


    for( zaehler = 0; zaehler < 7;zaehler++)
   {

    delay(1000);

    LEDs <<=1;
    LEDs |=1;

   }



}


//
//enum  {isOPEN,CLOSING,isCLOSED,OPENING};




void showinput(unsigned int Zustand)
{



switch(Zustand)

{
case 0 : LEDs = 0b00000000;
case 1 : LEDs = 0b00000010;
case 2 : LEDs = 0b11111111;
case 3 : LEDs = 0b01010101;
default:break;    

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

    for(;k>0;k--);

}
