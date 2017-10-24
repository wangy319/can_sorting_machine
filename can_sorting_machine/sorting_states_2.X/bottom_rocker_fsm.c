/*
 * File:   bottom_rocker_fsm.c
 * Author: ouutsuyuki
 *
 * Created on February 25, 2017, 3:32 PM
 */


/*In the main loop call function pointer, then base on the current pointing state, 
 * the pointed function will be called and run.
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


void (*bottomRockerState)(void); 

void bottom_rocker_initial(void) {
    //Put it outside of the main loop
    //to initialize the rocker
    //Move the rocker by hand to the right position to stop the can from moving
    
    //Set state to idle state to initialize
    bottomRockerState = bottom_rocker_idle;
 
    return;
}

void bottom_rocker_idle(void){
    
    
    //Check if detected
    //PORTAbits.RA1 = 0(5V) when detected
     
    if( PORTEbits.RE1 == 1){  //No can detected    
        fsm2++;  
            
    }else{       //Not Conductive -> pop can without pull tag 
                //Call detecting function   
        
        fsm2 = 0;           //Count from the beginning
        
        //Code
        labeled = 0;
        ei();         //Enable Interrupt for tin conductor    RB0
        
        int o;
        for(o = 0; o<20; o++){
            __delay_ms(5);
            //Conductor
            labeled = labeled || PORTCbits.RC2; 
            //Color Sensor
            //labeled = labeled || PORTBbits.RB0;
        }
        //Set a flag(global) for Finishing, to start the distribution process    
        start_bottom_distribution = 1;
        
        //Move to the center
        bottom_servo_rightTilt();
        for(o = 0; o<20; o++){
            __delay_ms(5);
            labeled = labeled || PORTCbits.RC2; 
            //labeled = labeled || PORTBbits.RB0;
        }
        //Update State
        bottomRockerState = bottom_rocker_detect;        
        }
    return;
}

void bottom_rocker_detect(void){
        
    labeled = labeled || PORTCbits.RC2;        //Bottom conductivity
    di(); 
    if(labeled){                //Used in bottom_distribution  
            bottom_move = 1;        //With label
            tin_can_label++;                
    }else{
            bottom_move = 0;        //without label
            tin_can++;     
    }
    bottomRockerState = bottom_rocker_release;
    return;
}

void bottom_rocker_release(void){
      
    //Move to release the can, for a few ms
    bottom_servo_rightTilt();
    __delay_ms(300);
    bottom_servo_rightTilt();
    
    bottomRockerState = bottom_rocker_restore;
    
    __delay_ms(500); 
    
    return;
}

void bottom_rocker_restore(void){
       
    //Move to the initial position, for a few ms
    bottom_servo_leftTilt();              //might be able to use the code for top_servo_init again
    //Update state
    bottomRockerState = bottom_rocker_idle;
    return;
}

