/*
 * Ecum.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */
#include <stdbool.h>
#include "main.h"
#include "stm32g0xx_ll_rcc.h"

#include "LedDrv.h"
#include "ButtonDrv.h"

static volatile unsigned int ru32_SysTick = 0u;
static volatile unsigned int ru32_OldSysTick = 0u;

void EcuM_Init(void);
void EcuM_MainFunction(void);

void EcuM_0(void)
{
	EcuM_Init();
	ButtonDrv_Init();
	LedDrv_Init();
	while(1)
	{
		if (ru32_OldSysTick != ru32_SysTick)
		{
			EcuM_MainFunction();
			ru32_OldSysTick = ru32_SysTick;
		}
	}
}

void EcuM_SysTickCallBack(void)
{
	ru32_SysTick++;
	if(ru32_SysTick == 10000)
	{
		ru32_SysTick = 0;
	}
}

void EcuM_Init(void)
{
	LL_RCC_ClocksTypeDef rcc_clocks;
	LL_RCC_GetSystemClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.SYSCLK_Frequency/1000);
}


void EcuM_MainFunction(void)
{
	ButtonDrv_MainFunction();
	LedDrv_MainFunction();
}


