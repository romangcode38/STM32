/*
 * Motor_ConverterDegreeToStep.c
 *
 *  Created on: 20 июл. 2023 г.
 *      Author: romag
 */

#include "Motor_ConverterDegreeToStep.h"


#define TIME_TASK				(2u)
#define COMPLITE_ROTATION	 	(6.28) // 2PI
#define FULL_ROTATION_STEPS	 	(2048u)
#define FULL_ROTATION_DEGREE 	(360u)

float fValueDegree;
uint32_t ResultValueToStep = 0u;
uint16_t u16Time_TaskPeriod = 0u;

/************************************************************************/
/*!	\fn						Motor_ConvDegreeTeStep_Init
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
void Motor_ConvDegreeTeStep_Init(void)
{
	fValueDegree = 0.0f;
}

/************************************************************************/
/*!	\fn						Motor_ConvDegreeToStep_GETValueFromUSART
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
void Motor_ConvDegreeToStep_GETValueFromUSART(float* fDegree)
{
	fValueDegree = *fDegree;
}

/************************************************************************/
/*!	\fn						Motor_ConvDegreeTeStep_SETValueStep
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
void Motor_ConvDegreeTeStep_SETValueStep(void)
{
//	ResultValueToStep = ((uint32_t)(FULL_ROTATION_STEPS * fValueDegree) / COMPLITE_ROTATION);		//When we enter the steps
	ResultValueToStep = ((uint32_t)(FULL_ROTATION_STEPS * fValueDegree) / FULL_ROTATION_DEGREE);	//When we enter the degree
}

/************************************************************************/
/*!	\fn					Motor_ConvDegreeTeStep_MainFunction
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
void Motor_ConvDegreeTeStep_MainFunction()
{
	if(TIME_TASK <= (u16Time_TaskPeriod++))
	{
		Motor_ConvDegreeTeStep_SETValueStep();
		f_MotorSteperDrv_SetStep(ResultValueToStep);
		u16Time_TaskPeriod = 0;
	}
}
