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

//Function Pointer 
void (*topDistributionState)(void);


void top_distribution_initial(void){
    //Initialization
    //Move the door to the initial position BY HAND!
    
    //Set state
    topDistributionState = top_distribution_idle;
    return;
}

void top_distribution_idle(void){
    
    if(start_top_distribution ==1){        //If finished detection
        topDistributionState = top_distribution_move
    }else{
        //Do Nothing
    }
    
    //Update state
    topDistributionState = top_distribution_move;
    return;
}

void top_distribution_move(void){
    /*This function either move or don't move base on the sorting result*/
    
    if(top_move == 1){      //From the result in top_rocker_fsm,  Note the timing issue, receive the right signal
        /*Code for moving the door*/
        //top_move = 0;       //Do NOT reset the global variable
    }else{
        /*Do nothing, the door doesn't move */
    }
    
    //Update state information
    topDistributionState = top_distribution_restore;
    return;
}

void top_distribution_restore(void){
    /*go back to the initial position*/
    
    if(top_move == 1){      //From the result in top_rocker_fsm,  Note the timing issue, receive the right signal
        /*Code for moving BACK the door*/
        top_move = 0;       //Reset the global variable HERE
    }else{
        /*Do nothing, the door didn't move */
    }
    
    //Update state information
    topDistributionState = top_distribution_idle;    
    return;
}