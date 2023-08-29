/*
 * MotorDrv.c
 *
 *  Created on: 15 июл. 2023 г.
 *      Author: romag
 */

#include "MotorDrvStepper.h"


#define TIME_STEPS_TASK	(2u)

//Direction Rotate
#define	ROTATE_LEFT	  (0x01)
#define ROTATE_RIGHT  (0x02)
#define ROTATE_REPAUS (0x00)


uint16_t u16StepNumber;
uint16_t u16TimerTick;
uint32_t u32ActualStep;
uint32_t u32RequestedStep;

TS_MotorConfig MotorConfigPin1;
TS_MotorConfig MotorConfigPin2;
TS_MotorConfig MotorConfigPin3;
TS_MotorConfig MotorConfigPin4;

/************************************************************************/
/*!	\fn						f_MotorSteperDrv_Init
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
void f_MotorSteperDrv_Init(TS_MotorConfig* MotorConfig, GPIO_TypeDef* PORT, uint16_t u16PIN)
{
	u16StepNumber = 0;
	u16TimerTick = 0;
    u32ActualStep = 0;
    u32RequestedStep = 0;

	MotorConfig->PORT = PORT;
	MotorConfig->u16PIN = u16PIN;
	PORT ->BRR = u16PIN;
}

/************************************************************************/
/*!	\fn						f_MotorSteperDrv_StepSetting
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
void f_MotorSteperDrv_StepSetting(uint8_t u8DirectionRotate)
{
	if(u8DirectionRotate == ROTATE_LEFT)
	{
		switch (u16StepNumber) {
			case 0:
				LL_GPIO_SetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 1:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 2:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 3:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
		}
	}
	else if(u8DirectionRotate == ROTATE_RIGHT)
	{
		switch (u16StepNumber) {
			case 0:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 1:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 2:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_SetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 3:
				LL_GPIO_SetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
		}
	}
	else if(u8DirectionRotate == ROTATE_REPAUS)
	{
		switch (u16StepNumber) {
			case 0:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 1:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 2:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
			case 3:
				LL_GPIO_ResetOutputPin(MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
				LL_GPIO_ResetOutputPin(MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
				break;
		}
	}

	if(u16StepNumber++ >= 3)
	{
		u16StepNumber = 0;
	}
}

/************************************************************************/
/*!	\fn						f_MotorSteperDrv_SetStep
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
void f_MotorSteperDrv_SetStep(uint32_t u32ValueRotation)
{
	u32RequestedStep = u32ValueRotation;
}

/************************************************************************/
/*!	\fn						f_MotorSteperDrv_MainFunction
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
void f_MotorSteperDrv_MainFunction(void)
{
	if (u32ActualStep < u32RequestedStep)
	{
		if(TIME_STEPS_TASK > u16TimerTick++)
		{
			f_MotorSteperDrv_StepSetting(ROTATE_LEFT);
			u32ActualStep++;
			u16TimerTick = 0;
		}

	}
	if (u32ActualStep > u32RequestedStep)
	{
		if(TIME_STEPS_TASK > u16TimerTick++)
		{
			f_MotorSteperDrv_StepSetting(ROTATE_RIGHT);
			u32ActualStep--;
			u16TimerTick = 0;
		}

	}
	if (u32ActualStep == u32RequestedStep)
	{
		f_MotorSteperDrv_StepSetting(ROTATE_REPAUS);
	}
}
