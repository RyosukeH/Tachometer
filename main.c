/* 
 * File:   main.c
 * Author: MMH
 *
 * Created on 2013/12/26, 23:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "globalDefine.h"
#include "motor.h"


// Configuration bits
#pragma config WDTEN = 0,  CONFIG1H = 0x48, CONFIG2L = 0x00, PBADEN = 0, PWRT = ON
//#pragma config CONFIG5L = 0x0f



// Function prototype
static void initSystem(void);
static void initPortReg(void);
static void initInterrupt(void);    // This Func called after everything is ready.



// Interrupt function
void interrupt myInt(void){

    if(INTCONbits.INT0IF){
        INTCONbits.GIE = 0;     // Disable all interrupt
        INTCONbits.INT0IE = 0;
        INTCONbits.INT0IF = 0;  // interrupt flag down     

        // test LED On Off
        //PORTAbits.RA0 = ~PORTAbits.RA0;
        motorChange(CW, mtrPhase);

        INTCONbits.INT0IE = 1;  // Enable INT0 interrupt
        INTCONbits.GIE = 1;     // Enable all interrupt
    }
}

int main(int argc, char** argv) {

    int i;
    

    initSystem();
    initPortReg();

    // motor function test
    initMotorPhase();
    //mtrDriverActive();


    PORTAbits.RA0 = 0;
    for(i=0; i<100; i++){
            __delay_ms(10);
    }
    //PORTAbits.RA0 = ~PORTAbits.RA0;

    // interrupt test
    initInterrupt();
    ei();
    
    while(1){
/*
        //PORTAbits.RA0 = 1;
        //PORTC = 0x0f;

        // motor function test
        //motorChange(CW, mtrPhase);
        for(i=0; i<100; i++){
            __delay_ms(1);
        }
        
        //PORTAbits.RA0 = 0;
        //PORTC = 0x00;

        // motor function test
        //motorChange(CW, mtrPhase);
        for(i=0; i<100; i++){
            __delay_ms(1);
        }

   */
    }

    return (EXIT_SUCCESS);
}

static void initSystem(void){

    // Clock setting
    // Internal Clock and PLL -> 64MHz
    OSCCON = 0x78;
    OSCTUNE = 0xc0;


    // Timer0
    T0CON = 0x06;

}



static void initPortReg(void){

    // Port A : LED Control
    // Port output
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;


    // Port B : Ext Interrupt
    // Tachometer signal input
    TRISBbits.TRISB0 = 1;   // use external interrupt 0 input
    ANSELHbits.ANS12 = 0;


    // Port C : Stepping Motor Control
    // Port output
    TRISCbits.TRISC0 = 0;   // Motor IN1A
    TRISCbits.TRISC1 = 0;   // Motor IN1B
    TRISCbits.TRISC2 = 0;   // Motor IN2A
    TRISCbits.TRISC3 = 0;   // Motor IN2B
    TRISCbits.TRISC4 = 0;   // Motor PS
}

static void initInterrupt(void){
    // Interrupt setting
    INTCON = 0;                 // All clear
    RCONbits.IPEN = 0;          // Disable interrupt priority
    INTCONbits.INT0IE = 1;      // Enables the INT0 external interrupt
    INTCON2bits.INTEDG0 = 0;    // Interrupt on falling edge
    INTCONbits.GIE = 1;         // Enables all unmasked interrupts
}

