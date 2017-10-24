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

//Function Pointer 
void (*bottomDistributionState)(void);


void bottom_distribution_initial(void){
    //Initialization
    //Move the door to the initial position BY HAND!
    
    /*
    //Test
        initLCD();
        __lcd_home();
        printf("Bottom init 2"); 
        __delay_1s();
    */
    
    //Set state
    bottomDistributionState = bottom_distribution_idle;
    return;
}

void bottom_distribution_idle(void){
    
   
    
    if(start_bottom_distribution ==1){        //If finished detection
        
       /*
        //Test
        initLCD();
        __lcd_home();
        printf("BOTTOM dis start"); 
        __delay_1s();
        */
        
        bottomDistributionState = bottom_distribution_prepare;
        start_bottom_distribution = 0;      //Reset
        
    }else{
        bottomDistributionState = bottom_distribution_idle;//Do Nothing
    }
    
    return;
}

void bottom_distribution_prepare(void){
    /*This function either move or don't move base on the sorting result*/
    
    if(bottom_move == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
                            //No label
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("B_CW"); 
        __delay_1s();
        */
        //Code for moving the door in one way
        bottom_distribution_motor_cw();
        
    }else{
    
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("B_CCW"); 
        __delay_1s();
        */
        
        //Moving the door in the other way
        bottom_distribution_motor_ccw();
        
    }
    
    //Update state information
    bottomDistributionState = bottom_distribution_move;
    
    return;
}

void bottom_distribution_move(void){
    
    /*
    //Test
        initLCD();
        __lcd_home();
        printf("Bottom restore 2"); 
        __delay_1s();
    */
        
    //Move and push done the can
    //Go back to the initial position
    
    if(bottom_move == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
        //Push the can into one side
        bottom_distribution_motor_ccw();
        
    }else{
        //Push the other way
        bottom_distribution_motor_cw();
    }
        
    //Update state information
    bottomDistributionState = bottom_distribution_idle;    
    return;
}