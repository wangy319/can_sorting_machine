//#include libraries

//define keypad characters
const char keys[] = "123A456B789C*0#D"; 

//Define global variables
int StartTime = 0;
int EndTime = 0;
int OperationTime = EndTime - StartTime;

int pop_can = 0;
int pop_can_tab = 0;
int tin_can = 0;
int tin_can_label = 0;
int total_sorted = pop_can + pop_can_tab + tin_can + tin_can_label;

//Main 
void main(){

	//set TRIS to motor input
	//set TRIS to sensor input
	//set bits to enable motor

	//Initializations
	
	INT1IE = 1;		//set interrupt flag bit for emergency stop button
	SortEnd = 0;

	while(start_signal != 1){
		//Stay in Standby Mode
		//If <Start> signal is received, jump out of the loop
	}

//There will be 2 finite state machines(FSM) defined in the program, one controls the 
	//the flow for soting tin can, and the other one controls the flow for the pop can. 
//Once the top break beam sensor(for tin cans) is triggered, enter the 1st FSM, and once 
	//the bottom break beam sensor(for pop cans) is triggered, enter the 2nd FSM.

	//Defining FSM_tin for the tin cans, and FSM_pop for the pop cans
	while(SortEnd == 0){
		
		if(pop_detect==1){
pop_fsm_label:
			void pop_fsm();		//Process in FSM for pop cans
			// or goto pop_fsm_label;
		}
			
		if(tin_detect==1){
tin_fsm_label:
			void tin_fsm();		//Process in FSM for tin cans
			// or goto tin_fsm_label;
		}
		else{
			break;
		}
	}

/*Display final information interface*/
}


void interrupt keypressed(void) {
    
    if(INT1IF){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        char keypress_temp = keys[keypress];
        if (keypress_temp == 0b01000001){   //A
            initLCD();
            printf("Total Sorted: %02x", tot);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000010){   //B
            initLCD();
            printf("With Tab: %02x",pop_can_tab);
            __lcd_newline();
            printf("No Tab: %02x",pop_can);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000011){   //C
            initLCD();
            printf("With Label: %02x",tin_can);
            __lcd_newline();
            printf("No Label: %02x",tin_can_label);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == 0b01000100){   //D
            initLCD();
            printf("Time: %02x s", operation_time);
            __delay_1s();
            __delay_1s();
            __delay_1s();
        }
        else if(keypress_temp == '#'){   //#
                initLCD();
                printf("Sorting");
                __delay_1s();
                __delay_1s();
                __delay_1s();

                goto info_display;

                initLCD();
                printf("Completed"); 
                passed = 1;
        }
        else if(keypress_temp == '0'){
            asm("RESET");
        }
        else{
            //initLCD();
            //printf(" ");
        }
        __lcd_home();
        INT1IF = 0;     //Clear flag bit
    }
}



int keypad_lcd (void){

info_display: 				//Label for goto instruction
	/* information selection interface showing on LCD,
	sorting information is displayed per users' request;
	could g back to main fuction */
}










