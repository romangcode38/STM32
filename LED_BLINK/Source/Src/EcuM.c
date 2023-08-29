/*
 * Ecum.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#include "Ecum.h"

static volatile unsigned int ru32_SysTick = 0u;
static volatile unsigned int ru32_OldSysTick = 0u;

/************************************************************************/
/*!	\fn				EcuM_Init
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void EcuM_Init(void)
{
	LL_RCC_ClocksTypeDef rcc_clocks;
	LL_RCC_GetSystemClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.SYSCLK_Frequency/1000);
	f_Ecum_InitBaseTask();
}

/************************************************************************/
/*!	\fn				EcuM_SysTickCallBack
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void EcuM_SysTickCallBack(void)
{
	ru32_SysTick++;
}


/************************************************************************/
/*!	\fn				EcuM_MainFunction
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
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
			else if(ru32_OldSysTick & SCHM_BASE_DIV_4)
			{
				f_Ecum_BaseRecurenceTaskDiv4();
			}
			else if(ru32_OldSysTick & SCHM_BASE_DIV_8)
			{
				f_Ecum_BaseRecurenceTaskDiv8();
			}
			else if(ru32_OldSysTick & SCHM_BASE_DIV_16)
			{
				f_Ecum_BaseRecurenceTaskDiv16();
			}
			else if(ru32_OldSysTick & SCHM_BASE_DIV_32)
			{
				f_Ecum_BaseRecurenceTaskDiv32();
			}
			else
			{
				//Comment
			}
		}
	}
}
