/* 
 * File:   top_distribution_fsm.h
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TOP_DISTRIBUTION_FSM_H
#define	TOP_DISTRIBUTION_FSM_H
 
void (*topDistributionState)(void);
void top_distribution_initial(void);
void top_distribution_idle(void);
void top_distribution_prepare(void);
void top_distribution_move(void);

#endif	/* TOP_DISTRIBUTION_FSM_H */



