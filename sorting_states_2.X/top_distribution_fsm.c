/*
 * File:   top_distribution_fsm.c
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
void (*topDistributionState)(void);

void top_distribution_initial(void){
    //Set state
    topDistributionState = top_distribution_idle;
    return;
}

void top_distribution_idle(void){
    
    //Update state
    if(start_top_distribution==1){        //If finished detection
        topDistributionState = top_distribution_prepare;
        start_top_distribution = 0;      //Reset
    }else{
        topDistributionState = top_distribution_idle;   //Don't change
    }
    
    return;
}

void top_distribution_prepare(void){
    //Prepare the motion of the door
    
    if(top_move == 1){      //From the result in top_rocker_fsm,  Note the timing issue, receive the right signal
        t_m = 1;
        top_distribution_motor_cw();        //Go half of the time
        
    }else{
        t_m = 0;
        top_distribution_motor_ccw();       //Go half of the time
         
    }
    
    //Update state information
    topDistributionState = top_distribution_move;
    return;
}


void top_distribution_move(void){
    //Code for moving the door to push the cans done
    //Back to the initial position
    
    if(t_m == 1){      //From the result in top_rocker_fsm,  Note the timing issue, receive the right signal
        top_distribution_motor_ccw();       //Go the whole time
        /*
        top_distribution_motor_ccw2(); 
        __delay_ms(30);
        top_distribution_motor_cw2(); 
        __delay_ms(200);
        */
        top_distribution_motor_ccw2(); 
        __delay_ms(30);
        top_distribution_motor_cw2();
        
    }else{
        top_distribution_motor_cw();        //Go the whole time
        /*
        top_distribution_motor_cw2();
        __delay_ms(30);
        top_distribution_motor_ccw2();
        __delay_ms(200);
        */
        top_distribution_motor_cw2();
        __delay_ms(30);
        top_distribution_motor_ccw2();
        
        
    }
    
    //Update state information
    topDistributionState = top_distribution_idle;
    return;
}
