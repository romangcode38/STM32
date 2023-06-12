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

uint16_t ru16_StateBtn;

volatile uint16_t u16BtnSetPeriod = 0;
int contor = 0;

typedef struct
{
	uint16_t u16IdBtn;
	GPIO_TypeDef* Port;
	uint32_t Pin;

}ButtonConfig;

ButtonConfig buttonConfig;


void ButtonDrv_Init(void)
{
	buttonConfig.u16IdBtn = 1;
	buttonConfig.Port = USER_BTN_GPIO_Port;
	buttonConfig.Pin = USER_BTN_Pin;

	ru32_SysClickBtn = 0;
}


void SetPeriod(uint16_t StateBtn)
{
	if (ru16_StateBtn == SET)
	{
		ChangeButtonVallue(buttonConfig.u16IdBtn, ru32_SysClickBtn);
		contor = 1;
	}
	else if (ru16_StateBtn == RESET)
	{
		if (contor == 1) {
			ru32_SysClickBtn = 0;
			contor = 0;
		}
		ru32_SysClickBtn++;
	}
}

void ButtonDrv_MainFunction()
{
	ru16_StateBtn = LL_GPIO_IsInputPinSet(buttonConfig.Port, buttonConfig.Pin);

	SetPeriod(ru16_StateBtn);
}

void ChangeButtonVallue(uint16_t u16IdBtn, uint32_t u32Tick)
{
	if (1 <= u32Tick && u32Tick <= 500)
	{
		u16BtnSetPeriod = 1;
		f_ConfigValueSet(ButtonON, u16IdBtn, u16BtnSetPeriod);
	}
	else if (500 <= u32Tick && u32Tick <= 1000)
	{
		u16BtnSetPeriod = 2;
		f_ConfigValueSet(ButtonON, u16IdBtn, u16BtnSetPeriod);
	}
	else if (1000 <= u32Tick && u32Tick <= 2000)
	{
		u16BtnSetPeriod = 5;
		f_ConfigValueSet(ButtonON, u16IdBtn, u16BtnSetPeriod);
	}

	else if (2000 <= u32Tick && u32Tick <= 3000)
	{
		u16BtnSetPeriod = 10;
		f_ConfigValueSet(ButtonON, u16IdBtn, u16BtnSetPeriod);
	}
	else
	{
		ru32_SysClickBtn = 0;
		u16BtnSetPeriod = 0;
		f_ConfigValueSet(ButtonOFF, u16IdBtn, u16BtnSetPeriod);
	}
}
