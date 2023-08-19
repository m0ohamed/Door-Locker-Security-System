/***********************************************************************
 *
 *  Author  : Mohamed khaled
 *  Project : Door Locker system
 *  Library file
 *
 * *********************************************************************/

//guard
#ifndef std_types
#define std_types
typedef unsigned char               boolean;

#ifndef         True
#define         True                (1u)
#endif
#ifndef         False
#define         False               (0u)
#endif
//define HIGH and LOW signals
#define         LOGIC_HIGH          (1u)
#define         LOGIC_LOW           (0u)
//define null pointer
#define         Null_ptr            ((void* )0)
//define data types
typedef         unsigned char       uint8;   // 255<<<<<<<<0
typedef         signed char         sint8;   // 127<<<<<<<<<-128
typedef         unsigned short      uint16;  // 2 byte 0 <<<<<<65535
typedef         signed short        sint16;  // 2 bytes -32,768<<<<<<<<32,767
typedef         unsigned long       uint32;  // 4 byte 0<<<<<<<<<<<4294967295
typedef         signed long         sint32;  // 4 byte -2147483648<<<<<<2147483647
typedef         unsigned long long  uint64;  //8 bytes
typedef         signed long long    sint64;  //8 bytes
typedef         float               float32;  //4 bytes
typedef         double              double64;  //8 bytes
typedef enum{

	INPUT_PIN,OUTPUT_PIN
}GPIOPinDirectionTypes;

//port direction enum
typedef enum{
	INPUT_PORT,OUTPUT_PORT=0xFF
}GPIOPORTDirectionTypes;

//end if std_types
#endif
