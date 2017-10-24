/*
 * File:   Info_retreat.c
 * Author: ouutsuyuki
 *
 * Created on February 23, 2017, 12:52 PM
 */

#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"



void results(void){
    while(1){
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
    //goback = 0;
}

