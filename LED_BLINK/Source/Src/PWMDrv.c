/*
 * PWMDrv.c
 *
 *  Created on: Jul 22, 2023
 *      Author: romag
 */

#include "PWMDrv.h"


#define OWERFLOW_VALUE		(65535u)
#define SCALE_MAX_VAUE		(1000u)
#define TIMER_STEP			(512u)

#define PEAK_TO_MAX			(1000u)
#define PEAK_TO_MIN			(100u)
#define TASK_PERIOD			(4u)

#define COMPARE_CHANNEL_VALUE(Value)	((Value * OWERFLOW_VALUE) / SCALE_MAX_VAUE);

TS_PWMConfig Ts_PWMConfig_RGB_Red;
TS_PWMConfig Ts_PWMConfig_RGB_Green;
TS_PWMConfig Ts_PWMConfig_RGB_Blue;

extern uint16_t u16ValueRGB_SetRed;
extern uint16_t u16ValueRGB_SetGreen;
extern uint16_t u16ValueRGB_SetBlue;

uint16_t u16TimePeriodTask = 0u;

uint16_t u16Indexd = 0;
uint16_t u16CompareValueCH;

/************************************************************************/
/*!	\fn						f_PWMDrv_Init
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
void f_PWMDrv_Init(TS_PWMConfig* PWM_Config, TIM_TypeDef* TIMx_Port, uint32_t u32TIMx_Pin, uint16_t u16TIMx_ActualValue, TFP_SetCompare SetCompare)
{
	PWM_Config->TIM_Port = TIMx_Port;
	PWM_Config->u32TIM_Pin = u32TIMx_Pin;
	PWM_Config->u16TIM_ActualValue = u16TIMx_ActualValue;
	PWM_Config->f_SetCompare = SetCompare;

	LL_TIM_CC_EnableChannel(PWM_Config->TIM_Port, PWM_Config->u32TIM_Pin);
	LL_TIM_EnableCounter(PWM_Config->TIM_Port);
}

/************************************************************************/
/*!	\fn						f_PWMDrv_SetVal_RGB
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
void f_PWMDrv_SetVal_RGB(TS_PWMConfig* Ts_PWMConfig_RGB, uint16_t* u16Percentage)
{
	TFP_SetCompare SetCompare = Ts_PWMConfig_RGB->f_SetCompare;
	Ts_PWMConfig_RGB->u16TIM_ActualValue = COMPARE_CHANNEL_VALUE(*u16Percentage);
	(*SetCompare)(TIM1, Ts_PWMConfig_RGB->u16TIM_ActualValue);
}

/************************************************************************/
/*!	\fn						f_PWMDrv_MainFunction
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
void f_PWMDrv_MainFunction(void)
{
	if(TASK_PERIOD <= (u16TimePeriodTask++))
	{
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Red, &u16ValueRGB_SetRed);
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Green, &u16ValueRGB_SetGreen);
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Blue, &u16ValueRGB_SetBlue);
	}
}
