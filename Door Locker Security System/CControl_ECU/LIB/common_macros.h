/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Library file
 *
 * *********************************************************************/


#include "std_types.h"

// guard
#ifndef common_macros
#define common_macros

//set_bit
#define SET_BIT(REG,BIT)      (REG = REG | (1<<BIT))

//clear bit
#define CLEAR_BIT(REG,BIT)    (REG = REG & (~(1<<BIT)))

//toggle bit
#define TOGGLE_BIT(REG,BIT)   (REG = REG ^ (1<<BIT))

//check if bit is set
#define BIT_IS_SET(REG,BIT)   (REG & (1<<BIT))

//check if bit is clear
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

//rotate to left
#define ROL(REG,num)          (REG = (REG<<num) | (REG>>(num-8))

//rotate to right
#define ROR(REG,num)          (REG = (REG>>num) | (REG<<(num-8)))
#define GET_BIT(REG,BIT_NUM) ( ( REG & (1<<BIT_NUM) ) >> BIT_NUM )

//endif
#endif
