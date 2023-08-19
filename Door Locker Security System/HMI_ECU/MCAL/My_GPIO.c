/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  GPIO driver HMI MCU
 *
 * *********************************************************************/

#include "../LIB/common_macros.h"
#include "../LIB/std_types.h"
#include "avr/io.h"
#include "My_GPIO.h"

//pin input or output direction
//if number of port or the number of pins invalid ,do nothing
void SetupPinDirection(uint8 port_num,uint8 pin_num,uint8 direction)
{
	if((port_num>=NUMBER_OF_PORTS) && (pin_num>=NUMBER_OF_PINS))
	{
		//do nothing
	}
	switch(port_num)
	{
	case PORTA_ID:
		if(direction==OUTPUT_PIN)
		{
		SET_BIT(DDRA,pin_num);
		}
		else
		{
			CLEAR_BIT(DDRA,pin_num);
		}
		break;
	case PORTB_ID:
		if(direction==OUTPUT_PIN)
				{
				SET_BIT(DDRB,pin_num);
				}
				else
				{
					CLEAR_BIT(DDRB,pin_num);
				}
		break;
	case PORTC_ID:
		if(direction==OUTPUT_PIN)
						{
						SET_BIT(DDRC,pin_num);
						}
						else
						{
							CLEAR_BIT(DDRC,pin_num);
						}
		break;
	case PORTD_ID:
		if(direction==OUTPUT_PIN)
						{
						SET_BIT(DDRD,pin_num);
						}
						else
						{
							CLEAR_BIT(DDRD,pin_num);
						}
		break;
	}
}

//pin HIGH or LOW direction
//if number of port or the number of pins invalid ,do nothing
void Write_Pin(uint8 port_num ,uint8 pin_num ,uint8 value)
{
	if((port_num>=NUMBER_OF_PORTS) && (pin_num>=NUMBER_OF_PINS))
	{
		//do nothing
	}
	switch(port_num)
	{
	case PORTA_ID:
		if(value==LOGIC_HIGH)
		{	SET_BIT(PORTA,pin_num);}
		else{CLEAR_BIT(PORTA,pin_num);}
		break;
	case PORTB_ID:
		if(value==LOGIC_HIGH)
		{	SET_BIT(PORTB,pin_num);}
		else{CLEAR_BIT(PORTB,pin_num);}
		break;
	case PORTC_ID:
		if(value==LOGIC_HIGH)
		{	SET_BIT(PORTC,pin_num);}
		else{CLEAR_BIT(PORTC,pin_num);}
		break;
	case PORTD_ID:
		if(value==LOGIC_HIGH)
		{	SET_BIT(PORTD,pin_num);}
		else{CLEAR_BIT(PORTD,pin_num);}
		break;
	}
}
//return the value of pin_num
//if number of port or the number of pins invalid ,return 0
uint8 Read_Pin(uint8 port_num ,uint8 pin_num)
{

	uint8 pinvalue=0;
	if((port_num>=NUMBER_OF_PORTS) && (pin_num>=NUMBER_OF_PINS))
	{
		//do nothing
	}
	switch(port_num)
	{
	case PORTA_ID:
		if(BIT_IS_SET(PINA,pin_num)){pinvalue=1;}
		break;
	case PORTB_ID:
		if(BIT_IS_SET(PINB,pin_num)){pinvalue=1;}
		break;
	case PORTC_ID:
		if(BIT_IS_SET(PINC,pin_num)){pinvalue=1;}
		break;
	case PORTD_ID:
		if(BIT_IS_SET(PIND,pin_num)){pinvalue=1;}
		break;
	}
	return pinvalue;
}

//port input or output direction
//if number of port invalid ,do nothing
void SetupPortDirection(uint8 port_num ,uint8 direction)
{
	if((port_num>=NUMBER_OF_PORTS))
	{
		//do nothing
	}

	switch(port_num)
	{
	case PORTA_ID:
		DDRA=direction;
		break;
	case PORTB_ID:
		DDRB=direction;
		break;
	case PORTC_ID:
		DDRC=direction;
		break;
	case PORTD_ID:
		DDRD=direction;
		break;
	}
}

//port HIGH or LOW
//if number of port invalid ,do nothing
void Write_Port(uint8 port_num ,uint8 value)
{
	if((port_num>=NUMBER_OF_PORTS))
	{
		//do nothing
	}

	switch(port_num)
	{
	case PORTA_ID:
		PORTA=value;
		break;
	case PORTB_ID:
		PORTB=value;
		break;
	case PORTC_ID:
		PORTC=value;
		break;
	case PORTD_ID:
		PORTD=value;
		break;
	}
}

//return the vlaue of port
//if number of port invalid ,return 0
uint8 Read_Port(uint8 port_num)
{
	uint8 portvalue=0;
	if((port_num>=NUMBER_OF_PORTS))
	{
		//do nothing
	}
	switch(port_num)
	{
	case PORTA_ID:
		portvalue=PINA;
		break;
	case PORTB_ID:
		portvalue=PINB;
		break;
	case PORTC_ID:
		portvalue=PINC;
		break;
	case PORTD_ID:
		portvalue=PIND;
		break;
	}
	return portvalue;
}
