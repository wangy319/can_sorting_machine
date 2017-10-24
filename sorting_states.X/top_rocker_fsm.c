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

void (*topRockerState)(void); 

void top_rocker_initial(void) {
    //Put it outside of the running loop
    //to initialize the rocker
    //Move the rocker by hand to the initial position to stop the can from moving(right)
    
    //Set state to idle state to initialize
    //(*topRockerState)(void); 
    
    
    //Test
    __lcd_home();
    initLCD();    
    printf("top rocker init");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    
    topRockerState = top_rocker_idle;
    //topRockerState = top_rocker_idle;
    
    return;
}

void top_rocker_idle(void){
    //Check if detected
    //PORTAbits.RA2 = 1(5V) when detected
    
    //Test
    __lcd_home();
    initLCD();    
    printf("rocker idle");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    
    
    if(! switch1){             //Not detected
        topRockerState = top_rocker_idle;      //Don't change state
    }else{                           //detected
        topRockerState = solenoids_out;
    }
    
    fsm1 ++;        //Update counter, if counter is greater than 100, means 
                    //there is no can arriving, then stop fsm operation
    return;
}

void solenoids_out(void){
    
    //Test
    __lcd_home();
    initLCD();    
    printf("solenoids out");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    //release solenoid for a few ms //depends on testing result
    pop_out();
    //Update state
    topRockerState = solenoids_back;
                
    return;
}

void solenoids_back(void){    
    
    //Test
    __lcd_home();
    initLCD();    
    printf("solenoids back");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    
    tabed = switch3;          //global variable to indicate if it has pull tab
    
    if(switch3){         //PORTCbits.RC1 = 1 means There IS current -> tab
        top_move = 1;          //Needs to move, top_move is a global variable
    }else{
        top_move = 0;
    }       
    
    //set solenoid back in position
    go_back();
    
    //Update state
    topRockerState = top_rocker_release;
    
    return;
}


void top_rocker_release(void){
    
    
    //Test
    __lcd_home();
    initLCD();    
    printf("rocker release");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    //Move to release the can, for a few ms, based on the testing result
    top_rocker_motor_ccw();
    
    //Might need delay here to give the cans time to move
    
    //Update state
    topRockerState = top_rocker_restore;
    
    //Set a flag(global) for Finishing, to start the distribution motor    
    start_top_distribution = 1;
    
    return;
}

void top_rocker_restore(void){
    
    //Test
    __lcd_home();
    initLCD();    
    printf("rocker restore");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    
    
    //Move to the initial position, for a few ms
    top_rocker_motor_cw();
    
    //Update state
    topRockerState = top_rocker_idle;
    
    return;
}

