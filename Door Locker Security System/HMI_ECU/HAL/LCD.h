/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  LCD Driver
 *
 * *********************************************************************/

#ifndef  LCD_H
#define  LCD_H

#include "../MCAL/My_GPIO.h"
#include "../LIB/std_types.h"
#define LCD_DATA_BITS_MODE 8
#if ((LCD_DATA_BITS_MODE !=4) && (LCD_DATA_BITS_MODE!=8))
#error "LCD_DATA_BITS_MODE should be 4 or 8"
#endif

#define LCD_E_BIT_PORT_ID            PORTC_ID
#define LCD_E_BIT_PIN_ID             PIN2_ID

#define LCD_RS_BIT_PORT_ID            PORTC_ID
#define LCD_RS_BIT_PIN_ID             PIN1_ID

#define DATA_BUS_PORT_ID              PORTA_ID
#if (LCD_DATA_BITS_MODE==4)
#define LCD_DATA_BUS_4BITMODE_PIN0_ID   PIN2_ID
#define LCD_DATA_BUS_4BITMODE_PIN1_ID   PIN3_ID
#define LCD_DATA_BUS_4BITMODE_PIN2_ID   PIN4_ID
#define LCD_DATA_BUS_4BITMODE_PIN3_ID   PIN5_ID
#endif
/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80
//LCD init
void LCD_init(void);
//send command
void LCD_sendCommand (uint8 command);
//send character
void LCD_sendCharacter (uint8 character);
//LCD send string
void LCD_sendString(const char *ptr);
//LCD move cursor
void LCD_moveCursor(uint8 row,uint8 col);

//LCD send string row col

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

//itoa
void LCD_intgerToString(int data);

//LCD clear screen
void LCD_clearScreen(void);

#endif /* LCD_H_ */
