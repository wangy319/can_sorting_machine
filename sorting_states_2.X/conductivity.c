/*
 * File:   conductivity.c
 * Author: ouutsuyuki
 *
 * Created on February 24, 2017, 8:12 PM
 */


#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "I2C.h"
#include "macros.h"


void top_conduction(void){
    //RC1
    while(1){
        if(swith3){  //Conductive -> pop can with pull tag 
            //Do nothing
        }else{       //Not Conductive -> pop can without pull tag 
            //Call detecting function
        }
    }      
    return;
}

void bottom_conduction(void){
    //RC2
    while(1){
        if(swith4){  //Conductive -> NO label
            //Do nothing
        }else{       //Not Conductive -> labeled
            //Call detecting function
        }
    }    
    return;
}
