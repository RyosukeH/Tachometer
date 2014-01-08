/* 
 * File:   main.c
 * Author: MMH
 *
 * Created on 2013/12/26, 23:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>



/*
 * 
 */

// Configuration bits
#pragma config WDTEN = 0,  CONFIG1H = 0x48, CONFIG2L = 0x00, PBADEN = 0
//#pragma config CONFIG5L = 0x0f

// define
#define _XTAL_FREQ  64000000 // 64MHz

// motor
#define CW          1
#define CCW         0
#define STANDBY     0x00
#define EX1         0x11
#define EX2         0x15
#define EX3         0x14
#define EX4         0x16
#define EX5         0x12
#define EX6         0x1a
#define EX7         0x18
#define EX8         0x19




// Function prototype
static void initSystem(void);
static void initPortReg(void);
static void beforeInt(void);    // This Func called after everything is ready.

// motor
static void mtrDriverActive(void);
static void initMotorPhase(void);
static void motorChange(char dir, unsigned char phase);

// Global variables
unsigned char mtrPhase;


// Interrupt function
void interrupt myInt(void){

    if(INTCONbits.INT0IF){
        INTCONbits.INT0IE = 0;
        INTCONbits.INT0IF = 0;  // interrupt flag down
        INTCONbits.PEIE = 0;
        INTCONbits.GIE = 0;     // Disable all interrupt

        // test LED On Off
        PORTAbits.RA0 = ~PORTAbits.RA0;

        INTCONbits.INT0IE = 1;
        INTCONbits.PEIE = 1;
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

    // interrupt test
    beforeInt();
    ei();
    PORTAbits.RA0 = 1;

    while(1){

        //PORTAbits.RA0 = 1;
        //PORTC = 0x0f;

        // motor function test
        motorChange(CW, mtrPhase);
        for(i=0; i<100; i++){
            __delay_ms(1);
        }
        
        //PORTAbits.RA0 = 0;
        //PORTC = 0x00;

        // motor function test
        motorChange(CW, mtrPhase);
        for(i=0; i<100; i++){
            __delay_ms(1);
        }

        
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

static void beforeInt(void){
    // Interrupt setting
    INTCON = 0;                 // All clear
    RCONbits.IPEN = 0;
    INTCONbits.INT0IE = 1;
    //INTCONbits.INT0IF = 0;
    //INTCONbits.RBIE = 1;
    INTCON2bits.INTEDG0 = 1;    // Interrupt on rising edge
    //INTCON2bits.RBIP = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

static void mtrDriverActive(void){
    // Motor Driver Active
    PORTCbits.RC4 = 1;
    __delay_us(40);
}

static void initMotorPhase(void){
    // motor standby
    PORTC &= STANDBY;

    mtrPhase = EX1;
    // To assign an initial value
    PORTC |= mtrPhase;

}

static void motorChange(char dir, unsigned char phase){
    // direction = CW
    if(dir == CW){
        switch(phase){
            case EX1:
                mtrPhase = EX2;
                PORTC = mtrPhase;
                break;

            case EX2:
                mtrPhase = EX3;
                PORTC = mtrPhase;
                break;

            case EX3:
                mtrPhase = EX4;
                PORTC = mtrPhase;
                break;

            case EX4:
                mtrPhase = EX5;
                PORTC = mtrPhase;
                break;

            case EX5:
                mtrPhase = EX6;
                PORTC = mtrPhase;
                break;

            case EX6:
                mtrPhase = EX7;
                PORTC = mtrPhase;
                break;

            case EX7:
                mtrPhase = EX8;
                PORTC = mtrPhase;
                break;

            case EX8:
                mtrPhase = EX1;
                PORTC = mtrPhase;
                break;

            default:
                break;
        }
    }
    // direction = CCW
    else{
        switch(phase){
            case EX1:
                mtrPhase = EX8;
                PORTC = mtrPhase;
                break;

            case EX2:
                mtrPhase = EX1;
                PORTC = mtrPhase;
                break;

            case EX3:
                mtrPhase = EX2;
                PORTC = mtrPhase;
                break;

            case EX4:
                mtrPhase = EX3;
                PORTC = mtrPhase;
                break;

            case EX5:
                mtrPhase = EX4;
                PORTC = mtrPhase;
                break;

            case EX6:
                mtrPhase = EX5;
                PORTC = mtrPhase;
                break;

            case EX7:
                mtrPhase = EX6;
                PORTC = mtrPhase;
                break;

            case EX8:
                mtrPhase = EX7;
                PORTC = mtrPhase;
                break;

            default:
                break;
        }
    }
}

