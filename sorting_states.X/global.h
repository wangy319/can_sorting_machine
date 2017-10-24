/* 
 * File:   global.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef GLOBAL_H
#define	GLOBAL_H
 
extern const char keys[]; 

//Declare Global Variables
extern unsigned int pop_can;
extern unsigned int pop_can_tab;
extern unsigned int tin_can;
extern unsigned int tin_can_label;
extern signed int operation_time;
extern unsigned int tot;
extern unsigned int tabed;
extern unsigned int top_move;
extern unsigned int start_top_distribution;
extern unsigned int fsm1;
//extern unsigned int fsm2;



#define switch1  PORTAbits.RA2  // Switch on RA2    //top break beam
#define switch2  PORTAbits.RA3  // Switch on RA3    //bottom break beam
#define switch3  PORTCbits.RC1  // Switch on RC1    //top conductor
#define switch4  PORTCbits.RC2  // Switch on RC2    //bottom conductor




//time calculation for operation_time file
extern unsigned char time[7];
extern unsigned char Start_time[2];    //Hour, StartMinute, SrartSecond;
extern unsigned long total_start, total_end;              //totalHour, totalMinute, totalSecond;

#endif	/* GLOBAL_H */



