
/*These are all the subfuctions used in pop_fsm*/

int EntryState(void){		//triggerred by break beam sensor
	//Stop rocker
}

int detect = 0;		//global variable

int DetectionState(void){
	//move solenoid out
	int detect = 0;
	if(current==1){
		detect = 1;
	}
	//move solenoid back
}

//Distribution depends on detection result
int DistributionState(void){
	if(detect ==1){
		//motor
		//door guide to the left
	}else{
		//motor
		//door guide to the right
	}
}

int Exit(void){
	goto tin_fsm_label;		//Check the other type;
}



//Code for motors
void motor (data){
    if(data ==1){
        LATC = 0x5;         //binary bits can give current
    }else{
        LATC = 0x9;
    }
}
