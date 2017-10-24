#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "macros.h"
#include "lcd.h"
#include "I2C.h"


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

    while(1){
        if( PORTAbits.RA2 == 1){
            __lcd_home();
            initLCD();    
            printf("HIGH");     //Get rid of the printing and delay in actual program
            __delay_1s();
        }else{
            __lcd_home();
            initLCD();    
            printf("LOW");     //Get rid of the printing and delay in actual program
            __delay_1s();
        }
        return;
    }
}