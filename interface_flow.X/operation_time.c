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


const char keys[] = "123A456B789C*0#D";
signed int total_second;

unsigned int operation(void) {
    
    unsigned char Start_time[2];    //Hour, StartMinute, SrartSecond;
    unsigned char End_time[2];      //EndHour, EndMinute, EndSecond;
    unsigned long total_start, total_end;              //totalHour, totalMinute, totalSecond;
    
    initLCD();
    unsigned char time[7];

    di(); // Disable all interrupts
    
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
    
    //Start Sorting Process
    startSorting();   
    
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

