/*
 * File:   solenoid.c
 * Author: ouutsuyuki
 *
 * Created on February 24, 2017, 6:25 PM
 */


#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"
#include "operation.h"
#include "global.h"
#include "top_rocker_fsm.h"
#include "top_distribution_fsm.h"
#include "solenoids.h"
#include "motors.h"
#include "bottom_distribution_fsm.h"
#include "bottom_rocker_fsm.h"
#include "servo.h"


/*RC0 Controls both solenoids*/

void pop_out(void){    
    
    LATDbits.LATD0 = 0;         //Pop out
    __delay_ms(1000);            //1 seconds delay, will be adjusted
    return;
}

void go_back(void){
    
    LATDbits.LATD0 = 1;         //Go back
    __delay_ms(1000);            //1 seconds delay, will be adjusted
    return;
}