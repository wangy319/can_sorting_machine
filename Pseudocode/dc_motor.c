
https://electrosome.com/category/tutorials/pic-microcontroller/mplab-xc8/



//DC motor Speed Control

//https://electrosome.com/dc-motor-speed-control-pic-pwm/

void main()
{
  short duty  = 0; //initial value for duty

  TRISD = 0xFF; //PORTD as input
  TRISC = 0x00; //PORTC as output
  TRISB = 0x00; //PORTB as output
  PORTB = 0x02; //Run motor in anticlock wise

  PWM1_Init(1000);  //Initialize PWM1
  PWM1_Start();  //start PWM1
  PWM1_Set_Duty(duty); //Set current duty for PWM1

  while (1)        // endless loop
  {
     if (!RD0_bit && duty<250) //if button on RD0 pressed      
     {       
        Delay_ms(40);       
        duty = duty + 10;  //increment current_duty     
        PWM1_Set_Duty(duty);  //Change the duty cycle      
     }     
     if (!RD1_bit && duty >0) //button on RD1 pressed
     {
       Delay_ms(40);
       duty = duty - 10;  //decrement duty
       PWM1_Set_Duty(duty);
     }
    Delay_ms(10);      // slow down change pace a little
  }
}


//DC Motor and L293D
//https://electrosome.com/dc-motor-l293d-pic-microcontroller/

void main()
{
 TRISB = 0; // PORT B as output port
 PORTB = 1; // Set RB0 to high
 do
 {
   //To turn motor clockwise
   PORTB.F0 = 1;
   Delay_ms(2000);//2 seconds delay

   //To Stop motor
   PORTB = 0; // or PORTB = 3 
   Delay_ms(2000);//2 seconds delay

   //To turn motor anticlockwise direction
   PORTB.F1 = 1;
   Delay_ms(2000);//2 seconds delay

   //To Stop motor
   PORTB = 0; // or PORTB = 3 (3 = 0b00000011)
   Delay_ms(2000); // 2 seconds delay

 }while(1);
}




//PWM
//https://electrosome.com/pwm-pic-microcontroller-mplab-xc8/
#define _XTAL_FREQ 20000000
#define TMR2PRESCALE 4

#include <xc.h>

// BEGIN CONFIG
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

long freq;

int PWM_Max_Duty()
{
  return(_XTAL_FREQ/(freq*TMR2PRESCALE);
}

PWM1_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}

PWM2_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}

PWM1_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty>>2;
  }
}

PWM2_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty>>2;
  }
}

PWM1_Start()
{
  CCP1M3 = 1;
  CCP1M2 = 1;
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  TMR2ON = 1;
  TRISC2 = 0;
}

PWM1_Stop()
{
  CCP1M3 = 0;
  CCP1M2 = 0;
}

PWM2_Start()
{
  CCP2M3 = 1;
  CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
    TMR2ON = 1;
    TRISC1 = 0;
}

PWM2_Stop()
{
  CCP2M3 = 0;
  CCP2M2 = 0;
}

void main()
{
  unsigned int i=0,j=0;
  PWM1_Init(5000);
  PWM2_Init(5000);
  TRISD = 0xFF;
  TRISB = 0;
  PWM1_Duty(0);
  PWM2_Duty(0);
  PWM1_Start();
  PWM2_Start();
  do
  {
    if(RD0 == 0 && i<1000)
      i=i+10;
    if(RD1 == 0 && i>0)
      i=i-10;
    if(RD2 == 0 && j<1000)
      j=j+10;
    if(RD3 == 0 && j>0)
      j=j-10;
    PWM1_Duty(i);
    PWM2_Duty(j);

    __delay_ms(50);
  }while(1);
}