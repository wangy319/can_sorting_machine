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

/*top rocker motor*/
void top_rocker_motor_cw(void){
    
    //To turn motor in one direction
    LATAbits.LATA0 = 0;
    LATAbits.LATA3 = 1;   
    __delay_ms(500);    
    
    //Stop
    LATAbits.LATA0 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}

void top_rocker_motor_ccw(void){
    
    int j;
    for(j=0;j<=5;j++){
        //To turn motor in the other direction
        LATAbits.LATA0 = 1;
        LATAbits.LATA3 = 0;
        __delay_ms(85);   

        //Stop
        LATAbits.LATA0 = 0;
        LATAbits.LATA3 = 0;
        __delay_ms(10); 
    }
    LATAbits.LATA0 = 0;
    LATAbits.LATA3 = 0;
    
    
    return;
}


//Bottom Rocker motor
void bottom_rocker_motor_cw(void){
    
    //To turn motor in one direction
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 1;   
    __delay_ms(500);    
    
    //Stop
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    return;
}

void bottom_rocker_motor_ccw(void){
    int k;
    for(k=0;k<=5;k++){
        //To turn motor in the other direction
        LATBbits.LATB2 = 1;
        LATBbits.LATB3 = 0;
        __delay_ms(85);   

        //Stop
        LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 0;
        __delay_ms(10); 
    }
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    
    return;
}

//Top distribution motor
void top_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 0;
    __delay_ms(500);    //0.2 seconds delay
    
    //Stop
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

void top_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 1;
    __delay_ms(500);    //0.2 seconds delay
   
    //Stop
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

//Bottom distribution motor
void bottom_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 0;
    LATBbits.LATB0 = 1; 
    __delay_ms(500);    //0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATBbits.LATB0 = 0;
    
    return;
}

void bottom_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATDbits.LATD1 = 1;
    LATBbits.LATB0 = 0;
    __delay_ms(500);    //zgbg0.2 seconds delay
    
    //Stop
    LATDbits.LATD1 = 0;
    LATBbits.LATB0 = 0;
    
    return;
}
