/*
 * File:   break_beam_sensor.c
 * Author: ouutsuyuki
 *
 * Created on February 24, 2017, 7:21 PM
 */


#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"


void top_break_beam(void) {
    //RA2
    while(1){
        if(swith1){  //No can detected
            //Do nothing
        }else{       //Can detected
            //Call detecting function
        }
    }      
    return;
}

void bottom_break_beam(void) {
    //RA3
    while(1){
        if(swith2){  //No can detected
            //Do nothing
        }else{
            //Call detecting function
        }
    }    
    return;
}



    