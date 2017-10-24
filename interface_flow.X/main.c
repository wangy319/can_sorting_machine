                            /*
 * File:   main.c
 * Author: True Administrator
 *
 * Created on July 18, 2016, 12:11 PM
 */


#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"

#define switch1  PORTAbits.RA2  // Switch on RA2    //top break beam
#define switch2  PORTAbits.RA3  // Switch on RA3    //bottom break beam
#define switch1  PORTAbits.RC1  // Switch on RC1    //top conductor
#define switch2  PORTAbits.RC2  // Switch on RC2    //bottom conductor

const char keys[] = "123A456B789C*0#D"; 
void interrupt keypressed(void);
//Declare Global Variables
unsigned int pop_can = 0x0;
unsigned int pop_can_tab = 0x0;
unsigned int tin_can = 0x0;
unsigned int tin_can_label = 0x0;
signed int operation_time;
unsigned int tot = 0x0;

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
    TRISA = 0x11111100;       // Set Port A as all input (Confirmed)
    TRISB = 0b11110010; // Set Keypad Pins as input, rest are output (Confirmed)
    //TRISC = 0x00;       // Set PortC all as output(Original, also works)
    TRISC = 0x00011110; // Set I2C pins as input, rest are output (Works, from board_test)
    TRISD = 0x00;       //All output mode RD2-7 are for LCD (Confirmed)
    TRISE = 0x00;       //Set PortD all as output (Confirmed)
    
    LATA = 0x00;        //Clear all ports output
    LATB = 0x00; 
    LATC = 0x01;
    LATD = 0x00; 
    LATE = 0x00001000;  //Set RE3 MCLR input
    
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB(All port) to be digital instead of analog default 
    
    initLCD();      //Initialize LCD 
    INT1IE = 1;     //Set Interrupt enable bit
    
    unsigned char time[7];      //Time
    I2C_Master_Init(10000);     //Initialize I2C Master with 100KHz clock
    set_time();                 //Call set_time to set begin time
      
    //This is the main loop
    while(1){            
        
        operation_time = operation();       //Enter the whole operation process
                                            //Interrupt is not enabled        
        LATA = 0x00;        //Clear all ports output
        LATB = 0x00;        //To stop all actuators and sensors
        LATC = 0x01;
        LATD = 0x00; 
        LATE = 0x00; 
        
        results();              //Display sorting information per user's request
    }    
    return;
} 

/* Optimization
 * Write a function get_time to get the current operating time, this fuction returns
 * the current time
 * Then move the time difference calculation to the main program.
 */

void tot_sorted(void){
    initLCD();
    printf("Total Sorted: %02x", tot);
    return;
}   

void op_time(void){
    initLCD();
    printf("Time: %01d min %02d s", operation_time/60, operation_time%60 );
    return;
}

void tin_results(void){
    initLCD();
    printf("With Label: %02x",tin_can);
    __lcd_newline();
    printf("No Label: %02x",tin_can_label);  
    return;
}

void pop_results(void){
    initLCD();
    printf("With Tab: %02x",pop_can_tab);
    __lcd_newline();
    printf("No Tab: %02x",pop_can);  
    return;
}