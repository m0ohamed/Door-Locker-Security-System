/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  GPIO Driver
 *
 * *********************************************************************/


//guard
#ifndef GPIO_H
#define GPIO_h

#include "../LIB/std_types.h"

#define NUMBER_OF_PORTS     4
#define NUMBER_OF_PINS      8

//ports ID
#define PORTA_ID            0
#define PORTB_ID            1
#define PORTC_ID            2
#define PORTD_ID            3

//pins ID
#define PIN0_ID             0
#define PIN1_ID             1
#define PIN2_ID             2
#define PIN3_ID             3
#define PIN4_ID             4
#define PIN5_ID             5
#define PIN6_ID             6
#define PIN7_ID             7


//pin Direction enum



//pin direction
void SetupPinDirection(uint8 port_num,uint8 pin_num,uint8 direction);
//write pin
void Write_Pin(uint8 port_num ,uint8 pin_num ,uint8 value);
//read pin
uint8 Read_Pin(uint8 port_num ,uint8 pin_num);
//port direction
void SetupPortDirection(uint8 port_num ,uint8 direction);
//write port
void Write_Port(uint8 port_num ,uint8 value);
//read port
uint8 Read_Port(uint8 port_num);

//endif
#endif
