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

void startSorting(void);
void results(void);
void reset_zero_pressed(void);


const char keys[] = "123A456B789C*0#D"; 
void interrupt keypressed(void) {
   
    
    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        //putch(keys[keypress]);
        unsigned char keypress_temp = keys[keypress];
        if (keypress_temp == 0b01000001){   //A
            tot_sorted();
            //initLCD();
            //printf("Total Sorted: %02x", tot);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000010){   //B
            pop_results();
            //initLCD();
            //printf("With Tab: %02x",pop_can_tab);
            //__lcd_newline();
            //printf("No Tab: %02x",pop_can);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000011){   //C
            tin_results();
            //initLCD();
            //printf("With Label: %02x",tin_can);
            //__lcd_newline();
            //printf("No Label: %02x",tin_can_label);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000100){   //D
            op_time();
            //initLCD();
            //printf("Time: %02x s", operation_time);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else{
            initLCD();
            printf(" ");
        }
        __lcd_home();
        INT1IF = 0;     //Clear flag bit
    }
    
}

/*

void tot_sorted(void){
    initLCD();
    printf("Total Sorted: %02x", tot);
    return;
}
            

void op_time(void){
    initLCD();
    printf("Time: %02x s", operation_time);
    return;
}


void tin_results(void){
    initLCD();
    printf("With Label: %02x",tin_can);
    __lcd_newline();
    printf("No Label: %02x",tin_can_label);  
    return;
}

void tin_results(void){
    initLCD();
    printf("With Tab: %02x",pop_can_tab);
    __lcd_newline();
    printf("No Tab: %02x",pop_can);  
    return;
}
*/         