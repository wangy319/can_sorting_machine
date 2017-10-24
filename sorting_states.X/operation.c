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
#include "operation.h"
#include "global.h"
#include "top_rocker_fsm.h"
#include "top_distribution_fsm.h"
#include "solenoids.h"


const char keys[] = "123A456B789C*0#D";

unsigned char Start_time[2];    //Hour, StartMinute, SrartSecond;
unsigned long total_start, total_end;  


void standby(void) {

    di(); // Disable all interrupts
    __lcd_home();
    initLCD();
    Nop();
    Nop();
    
    while(1){
        //Reset RTC memory pointer 
        I2C_Master_Start(); //Start condition
        I2C_Master_Write(0b11010000); //7 bit RTC address + Write
        I2C_Master_Write(0x00); //Set memory pointer to seconds
        I2C_Master_Stop(); //Stop condition

        //Read Current Time
        I2C_Master_Start();
        I2C_Master_Write(0b11010001); //7 bit RTC address + Read
        for(unsigned char i=0;i<0x06;i++){
            time[i] = I2C_Master_Read(1);
        }
        time[6] = I2C_Master_Read(0);       //Final Read without ack
        I2C_Master_Stop();        
       
        __lcd_home();
        printf("%02x/%02x   ",time[5],time[4]);    //Print date in YY/MM/DD
        printf("%02x:%02x:%02x", time[2],time[1],time[0]);    //HH:MM:SS
        
        __lcd_newline();
        printf("Press # to Start");
        
        //Read key pressed
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        while(PORTBbits.RB1 == 1){
            // Wait until the key has been released
        }
        unsigned char keypress_temp = keys[keypress];                
        
        if(keypress_temp == '#'){   //#         
            Start_time[2] = time[2];
            Start_time[1] = time[1];
            Start_time[0] = time[0];             
            break;
        }
        __delay_1s();   //Count for one second      
                        //If put it here, total time will be smaller by one second(4s))
    }
}

    
//Start Sorting Process
void startSorting(void){
                                
    //Initialize the program
    initialization();
    
/*Enter FSM checking while loop*/
    while(1){
        //Check FSM status
            //for now, top only
        
        //Test
        __lcd_home();
        initLCD();    
        printf("here");     //Get rid of the printing and delay in actual program
        __delay_1s();

        (*topRockerState)();
        //topDistributionState();
        //bottomRockerState();
        //bottomDistributionState();

        //__lcd_newline();
        //printf("Complete");
        __delay_ms(200);
        //After complete, stop all operation


        if(fsm1 >= 4){
            //Test
            __lcd_home();
            initLCD();    
            printf("time out");     //Get rid of the printing and delay in actual program
            __delay_1s();
            
            break;          //Stop operation
        }else{
            
        }
    }
    return;
} 
    

void initialization(void){
    
    //Counters
    //fsm1 = fsm2 = fsm3 = fsm4 = 0;
    fsm1 = 0;
    
    initLCD();
    __lcd_home();        
    printf("Initializing");     //Get rid of the printing and delay in actual program
    __delay_1s();
    
    //initialize loading rocker, break beam sensor
    LATBbits.LATB0 = 1;     //Initialize loading motor. The motor is constantly 
                            //moving, unless RB0 is set to zero
                            //See PWM motor to control the speed
    LATEbits.LATE0 = 1;     //Send signal to both laser beam sensor to start sending signal
    //This 2 pins is clear when finish sorting. They are cleared after the sorting loop(correct)
    
    //Initialize FSMs
    top_rocker_initial();
    
    
    
    //top_distribution_initial();
    //bottom_rocker_initial();
    //bottom_distribution_initial();
    
/*    
    __delay_1s();           //Get rid of these delay when running
    __delay_1s();         
    __delay_1s(); 
    __delay_1s(); 
 */
}


signed int done_sorting(void){
    
    fsm1 = 0;               //Reset stop counter1
    //fsm2 = 0;               //Reset stop counter2
    
    signed int total_second;
    unsigned char End_time[2];      //EndHour, EndMinute, EndSecond;
    
    //Done Sorting, read ending time, and calculate the operation time
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    I2C_Master_Stop(); //Stop condition

    //Read Current Time
    I2C_Master_Start();
    I2C_Master_Write(0b11010001); //7 bit RTC address + Read
    for(unsigned char i=0;i<0x06;i++){
        time[i] = I2C_Master_Read(1);
    }
    time[6] = I2C_Master_Read(0);       //Final Read without ack
    I2C_Master_Stop();  
        
    End_time[2] = time[2];
    End_time[1] = time[1];
    End_time[0] = time[0];
    
    total_start = (Start_time[1]/16*10 + Start_time[1]%16)*60 + (Start_time[0]/16*10 + Start_time[0]%16);
    total_end = (End_time[1]/16*10 + End_time[1]%16)*60 + (End_time[0]/16*10 + End_time[0]%16);
    total_second = total_end - total_start;
    
    if(total_second <= 0){   
        total_second = 3600 + total_second;        
    }
    return total_second;
}


void results(void){
    
    while(1){    
        __lcd_home();
        initLCD();
        Nop();
        Nop();
        
        printf("A:Total   B:Pop ");
        __lcd_newline();
        printf("C:Tin     D:Time");
        ei();
        __delay_1s();
        __delay_1s();
        di();
        initLCD();
        Nop();
        Nop();
        printf("Press 0 to Reset");
        ei();
        __delay_1s();
        di();  
        
        //Check if restart is pressed
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        unsigned char keypress_temp = keys[keypress];
        
        if(keypress_temp == '0'){   
            break;
        }   
    }
    return;
}


void tot_sorted(void){
    __lcd_home();
    initLCD();
    printf("Total Sorted: %02x", tot);
    return;
}   

void op_time(void){
    __lcd_home();
    initLCD();
    printf("Time: %01d min %02d s", operation_time/60, operation_time%60 );
    return;
}

void tin_results(void){
    __lcd_home();
    initLCD();
    printf("With Label: %02x",tin_can);
    __lcd_newline();
    printf("No Label: %02x",tin_can_label);  
    return;
}

void pop_results(void){
    __lcd_home();
    initLCD();
    printf("With Tab: %02x",pop_can_tab);
    __lcd_newline();
    printf("No Tab: %02x",pop_can);  
    return;
}