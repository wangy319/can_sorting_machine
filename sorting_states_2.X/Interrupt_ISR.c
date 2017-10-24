/*
 * File:   Interrupt_ISR.c
 * Author: ouutsuyuki
 *
 * Created on February 23, 2017, 12:46 PM
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


void interrupt keypressed(void) {  
    /*
    if(INT0IF){
        labeled = 1;
        INT0IF = 0;
    }
    */

    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        //putch(keys[keypress]);
        unsigned char keypress_temp = keys[keypress];
        if (keypress_temp == 0b01000001){   //A
            tot_sorted();
           
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000010){   //B
            pop_results();
         
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000011){   //C
            tin_results();
           
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000100){   //D
            op_time();
            
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == '*'){   
            asm("RESET");
        }
        else{
            initLCD();
            printf(" ");
        }
        __lcd_home();
        
       
        INT1IF = 0;     //Clear flag bit
    }
    
}
