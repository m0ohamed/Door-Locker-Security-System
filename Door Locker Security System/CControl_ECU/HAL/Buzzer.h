/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Buzzer Driver
 *
 * *********************************************************************/
#ifndef BUZZER_H
#define BUZZER_H
#include "../MCAL/My_GPIO.h"
#include "../LIB/std_types.h"

#define BUZZER_PORT_ID          PORTA_ID
#define BUZZER_PIN_ID           PIN0_ID



void BuzzerInit(void);
void BuzzerOn(void);
void BuzzerOff(void);

#endif
