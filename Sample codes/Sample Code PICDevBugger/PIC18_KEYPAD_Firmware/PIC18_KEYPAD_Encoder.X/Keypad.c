/*
 * File:   Keypad.c
 * Author: Michael Ding
 *
 * Created on July 28, 2016, 11:10 AM
 */


#include <xc.h>

//<editor-fold defaultstate="collapsed" desc=" CONFIG BITS ">

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_XT // Oscillator Selection bits (Internal oscillator, XT used by USB (INTXT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

//</editor-fold>

#define _XTAL_FREQ 1000000

int i;
unsigned int columnPressed = 0b00000000;
unsigned int rowPressed = 0b00000000;
unsigned int dataOut;

void delay_5ms(unsigned char n) { 
    while (n-- != 0) { 
        __delay_ms(5); 
    } 
}

char findKey(unsigned short b, unsigned short a)
{
   if(b == 0)
   {
      if(a == 0)
        return 0x0;
      else if(a == 1)
        return 0x1;
      else if(a == 2)
        return 0x2;
      else if(a == 3)
        return 0x3;
   }
   else if(b == 1)
   {
      if(a == 0)
         return 0x4;
      else if(a == 1)
         return 0x5;
      else if(a == 2)
         return 0x6;
      else if(a == 3)
         return 0x7;
   }
   else if(b == 2)
   {
      if(a == 0)
         return 0x8;
      else if(a == 1)
         return 0x9;
      else if(a == 2)
         return 0xA;
      else if(a == 3)
         return 0xB;
   }
   else if(b == 3)
   {
      if(a == 0)
         return 0xC;
      else if(a == 1)
         return 0xD;
      else if(a == 2)
         return 0xE;
      else if(a == 3)
         return 0xF;
   }
}


unsigned int readKeyboard(void)
{
   unsigned int i = 0;
   for(i=0;i<4;i++)
   {
       if(i == 0)
         PORTB = 0x10;
       else if(i == 1)
         PORTB = 0x20;
       else if(i == 2)
         PORTB = 0x40;
       else if(i == 3)
         PORTB = 0x80;
         
       if(PORTBbits.RB0)
          return findKey(i,0);
       if(PORTBbits.RB1)
          return findKey(i,1);
       if(PORTBbits.RB2)
          return findKey(i,2);
       if(PORTBbits.RB3)
          return findKey(i,3);
   }
   return 0xF0;
}

void main(void) {
    // Disable all interrupts
    INTCONbits.GIE = 0;
    RCONbits.IPEN = 0;
   
    // Set port B I/O Mode
    // RB7-RB4 output, RB3-RB0 input
    TRISB = 0b00001111;
   
    // Set LAT of all pins on port B to output high
    LATB = 0xFF;
    
    // Set ADCON for digital input on all pins
    ADCON1 = 0x0F;
    
    // Tristate output on port A except pin 4 
    TRISA = 0b11011111;
    
    
   
    while(1){
        if (PORTAbits.RA4){
            // IF RA4 is high, keypad disabled, set all data pins to tristate
            TRISA = 0xFF;
        } else {
            TRISA = 0b11011111;
            dataOut = readKeyboard();

            // Check if a key push is detected
            if (dataOut != 0xF0){
            // Debounce switch press, pull data avaliable line high if key press valid
                delay_5ms(4);
                if (dataOut == readKeyboard()){
                // Check keyboard again, if same key is read, keypress is valid
                    LATA = dataOut & 0b00001111;
                    TRISA = 0b11010000;
                    while (dataOut == readKeyboard()){
                    // HOLD data avaliable pin high while key is pressed
                        LATAbits.LATA5 = 1;
                        delay_5ms(2);
                    }
                }
            }
            // No key press, set data output to tristate, and Data available to low.
            LATAbits.LATA5 = 0;
            TRISA = 0b11011111;
            delay_5ms(4);
        }

    }
}