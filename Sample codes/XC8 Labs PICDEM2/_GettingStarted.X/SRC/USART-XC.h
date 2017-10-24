#ifndef __USART_XC_H__
#define __USART_XC_H__

void USARTInit(void);                // manual USART init required for printf() with XC compilers
#define mOPEN_USART USARTInit();

#if __XC8
    #if _18F4520
        #define BAUD 19200           // Proteus virtual terminal expects 19200/n/1
    #else
        #define BAUD 9600            // Proteus virtual terminal expects 9600/n/1
    #endif

    #define FOSC 4000000L
    #define DIVIDER ((int)(FOSC/(16UL * BAUD) -1))

    #define RX_PIN TRISC7
    #define TX_PIN TRISC6
#endif                               // __XC8


#if __XC16
    void IOMap (void);

    #include <libpic30.h>            // needed for "__C30_UART" library function

    #define FOSC 8000000L            // device clock frequency (8MHz for EXP16)
    #define FCY FOSC/2               // device instruction frequency

    #define BAUD 9600
    #define round(x) (int)(((float)(x))>0?(float)(x)+0.5:(float)(x)-0.5)
    #define BRGVAL round((FCY/BAUD/(float)16)-1)
#endif                               // __XC16

#endif                               // __USART_XC_H__
