/*
 * LedDrv.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#include "LedDrv.h"

#define TIME_TASK	(32u)

TS_LedConfig ledConfig1;
TS_LedConfig ledConfig2;
TS_LedConfig ledConfig3;
TS_LedConfig ledConfig4;

TS_LedConfig ledConfigGreen;

/************************************************************************/
/*!	\fn					LedDrv_Init
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void LedDrv_Init(TS_LedConfig* ledConfig, GPIO_TypeDef* Port, uint16_t Pin)
{
	ledConfig->Ledx_Port = Port;
	ledConfig->u32Ledx_Pin = Pin;
	ledConfig->u16Ledx_Period = 0;
	ledConfig->u16Ledx_Timer = 0;
	ledConfig->Ledx_Port->BSRR = ledConfig->u32Ledx_Pin;
}

/************************************************************************/
/*!	\fn					f_SetValuePeriod
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void f_SetValuePeriod(TS_LedConfig* ledConfig, uint16_t u16BlinkLed)
{
	ledConfig->u16Ledx_Period = u16BlinkLed / TIME_TASK;
}

/************************************************************************/
/*!	\fn					LedDrv_MainFunction
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void LedDrv_MainFunction(TS_LedConfig* ledConfig)
{
 	if(ledConfig->u16Ledx_Period <= ledConfig->u16Ledx_Timer++)
	{
 		LL_GPIO_TogglePin(ledConfig->Ledx_Port, ledConfig->u32Ledx_Pin);
 		ledConfig->u16Ledx_Timer = 0;
	}
}
