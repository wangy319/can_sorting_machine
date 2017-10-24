/*
 * File:   top_rocker_fsm.c
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


void (*topRockerState)(void); 

void top_rocker_initial(void) {
    //Put it outside of the running loop
    //to initialize the rocker
    topRockerState = top_rocker_idle;
    
    return;
}


void top_rocker_idle(void){
    //Check if detected

    initLCD();
    if(PORTCbits.RC0 == 1){
        topRockerState = top_rocker_idle;
        fsm1 ++;
        
    }else{
        topRockerState = solenoids_out;
        fsm1 = 0;       //Restart counter  
    }
    return;
}

void solenoids_out(void){
    //release solenoid for a few ms //depends on testing result
    pop_out();
    //Update state
    topRockerState = solenoids_back;
                
    //Set a flag(global) for Finishing, to start the distribution motor    
    start_top_distribution = 1;
    
    return;
}

void solenoids_back(void){    
    
    tabed = PORTCbits.RC1;          //global variable to indicate if it has pull tab
    						//in case switch 3 changes really fast
    if(tabed){         //PORTCbits.RC1 = 1 means There IS current -> tab
        top_move = 1;          //Needs to move, top_move is a global variable
        
        pop_can_tab++;
        
    }else{
        
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("TOP no Tab"); 
        __delay_1s();
        */
        pop_can++;
        top_move = 0;
    }       
    
    //set solenoid back in position
    go_back();
    
    //Update state
    topRockerState = top_rocker_release;
    
    
    return;
}


void top_rocker_release(void){
   
    //Move to release the can, for a few ms, based on the testing result
    top_servo_rightTilt();
    top_servo_rightTilt();
    __delay_ms(300);
  
    //Update state
    topRockerState = top_rocker_restore;
   
    return;
}

void top_rocker_restore(void){
    
    //Move to the initial position, for a few ms
    top_servo_leftTilt();              //might be able to use the code for top_servo_init again
    //__delay_ms(50);
                    //Might need to call the init function to go back to the initial position
    
    //Update state
    topRockerState = top_rocker_idle;
    
    return;
}

