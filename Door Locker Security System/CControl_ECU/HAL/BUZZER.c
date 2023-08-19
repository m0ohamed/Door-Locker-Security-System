/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Buzzer Driver
 *
 * *********************************************************************/

#include "BUZZER.h"

void BuzzerInit(void)
{
	SetupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,OUTPUT_PIN);
	Write_Pin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

void BuzzerOn(void)
{
	Write_Pin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);

}
void BuzzerOff(void)
{
	Write_Pin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

}
