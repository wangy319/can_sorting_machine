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

#define __delay_1s() for(char i=0;i<100;i++){__delay_ms(10);}
#define __lcd_newline() lcdInst(0b11000000);
#define __lcd_clear() lcdInst(0x01);
#define __lcd_home() lcdInst(0b10000000);

void set_time(void);
const char keys[] = "123A456B789C*0#D"; 
int passed = 0;

const char RtcTime[7] = {   0x45, //45 Seconds 
                            0x59, //59 Minutes
                            0x23, //24 hour mode, set to 23:00
                            0x07, //Saturday 
                            0x31, //31st
                            0x12, //December
                            0x16};//2016

void main(void) {
    // <editor-fold defaultstate="collapsed" desc=" STARTUP SEQUENCE ">
    
    TRISA = 0xFF; // Set Port A as all input
    TRISB = 0xFF; //All input mode, KB1 and KB4-7 are for keypad
    TRISC = 0x00011000; // Set I2C pins as input, rest are output
    TRISD = 0x00; //All output mode for LCD
    TRISE = 0x00;    

    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB to be digital instead of analog default  
    
    //nRBPU = 0;      //turn off the internal pull ups for port B 
        
    initLCD();
    //Flag for keypad interrupt
    INT1IF = 1; 
    ei();           //Enable all interrupts
    
    unsigned char time[7];

    I2C_Master_Init(10000); //Initialize I2C Master with 100KHz clock
    //di(); // Disable all interrupts
    
    set_time();
    
    while(1){
    while (passed == 0) {
      
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
        printf("%02x/%02x/%02x", time[6],time[5],time[4]);    //Print date in YY/MM/DD
        printf("%02x:%02x:%02x", time[2],time[1],time[0]);    //HH:MM:SS
        //__delay_1s();   
        
        initLCD();
        __lcd_newline();
        di();
        printf("Press # to Start");
        ei();
        __delay_1s();
    }
        // RB1 is the enable pin, so if there is no key pressed, RB1 will be 0
        // the PIC will wait and do nothing until a key press is signaled
       
        unsigned char keypress = (PORTB & 0xF0)>>4; // Read the 4 bit character code
        while(PORTBbits.RB1 == 1){
            // Wait until the key has been released
        }
     
        while(1){       //To print thins on the LCD, disable the interrupt first, print, and then re-enable interrupt
            di();     //Prevent LCD transmission from being corrupted midway
            //initLCD();
            printf("A:Total   B:Pop  ");
            __lcd_newline();
            printf("C:Tin     D:Time");
            ei();
            __delay_1s();
            di();
            __lcd_home();
            initLCD();
            printf("Press 0 to Reset");
            __delay_1s();
            ei();   // XC8 default routine, enable all interrupt
        }
        Nop();  //Apply breakpoint here because of compiler optimizations 
        Nop();
    }
    return;
}

void set_time(void){
    I2C_Master_Start(); //Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); //Set memory pointer to seconds
    for(char i=0; i<7; i++){
        I2C_Master_Write(RtcTime[i]);
    }    
    I2C_Master_Stop(); //Stop condition
}

void interrupt keypressed(void) {
    int pop_can = 0x1;
    int pop_can_tab = 0x2;
    int tin_can = 0x3;
    int tin_can_label = 0x4;
    int operation_time = 0x286;
    int tot = 0x10;
    
    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        char keypress_temp = keys[keypress];
        if (keypress_temp == 0b01000001){   //A
            initLCD();
            printf("Total Sorted: %02x", tot);
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000010){   //B
            initLCD();
            printf("With Tab: %02x",pop_can_tab);
            __lcd_newline();
            printf("No Tab: %02x",pop_can);
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000011){   //C
            initLCD();
            printf("With Label: %02x",tin_can);
            __lcd_newline();
            printf("No Label: %02x",tin_can_label);
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000100){   //D
            initLCD();
            printf("Time: %02x s", operation_time);
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == '#'){   //#
                initLCD();
                printf("Sorting");
                __delay_1s();
                __delay_1s();
                initLCD();
                printf("Completed"); 
                passed = 1;
        }
        else if(keypress_temp == '0'){
            initLCD();
            asm("RESET");
        }
        else{
            initLCD();
            printf(" ");
        }
        __lcd_home();
        INT1IF = 0;     //Clear flag bit
        __delay_1s();
    }
    
}