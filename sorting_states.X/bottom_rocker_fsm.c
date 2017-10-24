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
    if(! bottom_detected){             //top_detected        
        bottomRockerState = bottom_rocker_idle;      //Don't change state
                
    }else{
        bottomRockerState = bottom_rocker_release;
        //Read electrical signal, store in global variable: labeled
        //labeled = detected_pin_value          //If no label -> conductive -> pin = 1, else, pin = 0
    }
    return;
}

void bottom_rocker_release(void){
    //Move to release the can, for a few ms
    
    //Update state
    bottomRockerState = bottom_rocker_restore;
    
    
    return;
}

void bottom_rocker_restore(void){
    //Move to the initial position, for a few ms
    
    //Update state
    bottomRockerState = bottom_rocker_idle;
    //Set a flag(global) for Finishing, to start the distribution motor
    
    //SD2 = 1;
    return;
}

