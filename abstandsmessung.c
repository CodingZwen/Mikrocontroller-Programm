#include <c51rx2.h>
#include <lcd.h>
#include <stdio.h>
#include <adda.h>

#define MV

sfr at P2 LEDs;
sbit at P2_7 LED7;


/*

temp = m * digitalwert + b ;

*/

//code lässt variable im programmspeicher(eprom) und nicht im ram
volatile unsigned int counter=0;
unsigned char buffer[20];
code unsigned char seg7Code [] = {0x7e,0x12,0xbc,0xd2,0xe6,0xee,
0xfe,0xf6,0xfb,0xcf};

void printlcd(const  char *str,int numbertoprint);
void initTimer(void);
void p (char ausgabe);
unsigned char getNumber(unsigned char voltage);
void loeschenlcd();
void tempmeasure();
void initall(void);
void ms();
void delay(unsigned ms);
void measure(unsigned char  spannung);
int getspannung(int ADWert,bit mv);


void main(void)
{
        unsigned char ADWert ;
        initall();
        LEDs = 0b10101010;   

        while(1)
        {
        ADWert = ain(1);
        measure(ADWert);      
        }
    

}



void measure(unsigned char ADWert)
{
   unsigned int Abstand;

        if(ADWert > 153)
         {
        sprintf(buffer,"Zu Nah",Abstand);
    
    
         }
        //abstand bis 200 mm: ml = -100/48 b1 = 344
        else if(ADWert > 117)
        {
           Abstand =  153-ADWert * 100 / 48;
        } //abstand bis 300mm:
        else if(ADWert > 69)
        {//          b     x        (   m    )
           Abstand = 344-ADWert *  100 / 23;
        }
        else if(ADWert > 46)
        {//          b     x        (   m    )
           Abstand = 500-ADWert *  100 / 23;
        }
        else if(ADWert > 38)
        {
           Abstand = 875-ADWert * 100 / 8;
        }else {
            textlcd("Abstand > 400mm   ",1);
        }
        delay(1000);
    
    
     #ifdef MV
            
        sprintf(buffer,"Abstand %3d mm",Abstand);
        textlcd(buffer,1);
        sprintf(buffer,"Spannung: %d,%03d mV V",getspannung(ADWert,1)/1000,getspannung(ADWert,1)%1000);
        textlcd(buffer,2);
    
        #endif

}


void printlcd(const char *eingabe,int number)
{

   unsigned char buffer[30];
   sprintf(buffer,"Ausgabe: %s  : %d",eingabe,number);
   textlcd(buffer,1);

}

int  getspannung(int ADWert, bit mv)
{

if(!mv)
return ADWert * 5 / 256;
else 
    return (int) ((long)ADWert * 5000 / 256); // in mv
    
}


void timer_isr(void) interrupt 1
{
TL0 = (65535 - 50000) % 256;
TH0 = (65535 - 50000) / 256;

counter++;

}

unsigned char getNumber(unsigned char voltage)
{

if(voltage >51 && voltage <=102)
    return 0x1;
else if(voltage >102&& voltage <=153)
    return 0x2;
else if(voltage >153&& voltage <=203)
    return 0x3;
else if(voltage >203&& voltage <=255)
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
EA = 1;

LED7 = 0;
LEDs = 0;

}



void initall(void)
{

initlcd();
loeschenlcd();
initTimer();

   
}


void ms()
{

int k;

for(k = 125; k >0; k--){;}

}

void delay(unsigned int count)
{
int k;

for(k=0;k<count;k++){ms();}

}


void tempmeasure()
{
    
unsigned char digitalwert;
int temp;
digitalwert = ain(0);
temp = digitalwert * 40 / 96 - 29;
sprintf(buffer,"temp = %3d Grad", temp);
textlcd(buffer,1);
delay(1000);

#ifdef AUSWAHLGERADE
    
digitalwert =ain(0);


    #ifdef floatrechnen
    
    float ftemp = digitalwert*0.417-29.2;
    sprintf(buffer,"temp = %3f Grad", ftemp);

    #endif
    
    
#endif 


}



//ET0 = 1 // interrupt timer
//EX0 = 1 //interrupt 
