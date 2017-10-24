/*
 * File:   Sort.c
 * Author: ouutsuyuki
 *
 * Created on February 23, 2017, 12:57 PM
 */

#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"


const char keys[] = "123A456B789C*0#D";

void results(void);
//void Standby(void);
void initialization(void);


/*This function controls the sorting process*/
void startSorting(void){
    
    initLCD();
    __lcd_home();
        
    printf("Initializing");     //Get rid of the printing and delay in actual program
    __delay_1s();
                                
    //Initialize the program
    initialization();
    
    
    
    
    __lcd_newline();
    printf("Complete");
    __delay_1s();
    //After complete, stop all operation
    return;
}


void initialization(void){
    //initialize loading rocker, break beam sensor
    //Note: there is a 1s delay after press start 
    
    LATBbits.LATB0 = 1;     //Initialize loading motor. The motor is constantly 
                            //moving, unless RB0 is set to zero
                            //See PWM motor to control the speed
    LATEbits.LATE0 = 1;     //Send signal to both laser beam sensor to start sending signal
    //This 2 pins are still be HIGH when reset "0" is pressed
        
    __delay_1s();           //Get rid of these delay when running
    __delay_1s();           
}

void results(void){
    
    int restart_flag = 0;
    
    while(restart_flag == 0){
        di();     //Prevent LCD transmission from being corrupted midway        
        __lcd_home();
        initLCD();
        printf("A:Total   B:Pop ");
        __lcd_newline();
        printf("C:Tin     D:Time");
        ei();
        __delay_1s();
        __delay_1s();
        
        di();
        __lcd_home();
        initLCD();
        printf("Press 0 to Reset");
        ei();
        __delay_1s();
                
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        unsigned char keypress_temp = keys[keypress];
        
        if(keypress_temp == '0'){   //0
            printf("Restart");
            __delay_1s();
            restart_flag = 1;
        }   
    }
    return;
}

