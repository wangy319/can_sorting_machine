
/*These are all the subfuctions used in tin_fsm*/

int EntryState(void){		//triggerred by break beam sensor
	//Stop rocker
}

int detect = 0;		//global variable

int DetectionState(void){
	int detect = 0;
	if(current==1){
		detect = 1;
	}
}

//Distribution depends on detection result
int DistributionState(void){
	if(detect ==1){
		//door guide to the left
	}else{
		//door guide to the right
	}
}

int Exit(void){
	goto pop_fsm_label;		//Check the other type;
}