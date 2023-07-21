/*
 * Motor_ConverterDegreeToStep.c
 *
 *  Created on: 20 июл. 2023 г.
 *      Author: romag
 */

#include "Motor_ConverterDegreeToStep.h"
#include "MotorDrvStepper.h"


float fValueDegree;
uint32_t ResultValueToStep = 0u;



#define COMPLITE_ROTATION	(6.28) // 2PI
#define FULL_ROTATION_STEPS	(2048u)
#define FULL_ROTATION_DEGREE (360u)

void Motor_ConvDegreeTeStep_Init(void)
{
	fValueDegree = 0.0f;
}

void Motor_ConvDegreeToStep_GETValueFromUSART(float* fDegree)
{
	fValueDegree = *fDegree;
}

void Motor_ConvDegreeTeStep_SETValueStep(void)
{
//	ResultValueToStep = ((uint16_t)(FULL_ROTATION_STEPS * fValueDegree) / COMPLITE_ROTATION);		//When we enter the steps
	ResultValueToStep = ((uint32_t)(FULL_ROTATION_STEPS * fValueDegree) / FULL_ROTATION_DEGREE);	//When we enter the degree


}

void Motor_ConvDegreeTeStep_MainFunction()
{
	Motor_ConvDegreeTeStep_SETValueStep();
	f_MotorSteperDrv_SetStep(ResultValueToStep);
}
