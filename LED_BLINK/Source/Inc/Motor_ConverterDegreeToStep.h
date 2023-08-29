/*
 * Motor_ConverterDegreeToStep.h
 *
 *  Created on: 20 июл. 2023 г.
 *      Author: romag
 */

#ifndef INC_MOTOR_CONVERTERDEGREETOSTEP_H_
#define INC_MOTOR_CONVERTERDEGREETOSTEP_H_

#include "main.h"
#include "MotorDrvStepper.h"

void Motor_ConvDegreeTeStep_Init();
void Motor_ConvDegreeToStep_GETValueFromUSART(float* fDegree);
void Motor_ConvDegreeTeStep_SETValueStep(void);
void Motor_ConvDegreeTeStep_MainFunction();



#endif /* INC_MOTOR_CONVERTERDEGREETOSTEP_H_ */
