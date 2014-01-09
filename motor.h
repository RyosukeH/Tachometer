/* 
 * File:   motor.h
 * Author: MMH
 *
 * Created on 2014/01/08, 20:39
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif



// define
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
extern void mtrDriverActive(void);
extern void initMotorPhase(void);
extern void motorChange(char dir, unsigned char phase);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

