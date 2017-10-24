/*
 * File:   Servo.c
 * Author: ouutsuyuki
 *
 * Created on March 17, 2017, 12:09 PM
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
#include "servo.h"

void bottom_servo_rightTilt() 
{
  unsigned int i;
  for(i=0;i<4;i++)
  {
    LATBbits.LATB3 = 1;
    __delay_us(2200);
    LATBbits.LATB3 = 0;
    __delay_us(17800);
    
            
            labeled = labeled || PORTCbits.RC2;
            //labeled = labeled || PORTBbits.RB0;
    
  }
  return;
}

void bottom_servo_leftTilt() //180 Degree
{
  unsigned int i;
  for(i=0;i<15;i++)
  {
    LATBbits.LATB3 = 1;
    __delay_us(800);
    LATBbits.LATB3 = 0;
    __delay_us(19200);
  }
  return;
}

/*
void top_servo_init() //0 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATBbits.LATB2 = 1;
    __delay_us(1500);
    LATBbits.LATB2 = 0;
    __delay_us(18500);
  }
  return;
}
*/
void top_servo_rightTilt() 
{
  unsigned int i;
  for(i=0;i<6;i++)
  {
    LATBbits.LATB2 = 1;
    __delay_us(2200);
    
    LATBbits.LATB2 = 0;
    __delay_us(17800);
  }
  return;
}

void top_servo_leftTilt() //180 Degree
{
  unsigned int i;
  for(i=0;i<12;i++)
  {
    LATBbits.LATB2 = 1;
    __delay_us(800);
    LATBbits.LATB2 = 0;
    __delay_us(19200);
  }
  return;
}
