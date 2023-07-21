/*
 * MotorDrv.h
 *
 *  Created on: 15 июл. 2023 г.
 *      Author: romag
 */

#ifndef INC_MOTORDRVSTEPPER_H_
#define INC_MOTORDRVSTEPPER_H_

#include "main.h"


typedef struct
{
	GPIO_TypeDef* PORT;
	uint16_t u16PIN;
}TS_MotorConfig;

void f_MotorSteperDrv_Init(TS_MotorConfig* MotorConfig, GPIO_TypeDef* PORT, uint16_t u16PIN);
void f_MotorSteperDrv_StepSetting(uint8_t u8DirectionRotate);
void f_MotorSteperDrv_SetStep(uint32_t fValueRotation);
void f_MotorSteperDrv_MainFunction(void);


#endif /* INC_MOTORDRVSTEPPER_H_ */
