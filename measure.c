
/* Ampelsteuerungen
* 2BKI21 INFP
* Autor: irmin Strazimiri
* Datum: 3.12.19
*/
#include <stdio.h>
#include <c51rx2.h>
#include <lcd.h>


bit ShowTime, merker;
unsigned char zustand ;
unsigned char sekunde= 0, minute = 0 , stunde =0,tag =0, monat= 0, jahr =0 , zaehler = 0;
unsigned long zeit;
unsigned int ueberlaeufe, zeit1;
// ****************************************
// Funktionsprototypen
// ****************************************
void delay1ms(void) ;
void delay(unsigned int Millisekunden);
void init_seriell(void);

// ****************************************
// Hauptprogramm
// ****************************************
void main (void)
{
char buffer [20];
initlcd();
init_seriell();
ShowTime = 1;
TMOD = 0b00010001;
//Frequenz mit timmer
TL1=(65536-50000)%256; // Anfangswert
TH1=(65536-50000)/256;


// Uhrzeit stellen

while(1)
{
if(P3_3 && merker == 0)
{
merker=1;
TR1=1; // wieso Timer 1 gestartet??
}
else if(P3_3==0 && merker==1)
{
TR1=0;
zeit1=(256*TH1)+TL1;
//zeit =(65356L*ueberlaeufe)+zeit1; // Lüfter blockiert? Dann gibt es Überläufe...
TL1=TH1=0;
merker =0; // merker bit löschen

sprintf(buffer,"zeit:%5u %cs ", zeit1, 0xe4);
textlcd(buffer,1);
}
if(TF1==1) // Timer ist übergelaufen
{
TF1=0; // timer flag löschen
ueberlaeufe++;
}

}// ende der endlos schleife

}// ende der main


void init_seriell(void) {
PCON = PCON | 0x80;// SMOD1 = 1 setzen für doppelte Baudrate
BDRCON = 0x1F;
BRL = 217; // ergibt eine Baudrate von 9600 Bit/s
SCON = 0x52; // 8-Bit-UART, Empfang zulassen
ES = 0;
}

void delay1ms(void) {
unsigned int k;
for( k=125; k!=0; k--) {}
}

void delay(unsigned int Millisekunden) {
unsigned int k;
for(k=Millisekunden; k!=0; k--) {
delay1ms();
}
}
