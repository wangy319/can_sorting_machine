/*
 * File:   port_test.c
 * Author: Michael Ding
 *
 * Created on July 14, 2016, 10:25 AM
 */


#include "configBits.h"
//<editor-fold defaultstate="collapsed" desc="Variable Defs">
int i = 0;
unsigned char tmp = 0x00;
//</editor-fold>



void delay_10ms(unsigned char n) { 
         while (n-- != 0) { 
             __delay_ms(10); 
         } 
     }



void main(void) {
    
    
    // Disable Interrupt
    INTCON = 0x00;
    
    // SET ALL PORTS TO OUTPUT
    TRISA = 0x00; // PORT A OUTPUT
    TRISB = 0x00; // PORT B OUTPUT
    TRISC = 0x00; // PORT C OUTPUT
    TRISD = 0x00; // PORT D OUTPUT
    TRISE = 0x00; // PORT E OUTPUT
   
    // SET ALL PINS TO OUTPUT LOW
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    // Infinite loop, cycle state on each pin
    while(1){  
        // Same process for all other ports
        // Repeated forever
        tmp = 0x02;
        for (i = 0; i<=1; i++){
            LATE = tmp;
            tmp >>= 1;
            delay_10ms(10);
        }
        LATE = 0x00;
        
        tmp = 0x80;
        for (i = 0; i<=8; i++){
            LATA = tmp;
            tmp >>= 1;
            delay_10ms(10);
        }
        
        LATA = 0x00;
        tmp = 0x80;
        for (i = 0; i<=8; i++){
            LATB = tmp;
            tmp >>= 1;
            delay_10ms(10);
        }
        LATB = 0x00;
        
        tmp = 0x80;
        for (i = 0; i<=8; i++){
            LATC = tmp;
            tmp >>= 1;
            delay_10ms(10);
        }
        LATC = 0x00;
        
        tmp = 0x80;
        for (i = 0; i<=8; i++){
            LATD = tmp;
            tmp >>= 1;
            delay_10ms(10);
        }
        LATD = 0x00;
       
    }
  }