 /***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  UART driver HMI MCU
 *
 * *********************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../LIB/std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

//Disable or Enable(Even-Odd) Parity Bit
typedef enum
{
	Disabled,Even_Parity=2,Odd_Parity
}UART_Parity;

//choose 1 or 2 Stop Bits
typedef enum
{
	_1_Stop_Bit,_2_Stop_Bits
}UART_StopBit;

//character size 5,6,7,8 or 9
typedef enum
{
	_5_Bit_Mode,_6_Bit_Mode,_7_Bit_Mode,_8_Bit_Mode,_9_Bit_Mode=7
}UART_BitData;

typedef enum{
	RATE1=2400,RAte2=4800,Rate3=9600,Rate4=14400,Rate5=19200
}UART_BuadRate;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity Parity;
	UART_StopBit Stop_Bit;
	UART_BuadRate BaudeRate;
}UART_ConfigType;
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
