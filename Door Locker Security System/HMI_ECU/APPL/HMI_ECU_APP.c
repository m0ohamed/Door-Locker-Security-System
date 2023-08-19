/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  AppL for HMI_MCU (Human interface Micro_controller unit)
 *
 * *********************************************************************/


/*****************************************************************************************
							    Preprocessor '#'
 *****************************************************************************************/

#include "../HAL/LCD.h"
#include "../HAL/My_keypad.h"
#include "../MCAL/uart.h"
#include <util/delay.h>
#include <avr/io.h>
#include "../MCAL/Timer1.h"
////////////////////////////////////////////////

#define Arr_Size   5// Arr_Size of array

/*****************************************************************************************
							    Global variables
 *****************************************************************************************/

static uint8 step=0;//variable to control the steps

//Timer object 'timer'
//initial value of the timer counter is 50000
//compare value of timer counter is     0
//prescaler of timer                    1024
//timer mode                            Normal(overflow mode)
Timer1_ConfigType timer={50000,0,FCPU_1024,Normal};

uint8 TFlag=0;//timer callback functions flag
uint8 arr_pass[Arr_Size]={0,0,0,0,0};//password
uint8 arr_confirm[Arr_Size]={0,0,0,0,0};//confirm password
uint8 arr_eeprom[Arr_Size]={0,0,0,0,0};//password to compare with the eeprom password


/*****************************************************************************************
 	 	 	 	 	 	 	 	 function prototypes
 *****************************************************************************************/

//check the key, fill arr_pass[] array and return 1-the key is valid display '*'  2-the user submit and the number not valid display error  3-the user submit and the pass is valid
uint8 First_Pass(uint8 key);

//check the key, fill arr_confirm[] array and return 1-the key is valid display '*'  2-the user submit and the number not valid display error  3-the user submit and the pass is valid

uint8 Confirm_Pass(uint8 key);

//check the key, fill arr_eeprom[] array and return 1-the key is valid display '*'  2-the user submit and the number not valid display error  3-the user submit and the pass is valid

uint8 eeprom_pass(uint8 key);

/*****************************************************************************************
 	 	 	 	 	 	 	 	  callback functions
 *****************************************************************************************/

/*
 * Timer is a callback function
 * used to tell the Control_MCU to turn off buzzer
 * and return to the normal flow of step 3 the main page
 * */
void Timer(void)
{//start Timer
	TFlag++;//increment TFlag to count 1 minute
	if(TFlag==2)//when TFlag =2
	{//start if TFlag =2
		UART_sendByte(5);//make Control_MCU to execute step 5
		_delay_ms(20);//some time to send the next byte
		UART_sendByte(2);//make the Control_MCU turn off the buzzer
		LCD_clearScreen();//clear the screen
		step=3;//return to step 3
		Timer1_DeInit();//stop the timer
		TFlag=0;//reset TFlag to the next time
	}//end of the if TFlag=2
}//end of timer


/*
 * timer_function is a callback function
 * used Display error message and to tell the Control_MCU to turn ON buzzer
 * and return to the normal flow of step 0 nothing to do during the error message
 * */

void timer_function(void)
{//start timer_function
	timer.initial_value=0;//set the initial value of the timer counter to 0
	UART_sendByte(5);////make Control_MCU to execute step 5
	_delay_ms(20);//some time to send the next byte
	UART_sendByte(1);//make the Control_MCU turn ON the buzzer
	LCD_clearScreen();//clear the screen
	LCD_displayStringRowColumn(0,3,"ERROR...");//display first message on screen
	_delay_ms(100);
	step=0;//return to the normal flow of step 0 nothing to do during the error message
	Time1_SetCallBack(Timer);//call Timer function the next overflow
}//end of timer_function

/******************************************************************************************
 	 	 	 	 	 	 	     main Function
 ******************************************************************************************/

int main(void)
{ //start main
	/***************************************initializations***************************************************/
	SREG |=(1<<7);//enable global interrupt
	uint8 /*PIRto check PIR sensor,*/ counter=0/*count the number of times the password was incorrect */;
	uint8 flag=0/*//to control LCD once display*/,flag2=0/*to control LCD in switch + - statement*/,key=0/*the number from key pad  */,key1=0/*store the number for switch + - statement*/,ret/*return value from function*/,i/*for loop*/,ret2/*return value from control MCU*/;
	LCD_init();//initialize LCD
	UART_ConfigType uart={_8_Bit_Mode,Disabled,_1_Stop_Bit,Rate3};//configuration of uart with 8 bit character Arr_Size ,1 stop bit ,no parity bit and Baud rate 9600
	UART_init(&uart);//initialize UART with the address of uart object
	Time1_SetCallBack(timer_function);//set the callback pointer to timer_function
	step=1;//start system
	/***********************************************Super Loop************************************************/
	while(1)
	{//super loop start

		/////////////////////////////////////////////////////////////////////////////////////////////////////////


			switch(step)//start system step switch
			{//start step switch

			/////////////////////////////////"step 1"////////////////////////////////////////////////

			case 1://case step 1
				//////////////////////

				if(flag==0)//display the message once
				{//start if flag
					LCD_clearScreen();//clear the screen
					LCD_displayStringRowColumn(0,0,"Plz enter Pass:");//display first message on screen
					LCD_moveCursor(1,0);//move the cursor to the second row
					flag=1;//do not get here again
				}//end if flag

				//////////////////////

				key=KEYPAD_getPressedKey();//get numbers from user
				_delay_ms(200);
				ret=First_Pass(key);//check the return
				//////////////////////

				if(ret==1)//if the key between 0 and 9 and array still not full
				{//start if ret =1
					LCD_sendString("*");//display '*'
				}//end if ret =1

				//////////////////////

				else if(ret==2)//if the user submit but and array still not full
				{//start if ret= 2
					LCD_displayStringRowColumn(1,0,"               ");//clear row two
					LCD_displayStringRowColumn(1,0,"Error pass");//display Error message
					_delay_ms(150);//delay to make the user see the error
					LCD_displayStringRowColumn(1,0,"               ");//clear row two
					LCD_moveCursor(1,0);//move the cursor to the second row
				}//end if ret= 2

				//////////////////////

				else if(ret==3)//if the user submit and the pass is valid
				{//start if ret==3
					UART_sendByte(step);//send our step to Control_MCU
					_delay_ms(5);//wait to send data

					for(i=0;i<(Arr_Size-1);i++)//loop in arr_pass and send the elements to control MCU
					{//start for arr_pass
						UART_sendByte(arr_pass[i]);//send the password to control_MCU
						_delay_ms(20);//wait to send data
					}//end for arr_pass

					step=2;//go to step 2
					flag=0;//to enable displaying on screen

				}//end if ret =3
				///////////////////////

				break;//break case step 1

				/////////////////////////////////////case 2///////////////////////////////////////////

			case 2: //case step 2
				//////////////////////

				if(flag==0)//display the message once
				{//start if flag=1
					LCD_clearScreen();//clear the screen
					LCD_displayStringRowColumn(0,0,"confirm Pass:");//display first message on screen
					LCD_moveCursor(1,0);//move the cursor to the second row
					flag=1;//do not get here again
				}//end if flag
				//////////////////////

				key=KEYPAD_getPressedKey();//get numbers from user
				_delay_ms(200);

				ret=Confirm_Pass(key);//check the return

				//////////////////////

				if(ret==1)//if the key between 0 and 9 and array still not full
				{//start if ret =1
					LCD_sendString("*");//display '*'
				}//end if ret =1

				//////////////////////

				else if(ret==2)//if the user submit but and array still not full
				{//start if ret= 2
					LCD_displayStringRowColumn(1,0,"               ");//clear row two
					LCD_displayStringRowColumn(1,0,"Error pass");//display Error message
					_delay_ms(150);//delay to make the user see the error
					LCD_displayStringRowColumn(1,0,"               ");//clear row two
					LCD_moveCursor(1,0);//move the cursor to the second row
				}//end if ret= 2

				//////////////////////

				else if(ret==3)//if the user submit and the pass is valid
				{//start if ret==3

					UART_sendByte(step);//send our step to Control_MCU
					_delay_ms(5);//wait to send data

					//-------------------

					for(i=0;i<(Arr_Size-1);i++)//loop in arr_pass and send the elements to control MCU
					{//start for arr_pass
						UART_sendByte(arr_confirm[i]);//send the password to control_MCU
						_delay_ms(20);//wait to send data
					}//end for arr_pass

					//--------------------

					ret2=UART_recieveByte();

					if(ret2)//if the received number from Control_MCU is true
					{//start if //if the received number from Control_MCU is true

						step=3;//go to step 3
						flag=0;//to enable displaying
					}//end of //if the received number from Control_MCU is true

					else//if the received number from Control_MCU is False
					{//start of //if the received number from Control_MCU is False
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"pass not match");//display first message on screen
						_delay_ms(250);//delay to make user see teh message
						step=1;//go to step 1
						flag=0;//enable displaying
					}//end of //if the received number from Control_MCU is False

				}//end if ret =3
				break;//break case step 2

				/////////////////////////////////case 3////////////////////////////////////////////

			case 3://step 3 start
				//////////////////////

				if(flag==0)//display the message once
				{//start if flag=1
					LCD_clearScreen();//clear the screen
					LCD_displayStringRowColumn(0,0,"+ :Open Door");//display first message on screen
					LCD_displayStringRowColumn(1,0,"- :change pass");//display first message on screen
					key1=KEYPAD_getPressedKey();//get numbers from user
					_delay_ms(200);
					flag=1;//do not get here again
				}//end if flag

				//////////////////////

				switch(key1)//check if key = '+' or '-'
				{//start switch key
				////////////////////case 1 switch key////////////////////////////////

				case '+'://case + open door

					///////////////////////////////////////////////////////


					if(flag2==0)//display the message once
					{//start if flag
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"Plz enter Pass:");//display first message on screen
						LCD_moveCursor(1,0);//move the cursor to the second row
						flag2=1;//do not get here again
					}//end if flag

					//////////////////////

					key=KEYPAD_getPressedKey();//get numbers from user
					_delay_ms(200);

					ret=eeprom_pass(key);//check the return
					//////////////////////

					if(ret==1)//if the key between 0 and 9 and array still not full
					{//start if ret =1
						LCD_sendString("*");//display '*'
					}//end if ret =1

					//////////////////////

					else if(ret==2)//if the user submit but and array still not full
					{//start if ret= 2
						LCD_displayStringRowColumn(1,0,"               ");//clear row two
						LCD_displayStringRowColumn(1,0,"Error pass");//display Error message
						_delay_ms(150);//delay to make the user see the error
						LCD_displayStringRowColumn(1,0,"               ");//clear row two
						LCD_moveCursor(1,0);//move the cursor to the second row
					}//end if ret= 2

					//////////////////////

					else if(ret==3)//if the user submit and the pass is valid
					{//start if ret==3
						UART_sendByte(step);//send our step to Control_MCU
						_delay_ms(50);//wait to send data

						for(i=0;i<(Arr_Size-1);i++)//loop in arr_pass and send the elements to control MCU
						{//start for arr_pass
							UART_sendByte(arr_eeprom[i]);//send the password to control_MCU
							_delay_ms(20);//wait to send data
						}//end for arr_pass
						_delay_ms(20);//wait to send data

						ret2=UART_recieveByte();//take the result of comparison
						//////////////////////

						if(ret2==1)//if the password match
						{//start if the password match
							_delay_ms(20);//wait to send data
							UART_sendByte(4);
							step =4;//go to step 4 to open the motor
							flag=0;//enable displaying to display Door Unlocking
							flag2=0;
						}//end if the password match
						//////////////////////

						else//if the password not match
						{//start if password not match

							if(counter<2)
							{
								UART_sendByte(3);//sent 3 to the control_MCU
								step=3;//stay in step 3
								flag2=0;//dispaly "plz enter pass:"
								counter++;//count the number of consecutive incorrect password
							}

							else if(counter==2)//if the counter =3
							{//start if counter ==3
								UART_sendByte(0);//sent 0 to the control_MCU to to turn on buzzer
								_delay_ms(20);
								Time1_SetCallBack(timer_function);//set the callback to the timer_function
								Timer1_Init(&timer);//start the timer
								LCD_clearScreen();//clear the screen
								LCD_displayStringRowColumn(0,3,"ERROR...");//display Error message
								step=0;//stay and display the main window
								flag=0;//to enable displaying
								flag2=0;//to enable displaying
								counter=0;//reset the counter
								_delay_ms(2000);
							}//end if counter =3
						}//end else ret2
					}//end if ret =3

					/////////////////////////////////////////////////////
					////////////////////////////////////////////////////

					break;//break case +
					////////////////////case 2 switch key///////////////////////////////

				case '-'://case - change password

					/////////////////////////////////////////////////
					////////////////////////////////////////////////
					if(flag2==0)//display the message once
					{//start if flag
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"Plz enter Pass:");//display first message on screen
						LCD_moveCursor(1,0);//move the cursor to the second row
						flag2=1;//do not get here again
					}//end if flag

					////////////////////////

					key=KEYPAD_getPressedKey();//get numbers from user
					_delay_ms(200);

					ret=First_Pass(key);//check the return
					/////////////ret1

					if(ret==1)//if the key between 0 and 9 and array still not full
					{//start if ret =1
						LCD_sendString("*");//display '*'
					}//end if ret =1

					//////////////////ret 2

					else if(ret==2)//if the user submit but and array still not full
					{//start if ret= 2
						LCD_displayStringRowColumn(1,0,"               ");//clear row two
						LCD_displayStringRowColumn(1,0,"Error pass");//display Error message
						_delay_ms(150);//delay to make the user see the error
						LCD_displayStringRowColumn(1,0,"               ");//clear row two
						LCD_moveCursor(1,0);//move the cursor to the second row
					}//end if ret= 2

					//////////////////

					else if(ret==3)//if the user submit and the pass is valid
					{//start if ret==3
						UART_sendByte(step);//send our step to Control_MCU
						_delay_ms(50);//wait to send data

						for(i=0;i<(Arr_Size-1);i++)//loop in arr_pass and send the elements to control MCU
						{//start for arr_pass
							UART_sendByte(arr_pass[i]);//send the password to control_MCU
							_delay_ms(20);//wait to send data
						}//end for arr_pass
						////////////////////////////////////////////////////////////////////////////////////////////

						ret2=UART_recieveByte();//if the password match return ret2
						/////////////////////////

						if(ret2==1)//if the password match
						{//start if the password match
							UART_sendByte(1);
							step =1;//go to step 4 to open the motor
							flag=0;//enable displaying to display Door Unlocking
							flag2=0;
						}//end if the password match
						/////////////////////

						else//if the password not match
						{//start if password not match

							if(counter<2)
							{
								UART_sendByte(3);
								step=3;//stay in step 3
								flag2=0;//dispaly "plz enter pass:"
								counter++;//count the number of consecutive incorrect password
							}

							else if(counter==2)//if the counter =3
							{//start if counter ==3
								UART_sendByte(0);//sent 0 to the control_MCU to to turn on buzzer
								_delay_ms(20);
								Time1_SetCallBack(timer_function);//set the callback function to timer_function
								Timer1_Init(&timer);//start the timer
								LCD_clearScreen();//clear the screen
								LCD_displayStringRowColumn(0,3,"ERROR...");//display Error message
								step=0;//stay and display the main window
								flag=0;//to enable displaying
								flag2=0;//to enable displaying
								counter=0;//reset the counter
								_delay_ms(2000);
							}//end if counter =3
						}//end else ret2

						/////////////////////////////////////////////////////////////////////////////////////////////////


					}//end if ret =3
					///////////////////////////////////////////////
					//////////////////////////////////////////////

					break;//break case -

					/////////////////////////////////////////////////////
				default ://if the key invalid
					flag=0;//enable displaying
				}//end switch key
				//////////////////////////////////////////////////////////////////////////
				break;//step 3 break

				//////////////////////////////
				/////////////////////////////

				case  4 ://case 4 if the password match
					/////////////////////////////////

					ret2=UART_recieveByte();//take the what should i do number

					if(ret2==1)//if the DCmotor start Unlocking
					{
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"DOOR Unlocking");//display Unlocking message
					}

					else if(ret2==2)//if the DCmotor start Holding
					{
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"DOOR Holding");//display Holding message
					}

					else if(ret2==3)//if the DCmotor start locking
					{
						LCD_clearScreen();//clear the screen
						LCD_displayStringRowColumn(0,0,"DOOR Locking");//display locking message
					}

					else if (ret2==4)//if the the DC motor finish its work
					{
						step=3;//return to the main page again
					}


					break;//case 4 break

			}//end step switch

		///////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////

	}//end of super loop

}//main  end





/*************************************************************************************************
 * 											Function Body
 * **********************************************************************************************/
uint8 First_Pass(uint8 key)//function to check the key and fill arr_pass[]
{//start First_pass function
	uint8 ret=0/*carries the return value */;
	static uint8 i=0/*carries the index of array */;
	if(i>(Arr_Size)){i=0;}//if i higher than Arr_Size of array then i =0
	///////////////////////////////////////////////////////////////////////////

	if(key >=0 && key<=9)//if key between 0 and 9 is a valid number
	{//start if key
		if(i<(Arr_Size))//check the index is valid or not
		{//start if i
			arr_pass[i]=key;//if valid store it
			i++;//increment index
			ret=1;//return 1
		}//end if i

		else//if i not valid
		{//start else i
			return 0;//return error
		}//end else i
	}//end if key

	/////////////////////////////////////////////////////////////////

	else if (key==13 && (i<(Arr_Size) || i>Arr_Size))//if user submit but the password lower than 5 digits
	{//start else if password lower than 5 digits
		ret=2;//return 2
		i=0;//start again
	}//end else if password lower than 5 digits

	/////////////////////////////////////////////////////////////////

	else if(key==13 && (i==(Arr_Size)))////if user submit and the password equal 5 digits
	{//start if //if user submit but the password lower than 5 digits
		ret=3;//return 3
		i=0;//start again
	}//end if //if user submit but the password lower than 5 digits
	//////////////////////////////////////////////////////////////////
	return ret;//return ret
}
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
uint8 Confirm_Pass(uint8 key)
{
	uint8 ret=0/*carries the return value */;
	static uint8 i=0/*carries the index of array */;
	if(i>(Arr_Size)){i=0;}//if i higher than Arr_Size of array then i =0
	///////////////////////////////////////////////////////////////////////////

	if(key >=0 && key<=9)//if key between 0 and 9 is a valid number
	{//start if key
		if(i<(Arr_Size))//check the index is valid or not
		{//start if i
			arr_confirm[i]=key;//if valid store it
			i++;//increment index
			ret=1;//return 1
		}//end if i

		else//if i not valid
		{//start else i
			return 0;//return error
		}//end else i
	}//end if key

	/////////////////////////////////////////////////////////////////

	else if (key==13 && (i<(Arr_Size) || i>Arr_Size))//if user submit but the password lower than 5 digits
	{//start else if password lower than 5 digits
		ret=2;//return 2
		i=0;//start again
	}//end else if password lower than 5 digits

	/////////////////////////////////////////////////////////////////

	else if(key==13 && (i==(Arr_Size)))////if user submit and the password equal 5 digits
	{//start if //if user submit but the password lower than 5 digits
		ret=3;//return 3
		i=0;//start again
	}//end if //if user submit but the password lower than 5 digits
	//////////////////////////////////////////////////////////////////
	return ret;//return ret
}




uint8 eeprom_pass(uint8 key)
{
	uint8 ret=0/*carries the return value */;
	static uint8 i=0/*carries the index of array */;
	if(i>(Arr_Size)){i=0;}//if i higher than Arr_Size of array then i =0
	///////////////////////////////////////////////////////////////////////////

	if(key >=0 && key<=9)//if key between 0 and 9 is a valid number
	{//start if key
		if(i<(Arr_Size))//check the index is valid or not
		{//start if i
			arr_eeprom[i]=key;//if valid store it
			i++;//increment index
			ret=1;//return 1
		}//end if i

		else//if i not valid
		{//start else i
			return 0;//return error
		}//end else i
	}//end if key

	/////////////////////////////////////////////////////////////////

	else if (key==13 && (i<(Arr_Size) || i>Arr_Size))//if user submit but the password lower than 5 digits
	{//start else if password lower than 5 digits
		ret=2;//return 2
		i=0;//start again
	}//end else if password lower than 5 digits

	/////////////////////////////////////////////////////////////////

	else if(key==13 && (i==(Arr_Size)))////if user submit and the password equal 5 digits
	{//start if //if user submit but the password lower than 5 digits
		ret=3;//return 3
		i=0;//start again
	}//end if //if user submit but the password lower than 5 digits
	//////////////////////////////////////////////////////////////////
	return ret;//return ret
}
