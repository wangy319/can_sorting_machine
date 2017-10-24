#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "macroS.h"

#define servo = PORTBbit.RB3


void neutral() //0 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATB = 0b00001000;
    __delay_us(1550);
    LATB = 0b00000000;
    __delay_us(17800);
  }
}

void rightTilt()
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATB = 0b00001000;
    __delay_ms(2);
    LATB = 0b00000000;
    __delay_ms(18);
  }
}

void leftTilt()
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATB = 0b00001000;
    __delay_us(1200);
    LATB = 0b00000000;
    __delay_us(17800);
  }
}

void main()
{
  TRISA = 0xFF;
  TRISB = 0x00; // PORTB as Ouput Port
  TRISC = 0x00;
  TRISD = 0x00;
  TRISE = 0x00;

  LATA = 0x00;
  LATB = 0x00;
  LATC = 0x00;
  LATD = 0x00;
  LATE = 0x00;

  ADCON0 = 0x00;
  ADCON1 = 0xFF;

  nRBPU = 0;


  do
  {
    rightTilt(); //90 Degree
    __delay_ms(500);
    neutral(); //0 Degree
    __delay_ms(500);
    leftTilt(); //180 Degree
    __delay_ms(500);
    neutral(); //0 Degree
    __delay_ms(500);
  }while(1);
}
