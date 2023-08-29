/*
 * ButtonDrv.c
 *
 *  Created on: Jun 6, 2023
 *      Author: romag
 */
#include "ButtonDrv.h"

static volatile unsigned int ru32_SysClickBtn = 0u;
static volatile unsigned int ru32_TickBtn = 0u;

uint16_t ru16_StateBtn = 0u;


ButtonConfig buttonConfig;

/************************************************************************/
/*!	\fn				f_GetReturnValuePeriod
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
void ButtonDrv_Init(ButtonConfig* buttonConfig, GPIO_TypeDef* Port, uint32_t Pin)
{
	buttonConfig->Port = Port;
	buttonConfig->Pin = Pin;
	buttonConfig->PrevState = RESET;

	ru32_SysClickBtn = 0;
	ru16_StateBtn = SET;
}

/************************************************************************/
/*!	\fn
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
uint32_t f_GetReturnValuePeriod()
{
	return ru32_TickBtn;
}

/************************************************************************/
/*!	\fn				SetPeriod
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

/************************************************************************/
/*!	\fn				ButtonDrv_MainFunction
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
void ButtonDrv_MainFunction()
{
	ru16_StateBtn = LL_GPIO_IsInputPinSet(buttonConfig.Port, buttonConfig.Pin);

	SetPeriod(ru16_StateBtn);
}
