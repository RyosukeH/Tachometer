#include <xc.h>
#include "globalDefine.h"
#include "motor.h"


void mtrDriverActive(void){
    // Motor Driver Active
    PORTCbits.RC4 = 1;
    __delay_us(40);
}

void initMotorPhase(void){
    // motor standby
    PORTC &= STANDBY;

    mtrPhase = EX1;
    // To assign an initial value
    PORTC |= mtrPhase;

}

void motorChange(char dir, unsigned char phase){
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