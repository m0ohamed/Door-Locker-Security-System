/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  DC Motor Driver
 *
 * *********************************************************************/

#ifndef DC_motor_H
#define DC_motor_H
#include "../MCAL/My_GPIO.h"
#include "../LIB/std_types.h"
//configuration of the motor
#define DC_MOTOR_FIRST_PORT_ID  PORTB_ID
#define DC_MOTOR_FIRST_PIN_ID   PIN0_ID

#define DC_MOTOR_SECOND_PORT_ID  PORTB_ID
#define DC_MOTOR_SECOND_PIN_ID   PIN1_ID

#define DC_MOTOR_E_PORT          PORTB_ID
#define DC_MOTOR_E_PIN           PIN3_ID
//enum for the state of motor
typedef enum{
	OFF,CW,A_CW
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif
