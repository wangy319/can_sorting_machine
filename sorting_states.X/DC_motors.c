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

/*top rocker motor*/
void top_rocker_motor_cw(void){
    
    //To turn motor in one direction
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 1;   
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

void top_rocker_motor_ccw(void){
    
    //To turn motor in the other direction
    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 0;
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

/*
//Bottom Rocker motor
void bottom_rocker_motor_cw(void){
    
    //To turn motor in one direction
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 1;   
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

void bottom_rocker_motor_ccw(void){
    
    //To turn motor in the other direction
    LATBbits.LATB2 = 1;
    LATBbits.LATB3 = 0;
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

//Top distribution motor
void top_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 0;
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

void top_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 1;
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

//Bottom distribution motor
void bottom_distribution_motor_cw(void){
    
    //To turn motor in the other direction
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 1; 
    __delay_ms(1000);    //1 seconds delay
    
    return;
}

void bottom_distribution_motor_ccw(void){
    
    //To turn motor in the other direction
    LATEbits.LATE1 = 1;
    LATEbits.LATE2 = 0;
    __delay_ms(1000);    //1 seconds delay
    
    return;
}
*/
/*
void top_distribution_motor (void){
    //RC5 and RC6
    //Move in one direction for few ms -> Move back to default position
    do
    {
       //To turn motor in one direction
       LATCbits.LATC5 = 0;
       LATCbits.LATC6 = 1;   
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in the other direction
       LATCbits.LATC5 = 1;
       LATCbits.LATC6 = 0;
       __delay_ms(2000);    //2 seconds delay

       //Restore to stationary state
       LATCbits.LATC5 = 0;
       LATCbits.LATC6 = 0;
       __delay_ms(2000);    //2 seconds delay
   }while(1);
   
   return;
}

void bottom_distribution_motor (void){
    //RE1 and RE2    
    do
    {
       //To turn motor in one direction
       LATEbits.LATE1 = 0;
       LATEbits.LATE2 = 1;   
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in the other direction
       LATEbits.LATE1 = 1;
       LATEbits.LATE2 = 0;
       __delay_ms(2000);    //2 seconds delay

       //Restore to stationary state
       LATEbits.LATE1 = 0;
       LATEbits.LATE2 = 0;
       __delay_ms(2000);    //2 seconds delay 
    }while(1);
    
    return;
}
*/

/*
void top_rocker_motor (void){
    //RA0 and RA1
    //Stop -> Move in one direction, stop for a while for detection ->
    //move back -> Stop and wait for the next one    
    do
    {
       //Stop
       LATAbits.LATA0 = 0;
       LATAbits.LATA1 = 0;
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in one direction
       LATAbits.LATA0 = 0;
       LATAbits.LATA1 = 1;   
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in the other direction
       LATAbits.LATA0 = 1;
       LATAbits.LATA1 = 0;
       __delay_ms(2000);    //2 seconds delay

       //Stop
       LATAbits.LATA0 = 0;
       LATAbits.LATA1 = 0;
       __delay_ms(2000);    //2 seconds delay
       
   }while(1);
       
    return;
}


void bottom_rocker_motor(void){
    //RB2 and RB3
    return;
    do
    {
       //Stop
       LATBbits.LATB2 = 0;
       LATBbits.LATB3 = 0;
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in one direction
       LATBbits.LATB2 = 0;
       LATBbits.LATB3 = 1; 
       __delay_ms(2000);    //2 seconds delay

       //To turn motor in the other direction
       LATBbits.LATB2 = 1;
       LATBbits.LATB3 = 0;
       __delay_ms(2000);    //2 seconds delay

       //Stop
       LATBbits.LATB2 = 0;
       LATBbits.LATB3 = 0;
       __delay_ms(2000);    //2 seconds delay
       
   }while(1);    
}
*/

