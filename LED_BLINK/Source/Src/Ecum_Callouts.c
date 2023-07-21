/*
 * Ecum_Callouts.c
 *
 *  Created on: Jul 13, 2023
 *      Author: romag
 */

#include "LedDrv.h"
#include "ButtonDrv.h"
#include "USARTDrv.h"
#include "TheAPP.h"
#include "USART_CommunicationProtocol.h"
#include "Test.h"
#include "AdcDrv.h"
#include "ADC_ConverterValue.h"
#include "CDD_Thermistor_CalcValue.h"
#include "MotorDrvStepper.h"
#include "Motor_ConverterDegreeToStep.h"


extern TS_LedConfig ledConfig1;
extern TS_LedConfig ledConfig2;
extern TS_LedConfig ledConfig3;

extern TS_MotorConfig MotorConfigPin1;
extern TS_MotorConfig MotorConfigPin2;
extern TS_MotorConfig MotorConfigPin3;
extern TS_MotorConfig MotorConfigPin4;

void f_Ecum_InitBaseTask(void)
{
	ButtonDrv_Init();
	LedDrv_Init(&ledConfig1, LED_RED1_GPIO_Port, LED_RED1_Pin);
	LedDrv_Init(&ledConfig2, LED_RED2_GPIO_Port, LED_RED2_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);
	f_USARTCommProt_Init();
	USARTDrv_Init();
	TheApp_Init();
	AdcDrv_Init();
	Adc_ConverterValue_Init();
	Thermistor_InitFunction();
	Motor_ConvDegreeTeStep_Init();
}

void f_Ecum_BaseRecurenceTask(void)
{
	AdcDrv_MainFunction();
	USARTDrv_MainFunction();

}
void f_Ecum_BaseRecurenceTaskDiv2(void)
{
	TheAPP_MainFunction();

}
void f_Ecum_BaseRecurenceTaskDiv4(void)
{
	ButtonDrv_MainFunction();
	LedDrv_MainFunction(&ledConfig1);
	LedDrv_MainFunction(&ledConfig2);
	AdcConverterValue_MainFunction();
	Thermistor_MainFunction();
	f_MotorSteperDrv_MainFunction();
	Motor_ConvDegreeTeStep_MainFunction();

}
void f_Ecum_BaseRecurenceTaskDiv8(void)
{

}
void f_Ecum_BaseRecurenceTaskDiv16(void)
{
	f_USARTCommProt_Main();

}
void f_Ecum_BaseRecurenceTaskDiv32(void)
{
}
