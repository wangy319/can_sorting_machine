/* 
 * File:   bottom_rocker_fsm.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOTTOM_ROCKER_FSM_H
#define	BOTTOM_ROCKER_FSM_H
 
void (*bottomRockerState)(void);        //Function pointer points to the current active state

void bottom_rocker_initial(void);
void bottom_rocker_idle(void);
void bottom_rocker_release(void);
void bottom_rocker_restore(void);

#endif	/* BOTTOM_ROCKER_FSM_H */



