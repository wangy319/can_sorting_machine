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
    
    
    //Test
        __lcd_home();
        initLCD();    
        printf("top cw");     //Get rid of the printing and delay in actual program
        __delay_1s();
    
    //To turn motor in one direction
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 1;   
    __delay_ms(500);    
    
    //Stop
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
    
    return;
}

void top_rocker_motor_ccw(void){
    
    
    //To turn motor in the other direction
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 0;
    __delay_ms(500);   
    
    //Stop
    LATAbits.LATA2 = 0;
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
    
    //To turn motor in the other direction
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 0;
    __delay_ms(500);   
    
    //Stop
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;
    
    return;
}

//Top distribution motor
void top_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 0;
    __delay_ms(200);    //0.2 seconds delay
    
    //Stop
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

void top_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 1;
    __delay_ms(200);    //0.2 seconds delay
   
    //Stop
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    
    return;
}

//Bottom distribution motor
void bottom_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 1; 
    __delay_ms(200);    //0.2 seconds delay
    
    //Stop
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    
    return;
}

void bottom_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATEbits.LATE1 = 1;
    LATEbits.LATE2 = 0;
    __delay_ms(200);    //0.2 seconds delay
    
    //Stop
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    
    return;
}
