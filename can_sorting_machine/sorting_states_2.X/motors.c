/*
 * File:   DC_motors.c
 * Author: ouutsuyuki
 *
 * Created on February 24, 2017, 6:01 PM
 */

//Reference: https://electrosome.com/dc-motor-l293d-pic-microcontroller/


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


//Top distribution motor
void top_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC7 = 1;
    LATCbits.LATC6 = 0;
    __delay_ms(300);    //0.1 seconds delay
    
    //Stop
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

void top_distribution_motor_ccw2(void){
    
    //To turn motor in the other direction
    LATCbits.LATC7 = 1;
    LATCbits.LATC6 = 0;
    __delay_ms(200);    //0.1 seconds delay
    
    //Stop
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

void top_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 1;
    __delay_ms(300);    //0.2 seconds delay
   
    //Stop
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

void top_distribution_motor_cw2(void){
    
    //To turn motor in the other direction
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 1;
    __delay_ms(200);    //0.1 seconds delay
   
    //Stop
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}


//Bottom distribution motor
void bottom_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 1; 
    __delay_ms(300);    //0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}

void bottom_distribution_motor_cw2(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 1; 
    __delay_ms(200);    //0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}

void bottom_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 1;
    LATAbits.LATA3 = 0;
    __delay_ms(320);    //0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}

void bottom_distribution_motor_ccw2(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 1;
    LATAbits.LATA3 = 0;
    __delay_ms(210);    //0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}