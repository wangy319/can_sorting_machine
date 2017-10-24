// Code source: http://stackoverflow.com/questions/1371460/state-machines-tutorials

void pop_fsm(){

pop_fsm_label:
    //Call subfuctions for different states
    int EntryState(void);
    int DetectionState(void);
    int DistributionState(void);
    int Exit(void);

    /* array and enum below must be in sync! */

    int (* state[])(void) = { EntryState, DetectionState, DistributionState, Exit};

    enum class PopState {EntryState, DetectionState, DistributionState, Exit}

    enum ret_codes { ok, fail, repeat};
    struct transition {
        enum PopState src_state;
        enum ret_codes   ret_code;
        enum PopState dst_state;
    };

    /* transitions from end state aren't needed */
    struct transition state_transitions[] = {
        {EntryState,                ok,     DetectionState},
        {EntryState,                fail,   EntryState},
        {DetectionState,            ok,     DistributionState},
        {DetectionState,            fail,   Exit},
        {DistributionState,         ok,     Exit},
        {DistributionState,         fail,   Exit},
    }
    

    #define EXIT_STATE Exit
    #define ENTRY_STATE EntryState

    int main(int argc, char *argv[]) {
        enum state_codes cur_state = ENTRY_STATE;
        enum ret_codes rc;
        int (* state_fun)(void);    //Function pointer

        for (;;) {
            state_fun = state[cur_state];
            rc = state_fun();
            if (EXIT_STATE == cur_state)
                break;
            cur_state = lookup_transitions(cur_state, rc);
        }

        return EXIT_SUCCESS;
    }
}


/*
void detection(void){

	if (break beam is disrupted){
		Stop the Rocker motor;    //Stop the can from moving

        move solenoid in;

		if(electric signal is received){		//Without label
            move solenoid out;

			Roker moves to allow the can roll out;
			Roker keeps moving and wait for the next instruction;
			door opens to the left;		//Alow the tin can fall into the left bin
		}else{
            move solenoid out;

			Roker moves to allow the can roll out;
			Roker keeps moving and wait for the next instruction;
			door opens to the right;		//Alow the tin can fall into the left bin
		}
	}
*/
	


















