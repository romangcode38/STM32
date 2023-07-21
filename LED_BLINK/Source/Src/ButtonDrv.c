/*
 * ButtonDrv.c
 *
 *  Created on: Jun 6, 2023
 *      Author: romag
 */
#include <stdbool.h>
#include "LedDrv.h"
#include "main.h"


#define ButtonON		(1u)
#define ButtonOFF		(0u)

static volatile unsigned int ru32_SysClickBtn = 0u;
static volatile unsigned int ru32_TickBtn = 0u;


uint16_t ru16_StateBtn = SET;

typedef struct
{
	GPIO_TypeDef* Port;
	uint32_t Pin;
	uint16_t PrevState;

}ButtonConfig;

ButtonConfig buttonConfig;


void ButtonDrv_Init(void)
{
	buttonConfig.Port = USER_BTN_GPIO_Port;
	buttonConfig.Pin = USER_BTN_Pin;
	buttonConfig.PrevState = RESET;
	ru32_SysClickBtn = 0;
}

uint32_t f_GetReturnValuePeriod()
{
	return ru32_TickBtn;
}

void SetPeriod(uint16_t u16StateBtn)
{
	if (u16StateBtn == SET)
	{
		if(buttonConfig.PrevState != u16StateBtn)
		{
			ru32_TickBtn = ru32_SysClickBtn;
			f_GetReturnValuePeriod();
			ru32_SysClickBtn = 0u;
		}
	}
	else if (u16StateBtn == RESET)
	{
		ru32_SysClickBtn++;
	}
	buttonConfig.PrevState = u16StateBtn;
}



void ButtonDrv_MainFunction()
{
	ru16_StateBtn = LL_GPIO_IsInputPinSet(buttonConfig.Port, buttonConfig.Pin);

	SetPeriod(ru16_StateBtn);
}

//void ChangeButtonVallue(uint16_t u16IdBtn, uint32_t u32Tick)
//{
//	if (0 <= u32Tick && u32Tick <= 500)
//	{
//		f_ConfigValueSet(ButtonON, u16IdBtn, 1);
//	}
//	else if (500 <= u32Tick && u32Tick <= 1000)
//	{
//		f_ConfigValueSet(ButtonON, u16IdBtn, 2);
//	}
//	else if (1000 <= u32Tick && u32Tick <= 2000)
//	{
//		f_ConfigValueSet(ButtonON, u16IdBtn, 5);
//	}
//
//	else if (2000 <= u32Tick && u32Tick <= 3000)
//	{
//		f_ConfigValueSet(ButtonON, u16IdBtn, 10);
//	}
//	else if (3000 <= u32Tick)
//	{
//		f_ConfigValueSet(ButtonOFF, u16IdBtn, 0);
//		u32Tick = 0;
//	}
//}
