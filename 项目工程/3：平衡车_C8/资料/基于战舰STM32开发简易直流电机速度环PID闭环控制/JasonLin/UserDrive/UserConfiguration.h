#ifndef __USER_H
#define __USER_H

#define PWMPeriod   10000

#define MotorOneForward  0
#define MotorTwoForward  0
#define MotorOneBack     1
#define MotorTwoBack     1
#define MotorSpdZero     0

extern void UserTIM_Configuration(void);
extern void UserNVIC_Configuration(void);

extern void UserMotorSpeedSetOne(s32 MotorSpeed);
extern void UserMotorSpeedSetTwo(s32 MotorSpeed);
extern void UserMotorSpeedSetThr(s32 MotorSpeed);
extern void UserMotorSpeedSetFou(s32 MotorSpeed);

#endif


















