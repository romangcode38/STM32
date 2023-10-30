/*
 * Ecum_Callouts.c
 *
 *  Created on: Jul 13, 2023
 *      Author: romag
 */

#include "Ecum_Callouts.h"


extern TS_LedConfig ledConfig1;
extern TS_LedConfig ledConfig2;
extern TS_LedConfig ledConfigGreen;

extern ButtonConfig buttonConfig;

extern TS_MotorConfig MotorConfigPin1;
extern TS_MotorConfig MotorConfigPin2;
extern TS_MotorConfig MotorConfigPin3;
extern TS_MotorConfig MotorConfigPin4;

extern TS_PWMConfig Ts_PWMConfig_RGB_Red;
extern TS_PWMConfig Ts_PWMConfig_RGB_Green;
extern TS_PWMConfig Ts_PWMConfig_RGB_Blue;

extern TS_IR_Config IR_Config1;


/************************************************************************/
/*!	\fn					f_Ecum_InitBaseTask
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
void f_Ecum_InitBaseTask(void)
{
	ButtonDrv_Init(&buttonConfig, USER_BTN_GPIO_Port, USER_BTN_Pin);
	LedDrv_Init(&ledConfigGreen, LED_GREEN_GPIO_Port, LED_GREEN_Pin);

	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN1_GPIO_Port, MOTOR_PIN1_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN2_GPIO_Port, MOTOR_PIN2_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN3_GPIO_Port, MOTOR_PIN3_Pin);
	f_MotorSteperDrv_Init(&MotorConfigPin1, MOTOR_PIN4_GPIO_Port, MOTOR_PIN4_Pin);

	USARTDrv_Init(MX_USART1_UART_Init);
	f_USARTCommProt_Init();

	AdcDrv_Init(MX_ADC1_Init);
	Adc_ConverterValue_Init();

	Thermistor_InitFunction();

	Motor_ConvDegreeTeStep_Init();

    f_PWMDrv_Init(&Ts_PWMConfig_RGB_Red, TIM1, LL_TIM_CHANNEL_CH1, 0, LL_TIM_OC_SetCompareCH1);
    f_PWMDrv_Init(&Ts_PWMConfig_RGB_Green, TIM1, LL_TIM_CHANNEL_CH2, 0, LL_TIM_OC_SetCompareCH2);
    f_PWMDrv_Init(&Ts_PWMConfig_RGB_Blue, TIM1, LL_TIM_CHANNEL_CH3, 0, LL_TIM_OC_SetCompareCH3);

    IR_RemoteDrv_Init(&IR_Config1, TIM2, LL_TIM_CHANNEL_CH2, IR_Remote_IT_GPIO_Port, IR_Remote_IT_Pin);

    I2CDrv_Init(MX_I2C1_Init);
    f_LCD_Init();
    TheApp_Init();
}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTask
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
void f_Ecum_BaseRecurenceTask(void)
{
	AdcDrv_MainFunction();

}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTaskDiv2
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
void f_Ecum_BaseRecurenceTaskDiv2(void)
{
	f_MotorSteperDrv_MainFunction();
	Motor_ConvDegreeTeStep_MainFunction();

}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTaskDiv4
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
void f_Ecum_BaseRecurenceTaskDiv4(void)
{

	TheAPP_MainFunction();
	f_PWMDrv_MainFunction();
	IR_RemoteDrv_MainFunction();
	f_LCD_MainFunction();

}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTaskDiv8
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
void f_Ecum_BaseRecurenceTaskDiv8(void)
{
	AdcConverterValue_MainFunction();
	Thermistor_MainFunction();
	f_USARTCommProt_Main();
	Test_Drv();

}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTaskDiv16
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
void f_Ecum_BaseRecurenceTaskDiv16(void)
{

}

/************************************************************************/
/*!	\fn					f_Ecum_BaseRecurenceTaskDiv32
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
void f_Ecum_BaseRecurenceTaskDiv32(void)
{
	ButtonDrv_MainFunction();
	LedDrv_MainFunction(&ledConfigGreen);
}
