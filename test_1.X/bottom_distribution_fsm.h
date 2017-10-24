/* 
 * File:   bottom_distribution_fsm.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOTTOM_DISTRIBUTION_FSM_H
#define	BOTTOM_DISTRIBUTION_FSM_H
 
void (*bottomDistributionState)(void);
void bottom_distribution_initial(void);
void bottom_distribution_idle(void);
void bottom_distribution_prepare(void);
void bottom_distribution_move(void);

#endif	/* BOTTOM_DISTRIBUTION_FSM_H */



