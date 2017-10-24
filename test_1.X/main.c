/*
 * File:   main_sorting_states.c
 * Author: ouutsuyuki
 *
 * Created on February 25, 2017, 3:25 PM
 */


/* Enter Standby mode first
 * 
 * 
 * To exit FSMs, set many counter to count the time in idle state,
 * If all of them reaches 3s,(A&&B&&C,etc)
 * exit the FSMs
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


const char keys[] = "123A456B789C*0#D"; 


//Declare Global Variables
unsigned int pop_can = 0x0;
unsigned int pop_can_tab = 0x0;
unsigned int tin_can = 0x0;
unsigned int tin_can_label = 0x0;
signed int operation_time;
unsigned int tot = 0x0;
unsigned char time[7];
unsigned int tabed;         //Signal for top conductivity detection
unsigned int labeled;       //Signal for bottom conductivity detection
unsigned int top_move;      //Indicate if the top distribution door should move
unsigned int bottom_move;      //Indicate if the bottom distribution door should move
unsigned int start_top_distribution = 0;    //Flag(global) for finishing detection, to start the top distribution motor    
unsigned int start_bottom_distribution = 0; //Flag(global) for finishing detection, to start the bottom distribution motor    
unsigned int fsm1 = 0;      //top detection stop counter
unsigned int fsm2 = 0;        //bottom detection stop counter


//time calculation for operation_time file
unsigned char Start_time[2];    //Hour, StartMinute, SrartSecond;
unsigned long total_start, total_end;              //totalHour, totalMinute, totalSecond;


void interrupt keypressed(void);

//Time bits for RTC
const char real_time[7] = {  0x45, //45 Seconds 
                            0x59, //56 Minutes
                            0x17, //24 hour mode, set to 17:00
                            0x04, //Thursday 
                            0x31, //31st
                            0x02, //Feb
                            0x17};//2017

void set_time(void){
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    for(char i=0; i<7; i++){
        I2C_Master_Write(real_time[i]);
    }    
    I2C_Master_Stop(); //Stop condition    
}

void main(void) {
    //TRISA = 0x11111100;       // Set Port A as all input exceptA0 and A1(Confirmed)
    TRISA = 0xF3;
    //TRISB = 0b11110011; // Set Keypad Pins as input, rest are output (Confirmed)
    TRISB = 0xF3;           //RB0 is the emergency stop 
    //TRISC = 0x00011110; // Set I2C pins as input, rest are output (Works, from board_test)
    TRISC = 0x1E;       //RC0 is the signal to loading motor 
    TRISD = 0x00;       //All output mode RD2-7 are for LCD (Confirmed)
    TRISE = 0x00;       //Set PortD all as output (Confirmed)
    
    LATA = 0xFF;        //Clear all ports output
    LATAbits.LA2 = 0;
    LATAbits.LA3 = 0;
    LATB = 0x00; 
    LATC = 0x00;        //RC0 is set to testing input //Solenoids are given  HIGH at the beginning to keep them in place
    LATD = 0x00;        //USE RD0 = LOW, RD1 = HIGH for testing
    LATE = 0x08;
    
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB(All port) to be digital instead of analog default 
    
    initLCD();      //Initialize LCD
    Nop();
    Nop();
    INT1IE = 1;     //Set Interrupt enable bit for keypad
    //INT0IE = 1;     //Set Interrupt enable bit for emergency stop
    
    I2C_Master_Init(10000);     //Initialize I2C Master with 100KHz clock
    set_time();                 //Call set_time to set begin time

    //This is the main loop
    while(1){            
        
        //Enter Standby mode
        standby();
    
        //Call sorting
        startSorting();
       
        //Obtain operation time
        operation_time = done_sorting();       //Enter the whole operation process
                                                //Interrupt is not enabled        
        Nop();
        Nop();
        
        LATA = 0xFF;        //Clear all ports output
        LATAbits.LA2 = 0;
        LATAbits.LA3 = 0;
        LATB = 0x00; 
        LATC = 0x00;        //RC0 is set to testing input //Solenoids are given  HIGH at the beginning to keep them in place
        LATD = 0x00;        
        //LATE = 0x00001000;  //Set RE3 MCLR input
        LATE = 0x08;
        
        results();              //Display sorting information per user's request
    }    
    Nop();
    Nop();
    return;
} 

/* Optimization
 * Write a function get_time to get the current operating time, this fuction returns
 * the current time
 * Then move the time difference calculation to the main program.
 */

/*
void reset(void){
    
    
    initLCD();
        __lcd_home();
        printf("hhhhhhhhhhh"); 
        __delay_1s();
    __delay_1s();
    __delay_1s();
    
    asm("RESET");
    return;
}
 */