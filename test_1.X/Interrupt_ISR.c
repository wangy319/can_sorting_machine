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

void reset(void);

void interrupt keypressed(void) {   
    /*
    if(INT0IF){
        LATA = 0xFF;        //Clear all ports output
        LATAbits.LA2 = 0;
        LATAbits.LA3 = 0;
        LATB = 0x00; 
        LATC = 0x00;        //RC0 is set to testing input //Solenoids are given  HIGH at the beginning to keep them in place
        LATD = 0x00;        //USE RD0 = LOW, RD1 = HIGH for testing
        LATE = 0x08;
        
        
        __lcd_home();
        initLCD();    
        printf("Emergency");     
        __delay_1s(); 
        __delay_1s();
        
        asm("RESET");
        INT0IF = 0;
    }
    */
    
    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
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
        }else if(keypress_temp == '*'){   //D            
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
