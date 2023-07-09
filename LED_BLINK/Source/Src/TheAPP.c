/*
 * TheAPP.c
 *
 *  Created on: Jun 27, 2023
 *      Author: romag
 */

#include "TheAPP.h"
#include "ButtonDrv.h"



#define TIMER_TASK (1000 / 1)


uint8_t u8App_RxBuffer[15];
uint16_t u16ReceiverLength;
uint32_t u16SysClickBtn = 0u;

uint16_t u16PeriodUSART = 0u;
uint16_t u16PeriodButton = 0u;

uint16_t u16PreviousValueBlinkBtn = 0u;
uint16_t u16PreviousValueBlinkUSART = 0u;

bool u16FlagCallBack = false;
uint16_t u16ValueBlinkUSART = 0u;

ByteBitField byteBitField;

void TheApp_Init(void)
{
	byteBitField.BytesofData.u8FirstBit = 0;
	byteBitField.BytesofData.u8SecondBit = 0;
}


void TheAPP_MainFunction(void)
{
//	TheAPP_GetClickButton();
//	TheAPP_GetDataFromUSART(u8App_RxBuffer, 15, u16ReceiverLength);
	if(u16FlagCallBack == true)
	{

		u16PeriodUSART = TheAPP_SetPeriodParameters(u16ValueBlinkUSART);
		f_ConfigValueSet(1, 1, u16PeriodUSART);
		u16FlagCallBack = false;
	}

//	if(u16PreviousValueBlinkBtn != u16PeriodButton)
//	{
//		f_ConfigValueSet(1, 1, u16PeriodButton);
//		u16PreviousValueBlinkBtn = u16PeriodButton;
//	}
}

uint16_t TheAPP_SetPeriodParameters(uint16_t u16ValueSet)
{
	uint16_t u16ReturnValue;
	if (0 <= u16ValueSet && u16ValueSet <= 500)
	{
		u16ReturnValue = 1;
	}
	else if (500 <= u16ValueSet && u16ValueSet <= 1000)
	{
		u16ReturnValue = 2;
	}
	else if (1000 <= u16ValueSet && u16ValueSet <= 2000)
	{
		u16ReturnValue = 5;
	}

	else if (2000 <= u16ValueSet && u16ValueSet <= 3000)
	{
		u16ReturnValue = 10;
	}
	else if (3000 <= u16ValueSet)
	{
		u16ReturnValue = 0;
	}
	return u16ReturnValue;
}

void TheAPP_GetClickButton(void)
{
	u16SysClickBtn = f_GetReturnValuePeriod();
	u16PeriodButton = TheAPP_SetPeriodParameters(u16SysClickBtn);
}


//void TheAPP_GetDataFromUSART(uint8_t* BufferData, uint16_t Len, uint16_t* RecievedLen)
//{
//
////	USART_ReceiverBuffer(BufferData, Len, &RecievedLen);
//
//	if(1u == RecievedLen || 2u == RecievedLen)
//	{
//		byteBitField.BytesofData.u8FirstBit = u8App_RxBuffer[1];
//		byteBitField.BytesofData.u8SecondBit = u8App_RxBuffer[0];
//	}
//
//	u16PeriodUSART = TheAPP_SetPeriodParameters(byteBitField.u16InfoBits);
//}

void TheAPP_CallBack(uint16_t u16Value)
{
	u16FlagCallBack = true;
	u16ValueBlinkUSART = u16Value;
}


