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

//Function Pointer 
void (*topDistributionState)(void);

void top_distribution_initial(void){
    //Initialization
    //Move the door to the initial position BY HAND!
    
    
    //Test
        initLCD();
        __lcd_home();
        printf("TOP init 2"); 
        __delay_1s();
    
    
    //Set state
    topDistributionState = top_distribution_idle;
    return;
}

void top_distribution_idle(void){
    
    //Update state
    if(start_top_distribution==1){        //If finished detection
    
    /*
        //Test
        initLCD();
        __lcd_home();
        printf("TOP dis start"); 
        __delay_1s();
    */    
        
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
      
        top_distribution_motor_cw();        //Go half of the time
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("TOP move cw"); 
        __delay_1s();      
        */  
    }else{
        
        top_distribution_motor_ccw();       //Go half of the time
        
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("TOP move ccw"); 
        __delay_1s();    
        */    
    }
    
    //Update state information
    topDistributionState = top_distribution_move;
    return;
}


void top_distribution_move(void){
    //Code for moving the door to push the cans done
    //Back to the initial position
    
    if(top_move == 1){      //From the result in top_rocker_fsm,  Note the timing issue, receive the right signal
        top_distribution_motor_ccw();       //Go the whole time
        
        /*
        //Test
        initLCD();
        __lcd_home();
        printf("TOP move");                 
        __delay_1s();
        */
        
    }else{
        top_distribution_motor_cw();        //Go the whole time
        
        /*
        initLCD();
        __lcd_home();
        printf("TOP dont move"); 
        __delay_1s();
         */
        
        
        
    }
    
    //Update state information
    topDistributionState = top_distribution_idle;
    return;
}
/*
void top_distribution_restore(void){
    //Go back to initial position
    
    if(top_move == 1){                  
        top_distribution_motor_cw();            //Go half of the time
    }else{
        top_distribution_motor_ccw();           //Go half of the time        
    }
    
    
    //Test
        initLCD();
        __lcd_home();
        printf("TOP restore 2"); 
        __delay_1s();

    //Update state information
    topDistributionState = top_distribution_idle;    
    return;
}
*/