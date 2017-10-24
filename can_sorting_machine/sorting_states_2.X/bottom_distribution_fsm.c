/*
 * File:   bottom_distribution_fsm.c
 * Author: ouutsuyuki
 *
 * Created on February 25, 2017, 4:25 PM
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


//Function Pointer 
void (*bottomDistributionState)(void);

void bottom_distribution_initial(void){
    //Initialization
    //Move the door to the initial position BY HAND!
    
    //Set state
    bottomDistributionState = bottom_distribution_idle;
    return;
}

void bottom_distribution_idle(void){
    
    if(start_bottom_distribution == 1){        //If finished detection
        bottomDistributionState = bottom_distribution_prepare;          //might need to put the prepare code here
        start_bottom_distribution = 0;      //Reset
    }else{
        bottomDistributionState = bottom_distribution_idle;             //Do Nothing
    }
    return;
}

void bottom_distribution_prepare(void){
    /*This function either move or don't move base on the sorting result*/
    
    if(bottom_move == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
                            //No label
        //Code for moving the door in one way
        b_m = 1;
        bottom_distribution_motor_cw();     
    }else{
        b_m = 0;
        //Moving the door in the other way
        bottom_distribution_motor_ccw();   
    }
    //Update state information
    bottomDistributionState = bottom_distribution_move;
    
    return;
}



void bottom_distribution_move(void){
        
    //Move and push done the can
    //Go back to the initial position
    
    if(b_m == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
        //Push the can into one side
        bottom_distribution_motor_ccw();        
        bottom_distribution_motor_ccw2();
        __delay_ms(30);
        bottom_distribution_motor_cw2();
        __delay_ms(200);
        bottom_distribution_motor_ccw2();
        __delay_ms(30);
        bottom_distribution_motor_cw2();
    }else{
        //Push the other way
        bottom_distribution_motor_cw();        
        bottom_distribution_motor_cw2();
        __delay_ms(30);
        bottom_distribution_motor_ccw2();
        __delay_ms(200);
        bottom_distribution_motor_cw2();
        __delay_ms(30);
        bottom_distribution_motor_ccw2();
    } 
    
    //Update state information
    bottomDistributionState = bottom_distribution_idle;    
    return;
}