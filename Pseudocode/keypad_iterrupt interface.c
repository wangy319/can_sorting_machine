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

#define __delay_1s() for(char i=0;i<100;i++){__delay_ms(10);}
#define __lcd_newline() lcdInst(0b11000000);
#define __lcd_clear() lcdInst(0x01);
#define __lcd_home() lcdInst(0b10000000);

const char keys[] = "123A456B789C*0#D"; 
int passed = 0;

void main(void) {
    TRISC = 0x00;
    TRISD = 0x00;   //All output mode
    //TRISB = 0xFF;   //All input mode
    TRISB = 0b11110010; // Set Keypad Pins as input, rest are output
    LATB = 0x00; 
    LATC = 0x00;
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB to be digital instead of analog default  
    initLCD();
    INT1IE = 1;
    ei();           //Enable all interrupts
    while(1){
        while(passed == 0){ 
            initLCD();
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
            __delay_1s();
            ei();   // XC8 default routine, enable all interrupt
        }
        Nop();  //Apply breakpoint here because of compiler optimizations
        Nop();
    }    
    return;
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
            __delay_1s();
        }
        else if(keypress_temp == 0b01000010){   //B
            initLCD();
            printf("With Tab: %02x",pop_can_tab);
            __lcd_newline();
            printf("No Tab: %02x",pop_can);
            __delay_1s();
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
            __delay_1s();
        }
        else if(keypress_temp == 0b01000100){   //D
            initLCD();
            printf("Time: %02x s", operation_time);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == '#'){   //#
                initLCD();
                printf("Sorting");
                __delay_1s();
                __delay_1s();
                __delay_1s();
                initLCD();
                printf("Completed"); 
                passed = 1;
        }
        else if(keypress_temp == '0'){
            asm("RESET");
        }
        else{
            //initLCD();
            //printf(" ");
        }
        __lcd_home();
        INT1IF = 0;     //Clear flag bit
    }
    
}




/*
 
 
 
 */