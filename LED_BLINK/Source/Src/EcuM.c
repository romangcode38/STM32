/*
 * Ecum.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */
#include <stdbool.h>
#include "main.h"
#include "stm32g0xx_ll_rcc.h"


#include "Ecum.h"
#include "Ecum_Callouts.h"


static volatile unsigned int ru32_SysTick = 0u;
static volatile unsigned int ru32_OldSysTick = 0u;


void EcuM_Init(void);
void EcuM_MainFunction(void);


void EcuM_SysTickCallBack(void)
{
	ru32_SysTick++;
}

void EcuM_Init(void)
{
	LL_RCC_ClocksTypeDef rcc_clocks;
	LL_RCC_GetSystemClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.SYSCLK_Frequency/1000);
	f_Ecum_InitBaseTask();
}


void EcuM_MainFunction(void)
{
	EcuM_Init();

	while(1)
	{

		if (ru32_OldSysTick ^ ru32_SysTick)
		{
			ru32_OldSysTick = ru32_SysTick;

			f_Ecum_BaseRecurenceTask();
			if(ru32_OldSysTick & SCHM_BASE_DIV_2)
			{
				f_Ecum_BaseRecurenceTaskDiv2();
			}
			if(ru32_OldSysTick & SCHM_BASE_DIV_4)
			{
				f_Ecum_BaseRecurenceTaskDiv4();
			}
			if(ru32_OldSysTick & SCHM_BASE_DIV_8)
			{
				f_Ecum_BaseRecurenceTaskDiv8();

			}
			if(ru32_OldSysTick & SCHM_BASE_DIV_16)
			{
				f_Ecum_BaseRecurenceTaskDiv16();

			}
			if(ru32_OldSysTick & SCHM_BASE_DIV_32)
			{
				f_Ecum_BaseRecurenceTaskDiv32();
			}

		}
	}
}


