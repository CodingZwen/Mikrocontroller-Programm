#include <c51rx2.h>
#include <lcd.h>
#include <stdio.h>
#include <i2c_basis.h>

void checkack();

//pcf8574a adressen
//          0111000
//schreiben 01110000
//lesen     01110001

#define I2C_LED_W 0x70 //01110000 
#define I2C_LED_R 0x71

#define I2C_DIP_W 0b01000000
#define I2C_DIP_R 0b01000001

#define I2C_TEMP_R 0b10011111

#define WRITEWITHDIP


sfr at P2 leds;
sfr at P1 dipschalter;

void delay(unsigned int );
void ms();

void main(void)
{
    bit sek = 0;
    char buffer[20];
    signed char dipdata;
    initlcd();
    i2c_init();

    leds = 0b0101010101;


    while(1)
    {
    
    //dip lesen 
    i2c_start(); //start communicate
    i2c_write(I2C_DIP_R); // 
    dipdata = i2c_read(NACK); //NACK einmal lesen dann fertig -> ACK:
    i2c_stop();
    leds = dipdata;
    

    i2c_start(); //start communicate
    i2c_write(I2C_LED_W); // 
    i2c_write(~P1);
    I2c_stop();
    
    
    //temp sensor lesen 
    
    //0b10011111
    i2c_start(); //start communicate
    i2c_write(I2C_TEMP_R); // 
    dipdata = i2c_read(NACK); //NACK einmal lesen dann fertig -> ACK:
    i2c_stop();
    
    sprintf(buffer,"tmeperatur: %3i mm",dipdata);
    textlcd(buffer,1);
     delay(100);

    
    
    }
       
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


void checkack()
{

   if(i2c_write(I2C_LED_W) == ACK); //ACK ist 0,
}

/*
void lcdprint()
{
sprintf(buffer,"Abstand %3d mm",Abstand);
        textlcd(buffer,1);
        sprintf(buffer,"Spannung: %d,%03d mV V",getspannung(ADWert,1)/1000,getspannung(ADWert,1)%1000);
        textlcd(buffer,2)

;}
*/


//ET0 = 1 // interrupt timer
//EX0 = 1 //interrupt 
