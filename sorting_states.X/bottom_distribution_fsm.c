/*
 * File:   bottom_distribution_fsm.c
 * Author: ouutsuyuki
 *
 * Created on February 25, 2017, 4:25 PM
 */


#include <xc.h>

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
    
    if(SD1 ==1){        //If finished detection
        bottomDistributionState = bottom_distribution_move
    }else{
        //Do Nothing
    }
    
    //Update state
    bottomDistributionState = bottom_distribution_move;
    return;
}

void bottom_distribution_move(void){
    /*This function either move or don't move base on the sorting result*/
    
    if(labeled == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
                            //No label
        /*Code for moving the door*/
        //labeled = 0;       //Do NOT reset the global variable
    }else{
        /*Do nothing, the door doesn't move */
    }
    
    //Update state information
    bottomDistributionState = bottom_distribution_restore;
    return;
}

void bottom_distribution_restore(void){
    /*go back to the initial position*/
    
    if(top_move == 1){      //From the result in bottom_rocker_fsm,  Note the timing issue, receive the right signal
        /*Code for moving BACK the door*/
        bottom_move = 0;       //Reset the global variable HERE
    }else{
        /*Do nothing, the door didn't move */
    }
    
    //Update state information
    bottomDistributionState = bottom_distribution_idle;    
    return;
}