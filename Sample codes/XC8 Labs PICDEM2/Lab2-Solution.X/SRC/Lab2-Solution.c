#include <xc.h>

#define _XTAL_FREQ 4000000
void InitSystem(void);
int main(void)
{
    ANSELD = 0;
    OSCCONbits.IRCF = 0xD;  // for 1937 to run at 4 MHz
    InitSystem();
    while(1)
    {
        PORTB=0x0F;
        __delay_ms(197);    //  197 is max value for this function @ 4MHz
        __delay_ms(197);    //  197 is max value for this function @ 4MHz
        PORTB=0x00;
        __delay_ms(197);    //  197 is max value for this function @ 4MHz
        __delay_ms(197);    //  197 is max value for this function @ 4MHz
    }
}
void InitSystem(void)
{
    PORTB = 0X00;  //initialize PORTB register
    TRISB = 0XF0;  //set RB0-RB3 as outputs and RB4-RB7 as inputs
}
/********************************************************************************
|  CLASS:         Getting Started with MPLAB XC compilers
|  PROGRAM:       Lab2.c   
|  AUTHOR:        Mark Reynolds
|  DATE:          May 2013
|  DESCRIPTION:   Set configuration bits in code, check result in configuration
|                 bits window.
|  REQUIREMENTS:                   
| 
|  REVISION HISTORY:
|  Jan 2013       Mark Reynolds modified for XC8 v1.10
|  Dec 2012       Mark Reynolds Updated for XC16 v1.10
|  20 JAN 2008    Rob Ostapiuk
|                 First Draft
********************************************************************************/