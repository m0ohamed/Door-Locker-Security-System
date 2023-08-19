/*
 * Author: Mohamed Khaled
 * Timer 1 Driver with Overflow and CTC modes
 * */
#ifndef TIMER1_H
#define TIMER1_H

#include "../LIB/std_types.h"

/************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 Configuration
 ************************************************************************************************************/

//value of prescaler
typedef enum
{
	NoClock,No_prescaler,FCPU_8,FCPU_16,FCPU_256,FCPU_1024,EX_Falling,EX_Rising
}Timer1_prescaler;

/*
 * 01- 0.........OverFlow mode
 * 02- 1.........Compare match mode
 * */
typedef enum
{
	Normal,CTC
}Timer1_Mode;


/*
 * initial value= the value in TCNT1
 * copmare value= the value in OCR1A
 * prescaler    = the value from Timer1_prescaler enum
 * Mode         = the value from Timer1_Mode enum */


typedef struct
{
uint16 initial_value;
uint16 compare_value;
Timer1_prescaler prescaler;
Timer1_Mode Mode;
}Timer1_ConfigType;




/************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 Function Prototypes
 ************************************************************************************************************/

void Timer1_Init(const Timer1_ConfigType *Config_Ptr);
void Timer1_DeInit(void);
void Time1_SetCallBack(void (*a_Ptr) (void));








#endif
