/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Keypad Driver
 *
 * *********************************************************************/

#include "../LIB/std_types.h"
#ifndef my_keypad
#define my_keypad



//#define STANDARD_KEYPAD


#define NUM_OF_ROWS                     4
#define NUM_OF_COL                      4


#define KEYPAD_ROWS_ID                  PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID         PIN0_ID

#define KEYPAD_COLS_ID                  PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID         PIN4_ID



#define KEYPAD_BUTTON_PRESSED           LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED          LOGIC_HIGH



uint8 KEYPAD_getPressedKey(void);
#endif
