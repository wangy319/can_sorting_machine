//
//  IR_sensor.c
//

//http://www.rakeshmondal.info/IR-object-detection


#include <stdio.h>
//http://www.rakeshmondal.info/IR-Sensor-Interface-pic18f4550-input
/*
 * File:   infraredinput.c
 * Author: ron
 * December 10, 2012, 1:21 PM
 */
#include <p18f4550.h>           // Include Header for PIC18F4550

#define switch1  PORTAbits.RA0  // Switch on RA0

#define led1    LATDbits.LATD7     // led1
#define led2    LATDbits.LATD6    // led2

#define led3    LATBbits.LATB0   // led3
#define led4    LATBbits.LATB1    // led4
#define led5    LATBbits.LATB2    // led5

void main (void)

{
    
    /* If you want your microcontroller to work at  1MHZ then comment the three lines below */
    
    OSCCONbits.IRCF0 = 1 ;               // set internal clock to 8 MHz
    OSCCONbits.IRCF1 = 1;                //  For Avoiding switch debouncing problem
    OSCCONbits.IRCF2= 1;                 //
    
    /* Input output settings*/
    
    TRISAbits.TRISA0 = 1;                  //   RA0 Input for taking input from IR sensor
    
    TRISDbits.TRISD7 = 0;                  // Port D pins output
    TRISDbits.TRISD6 = 0;
    
    TRISBbits.TRISB0 = 0;                  // Port B pins Output
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    
    CMCON = 0x07;           // Disable Comparator
    
    ADCON1bits.PCFG0 = 1;          // These 4 settings below determines the analog or digital input
    ADCON1bits.PCFG1 = 1;          // In our case we are making all the pins digital
    ADCON1bits.PCFG2 = 1;         // by setting them as 1111
    ADCON1bits.PCFG3 = 1;         // Check with the datasheet for a nice desc of these bits and config.
    
    ADCON0bits.ADON = 0;  //  Disabled ADC
    
    while(1)
    {   //Forever Loop
        if(switch1 == 1)    //   On reading IR sensor value ON
        {    //Turn led ON
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 1;
            led5 = 1;              }
        else if ( switch1 == 0) // On reading IR Sensor Value OFF
        {   //Turn led off
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 0;
            led5 = 0;              }
        else {    }
        
    }   //End While loop --forever
}

/* THE END */
