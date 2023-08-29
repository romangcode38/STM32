/*
 * Test.c
 *
 *  Created on: Jun 27, 2023
 *
 *   Author: romag
 */

#include <stdint.h>
#include<main.h>

#define CONST_1     (1u)
#define CONST_2     (2u)
#define CONST_3     (3u)
#define CONST_4     (4u)

#define LEN 		(16)



typedef enum
{
    Const_0 = 0u,
    Const_1,
    Const_2,
    Const_3,
    Const_4,
	Const256 = 256u,

}TE_Value;


typedef struct
{
	uint8_t Val1;
	uint8_t Val2;
	TE_Value Te_Value;
}TS_Test;


typedef union
{
	uint8_t array[10];
	TS_Test Ts_Test;
}TU_Test;



///////////////////////////////////////////////////////////////////////////

//#pragma pack(2)

typedef struct
{
	uint8_t array[LEN];
	uint32_t u32len;
	uint8_t len;
	uint8_t state;


}TS_Buffer;



typedef struct
{
	uint8_t position;
	TS_Buffer* localBuffer;

}TS_Test2Buffer;


/////////////////////////////////////////////////////////////////////////////


volatile TS_Buffer ts_Buffer;
volatile TS_Test2Buffer ts_Test2Buffer;

//#pragma pack()



volatile uint8_t Value1;
volatile TE_Value Value2;


volatile TS_Test Ts_Test;
volatile TU_Test Tu_Test;


volatile uint8_t Len1;
volatile uint8_t Len2;



void Test_Drv(void)
{
	ts_Buffer.array[1] = 10;
	ts_Test2Buffer.position = 10;
	ts_Test2Buffer.localBuffer = &ts_Buffer;

	 Value1 = CONST_3;
 	 Value2 = 50;

 	 Len1 = sizeof(ts_Buffer);
 	 Len2 = sizeof(ts_Test2Buffer);

}





