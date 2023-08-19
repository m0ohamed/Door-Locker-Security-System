/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  PWM Timer0 Driver
 *
 * *********************************************************************/

#ifndef PWM_H
#define PWM_H
#include "../LIB/std_types.h"
#include "My_GPIO.h"
//configuration of PWM
#define PWM_PORT_ID   PORTB_ID
#define PWM_PIN_ID    PIN3_ID


void PWM_Timer0_START(unsigned char set_duty_cycle);


#endif
