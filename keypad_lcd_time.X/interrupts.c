
/*http://www.microchip.com/forums/m749119.aspx*/
#pragma interrupt keypressed 
void keypressed(void) {
    printf("hahahaha");
    
    if(INT1IF){
     
        //printf("hahahaha");
        
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        char keypress_temp = keys[keypress];

        if(keypress_temp == '#'){   //#
            
                initLCD();
                printf("Sorting");
                __delay_1s();
                __delay_1s();
                __delay_1s();
                initLCD();
                printf("Completed"); 
                __delay_1s();
            }
            __lcd_home();
            INTCONbits.GIEL = 0;
            while(1){       //To print thins on the LCD, disable the interrupt first, print, and then re-enable interrupt
                INTCONbits.GIEL = 1;
                di();     //Prevent LCD transmission from being corrupted midway
                printf("A:Total   B:Pop ");
                __lcd_newline();
                printf("C:Tin     D:Time");
                INT1IE = 1;
                __lcd_home();
                ei();   // XC8 default routine, enable all interrupt
                __delay_1s();
                __delay_1s();
            }
    }
}


#pragma interruptlow InterruptServiceLow 
void InterruptServiceLow(void) {
//void interrupt keypressed(void) {
    int pop_can = 0x1;
    int pop_can_tab = 0x2;
    int tin_can = 0x3;
    int tin_can_label = 0x4;
    int operation_time = 0x286;
    int tot = 0x10;
    //tot = pop_can+pop_can_tab+tin_can+tin_can_label;
    
    printf("hahahaha");
    
    if(INTCONbits.GIEH){
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        char keypress_temp = keys[keypress];
        if (keypress_temp == 0b01000001){   //A
            initLCD();
            printf("Total Sorted: %02x", tot);
        }
        else if(keypress_temp == 0b01000010){   //B
            initLCD();
            printf("With Tab: %02x",pop_can_tab);
            __lcd_newline();
            printf("No Tab: %02x",pop_can);
        }
        else if(keypress_temp == 0b01000011){   //C
            initLCD();
            printf("With Label: %02x",tin_can);
            __lcd_newline();
            printf("No Label: %02x",tin_can_label);
        }
        else if(keypress_temp == 0b01000100){   //D
            initLCD();
            printf("Time: %02x", operation_time);
        }
        
        else{
            initLCD();
            printf("AER201");
        }
        __lcd_home();
        INTCONbits.GIEH  = 0;     //Clear flag bit
    }
    
}

 
