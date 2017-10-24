/* 
 * File:   top_rocker_fsm.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TOP_ROCKER_FSM_H
#define	TOP_ROCKER_FSM_H

void (*topRockerState)(void);        //Function pointer points to the current active state

void top_rocker_initial(void);
void top_rocker_idle(void);
void solenoids_out(void);
void solenoids_back(void);
void top_rocker_release(void);
void top_rocker_restore(void);

#endif	/* TOP_ROCKER_FSM_H */



