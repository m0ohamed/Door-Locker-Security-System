/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  LCD Driver
 *
 * *********************************************************************/

#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"
#include "LCD.h"
#include <util/delay.h>
#include <stdlib.h>

#include "../MCAL/My_GPIO.h"
void LCD_init(void)
{
	SetupPinDirection(LCD_RS_BIT_PORT_ID,LCD_RS_BIT_PIN_ID,OUTPUT_PIN);
	SetupPinDirection(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,OUTPUT_PIN);
	_delay_ms(20);
#if (LCD_DATA_BITS_MODE==4)
	SetupPinDirection(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN0_ID,OUTPUT_PIN);
	SetupPinDirection(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN1_ID,OUTPUT_PIN);
	SetupPinDirection(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN2_ID,OUTPUT_PIN);
	SetupPinDirection(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN3_ID,OUTPUT_PIN);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#elif (LCD_DATA_BITS_MODE==8)
	SetupPortDirection(DATA_BUS_PORT_ID,OUTPUT_PORT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}



void LCD_sendCommand (uint8 command)
{
	Write_Pin(LCD_RS_BIT_PORT_ID,LCD_RS_BIT_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE==4)
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN0_ID,GET_BIT(command,4));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN1_ID,GET_BIT(command,5));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN2_ID,GET_BIT(command,6));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN3_ID,GET_BIT(command,7));
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN0_ID,GET_BIT(command,0));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN1_ID,GET_BIT(command,1));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN2_ID,GET_BIT(command,2));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN3_ID,GET_BIT(command,3));
_delay_ms(1);
Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
#elif (LCD_DATA_BITS_MODE==8)
Write_Port(DATA_BUS_PORT_ID,command);
Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
#endif
}
void LCD_sendCharacter (uint8 character)
{
	Write_Pin(LCD_RS_BIT_PORT_ID,LCD_RS_BIT_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE==4)
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN0_ID,GET_BIT(character,4));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN1_ID,GET_BIT(character,5));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN2_ID,GET_BIT(character,6));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN3_ID,GET_BIT(character,7));
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN0_ID,GET_BIT(character,0));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN1_ID,GET_BIT(character,1));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN2_ID,GET_BIT(character,2));
	Write_Pin(DATA_BUS_PORT_ID,LCD_DATA_BUS_4BITMODE_PIN3_ID,GET_BIT(character,3));
_delay_ms(1);
Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
#elif (LCD_DATA_BITS_MODE==8)
Write_Port(DATA_BUS_PORT_ID,character);
Write_Pin(LCD_E_BIT_PORT_ID,LCD_E_BIT_PIN_ID,LOGIC_LOW);
#endif
}


void LCD_sendString(const char *sptr)
{
	while(*sptr!='\0')
	{
		LCD_sendCharacter(*sptr);
		sptr++;
	}
}
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_sendString(Str); /* display the string */
}
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_sendString(buff); /* Display the string */
}
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

