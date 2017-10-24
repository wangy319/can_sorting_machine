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

void (*topRockerState)(void); 

void top_rocker_initial(void) {
    //Put it outside of the running loop
    //to initialize the rocker
    //Move the rocker by hand to the initial position to stop the can from moving(right)
    
    /*
    //Test
    __lcd_home();
    initLCD();    
    printf("top init 1");     //Get rid of the printing and delay in actual program
    __delay_1s();
    */
    
    topRockerState = top_rocker_idle;
    
    return;
}


void top_rocker_idle(void){
    //Check if detected
    //PORTAbits.RA0 = 1(5V) when detected
    
    //Test
    __lcd_home();
    initLCD();    
    printf("top idle");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    
    initLCD();
    if( PORTAbits.RA0 == 1){  //No can detected
        
        fsm1++;  

        __lcd_home();
        printf("TOP No Can"); 
        __delay_1s();
                
    }else{       //Not Conductive -> pop can without pull tag 
                //Call detecting function
        __lcd_home();
        printf("TOP Detected");  
        __delay_1s();
    
        //Update State
        topRockerState = solenoids_out;
        fsm1 = 0;       //Restart counter
    }
    
    return;
}

void solenoids_out(void){
    
    /*
    //Test
    __lcd_home();
    initLCD();    
    printf("solenoids out");     //Get rid of the printing and delay in actual program
    __delay_1s();
    */
    
    //release solenoid for a few ms //depends on testing result
    pop_out();
    //Update state
    topRockerState = solenoids_back;
                
    return;
}

void solenoids_back(void){    
    
    /*
    //Test
    __lcd_home();
    initLCD();    
    printf("solenoids back");     //Get rid of the printing and delay in actual program
    __delay_1s();
    */
    
    tabed = PORTCbits.RC1;          //global variable to indicate if it has pull tab
    						//in case switch 3 changes really fast
    if(tabed){         //PORTCbits.RC1 = 1 means There IS current -> tab
        top_move = 1;          //Needs to move, top_move is a global variable
        
        pop_can_tab++;
        
        //Test
        initLCD();
        __lcd_home();
        printf("TOP has Tab"); 
        __delay_1s();
        
    }else{
        
        
        //Test
        initLCD();
        __lcd_home();
        printf("TOP no Tab"); 
        __delay_1s();
        
        pop_can++;
        top_move = 0;
    }       
    
    //set solenoid back in position
    go_back();
    
    /*
    //Test
        initLCD();
        __lcd_home();
        printf("Solenoids Back"); 
        __delay_1s();
    */
    
    //Update state
    topRockerState = top_rocker_release;
    
    return;
}


void top_rocker_release(void){
    
    
    //Test
    __lcd_home();
    initLCD();    
    printf("top release");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    //Move to release the can, for a few ms, based on the testing result
    top_rocker_motor_ccw();
    
    //Might need delay here to give the cans time to move
    
    //Update state
    topRockerState = top_rocker_restore;
    
    //Set a flag(global) for Finishing, to start the distribution motor    
    start_top_distribution = 1;
    
    //Test
        initLCD();
        __lcd_home();
        printf("TOP pass on"); 
        __delay_1s();
    
    return;
}

void top_rocker_restore(void){
    
    //Test
    __lcd_home();
    initLCD();    
    printf("top restore 1");     //Get rid of the printing and delay in actual program
    __delay_1s();
       
    //Move to the initial position, for a few ms
    top_rocker_motor_cw();
    
    //Update state
    topRockerState = top_rocker_idle;
    
    return;
}

