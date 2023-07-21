/*
 * TheAPP.c
 *
 *  Created on: Jun 27, 2023
 *      Author: romag
 */

#include "TheAPP.h"
#include "ButtonDrv.h"
#include "LedDrv.h"
#include "MotorDrvStepper.h"
#include "Motor_ConverterDegreeToStep.h"



#define TIMER_TASK (1000 / 1)
#define DATA_FOR_LED		(0x01)
#define DATA_FOR_STEP_MOTOR	(0x02)


uint8_t u8App_RxBuffer[15];
uint16_t u16ReceiverLength;
uint32_t u16SysClickBtn = 0u;

uint16_t u16PeriodUSART = 0u;
uint16_t u16PeriodButton = 0u;

uint16_t u16PreviousValueBlinkBtn = 0u;
uint16_t u16PreviousValueBlinkUSART = 0u;

bool u16FlagCallBack = false;
uint16_t u16ValueUSART = 0u;
float fValueUSARTForMotor = 0u;
uint8_t u8CMD_DataUSART = 0u;

extern TS_LedConfig ledConfig1;
extern TS_LedConfig ledConfig2;
extern TS_LedConfig ledConfig3;
extern TS_LedConfig ledConfig4;



ByteBitField byteBitField;

void TheApp_Init(void)
{
	byteBitField.BytesofData.u8FirstBit = 0;
	byteBitField.BytesofData.u8SecondBit = 0;
}


void TheAPP_MainFunction(void)
{
	TheAPP_GetClickButton();

	if(u16FlagCallBack == true)
	{

		if(u8CMD_DataUSART == DATA_FOR_LED)
		{
		    f_SetValuePeriod(&ledConfig1, u16ValueUSART);
		}
		else if(u8CMD_DataUSART == DATA_FOR_STEP_MOTOR)
		{
			Motor_ConvDegreeToStep_GETValueFromUSART(&fValueUSARTForMotor);
		}
		u16FlagCallBack = false;
	}

}


void TheAPP_GetClickButton(void)
{
	u16SysClickBtn = f_GetReturnValuePeriod();
	if(u16PreviousValueBlinkBtn != u16SysClickBtn)
	{
	    f_SetValuePeriod(&ledConfig2, u16SysClickBtn);
		u16PreviousValueBlinkBtn = u16SysClickBtn;
	}
}

void TheAPP_CallBack(uint8_t u8CMDData, uint16_t u16Value)
{
	u16FlagCallBack = true;
	u16ValueUSART = u16Value;
	u8CMD_DataUSART = u8CMDData;
}

void TheAPP_CallBack_Motor(uint8_t u8CMDDataMotor, float* fValue)
{
	u16FlagCallBack = true;
	fValueUSARTForMotor =  (*fValue);
	u8CMD_DataUSART = u8CMDDataMotor;
}


