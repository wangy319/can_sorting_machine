/*
 * File:   solenoid.c
 * Author: ouutsuyuki
 *
 * Created on February 24, 2017, 6:25 PM
 */


#include <xc.h>
#include "configBits.h"

void solenoid(void) {
    //RC0    
    LATCbits.LATC0 = 1;         //Go back
    __delay_ms(1000);            //1 seconds delay, will be adjusted
    
    LATCbits.LATC0 = 0;         //Pop out
    __delay_ms(2000);            //2 seconds delay, will be adjusted

    LATCbits.LATC0 = 1;         //Go back
    return;
}