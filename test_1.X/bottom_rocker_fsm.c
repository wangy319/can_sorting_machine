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

void (*bottomRockerState)(void); 

void bottom_rocker_initial(void) {
    //Put it outside of the main loop
    //to initialize the rocker
    //Move the rocker by hand to the right position to stop the can from moving
    
    //Test
    __lcd_home();
    initLCD();    
    printf("bottom init 1");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    //Set state to idle state to initialize
    bottomRockerState = bottom_rocker_idle;
    
    return;
}

void bottom_rocker_idle(void){
    
    
    //Check if detected
    //PORTAbits.RA1 = 0(5V) when detected
    
    //Test
    __lcd_home();
    initLCD();    
    printf("bottom idle");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    if( PORTAbits.RA1 == 1){  //No can detected    
        fsm2++;  
    
        //Test
        __lcd_home();
        initLCD();
        printf("Bottom No Can"); 
        __delay_1s();
                
    }else{       //Not Conductive -> pop can without pull tag 
                //Call detecting function
        
        //Test
        __lcd_home();
        initLCD();
        printf("bottom Detected");  
        __delay_1s();
      
        
        fsm2 = 0;           //Count from the beginning
        //Code
        labeled = PORTCbits.RC2;        //Bottom conductivity
        
        if(labeled){                //Used in bottom_distribution  
            bottom_move = 1;        //With label
            
            tin_can_label++;
            
            //Test
            __lcd_home();
            initLCD();
            printf("labeled");  
            __delay_1s();
        
            
        }else{
            bottom_move = 0;        //without label
            tin_can++;
            
            //Test
            __lcd_home();
            initLCD();
            printf("No label");  
            __delay_1s();   
            
        }
        
       
        //Update State
        bottomRockerState = bottom_rocker_release;
                
    }

    return;
}

void bottom_rocker_release(void){
    
    //Test
    __lcd_home();
    initLCD();    
    printf("bottom release");     //Get rid of the printing and delay in actual program
    __delay_1s();    
        
    //Move to release the can, for a few ms
    bottom_rocker_motor_ccw();
    
    //Set a flag(global) for Finishing, to start the distribution process    
    start_bottom_distribution = 1;
    
    //Update state
    bottomRockerState = bottom_rocker_restore;
    
    return;
}

void bottom_rocker_restore(void){
    
    //Test
    __lcd_home();
    initLCD();    
    printf("bottom restore");     //Get rid of the printing and delay in actual program
    __delay_1s();
        
    //Move to the initial position, for a few ms
    bottom_rocker_motor_cw();
    
    //Update state
    bottomRockerState = bottom_rocker_idle;
    
    return;
}

