/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Timer1 Driver
 *
 * *********************************************************************/

#include "Timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*global variable to save the address of the call back function */
static void (*g_callBackPtr)(void) = Null_ptr;

/*ISR of timer 1 when overflow occurs */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != Null_ptr)
			{
				/* Call the Call Back function in the application */
				(*g_callBackPtr)();
			}
}


/*ISR of timer 1 when compare match occurs */

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != Null_ptr)
			{
				/* Call the Call Back function in the application */
				(*g_callBackPtr)();
			}
}




//initialization of timer 1 with overflow and compare match modes
void Timer1_Init(const Timer1_ConfigType *Config_Ptr)
{
	TCNT1 =(uint16)Config_Ptr->initial_value;//Put the initial value in TCNT1
	OCR1AL =(Config_Ptr->compare_value);//Put the compare value in OCR1A
	OCR1AH =((Config_Ptr->compare_value)>>8);//Put the compare value in OCR1A

	if((Config_Ptr->Mode)==Normal)//if overflow mode
	{
		TCCR1A=0x08;//WGM10 and WGM11 are cleared.... FOC1A and FOC1B set (Non-PWM Mode)
		TCCR1B=0x00;//WGM12 and WGM13 are cleared
		TCCR1B= (TCCR1B & 0xF8) | ((uint8)(Config_Ptr->prescaler));//put the value of prescaler in CS10 ,CS11 and CS12
		TIMSK |=(1<<TOIE1);//enable overflow interrupt
	}
	else if((Config_Ptr->Mode)==CTC)
	{
		TCCR1A=0x08;//WGM10 and WGM11 are cleared.... FOC1A and FOC1B set (Non-PWM Mode)
		TCCR1B=0x08;//WGM12=1 and WGM13 is cleared
		TCCR1B= (TCCR1B & 0xF8) | ((uint8)(Config_Ptr->prescaler));//put the value of prescaler in CS10 ,CS11 and CS12
		TIMSK |=(1<< OCIE1A);//enable compare match interrupt


	}
}

//stop the timer/counter
void Timer1_DeInit(void)
{
	TCCR1B=0;//No clock source
}


void Time1_SetCallBack(void (*a_Ptr) (void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr=a_Ptr;
}
