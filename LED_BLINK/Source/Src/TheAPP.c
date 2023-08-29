/*
 * TheAPP.c
 *
 *  Created on: Jun 27, 2023
 *      Author: romag
 */

#include "TheAPP.h"


#define TASK_PERIOD			(4u)

#define TIME_OUT_PACKET			(1000 / TASK_PERIOD)
#define TIME_PACKET_TRANSMIT	(120u / TASK_PERIOD)
#define MAXIMUM_PWM_PERCENTAGE	(1000u)

bool u16FlagCallBack = false;

uint32_t u16SysClickBtn = 0u;

uint32_t u32ValueTemperatureCurrent = 0u;
uint32_t u32ValueTemperatureOld = 0u;

uint32_t u32ValueLuminosityCurrent = 0u;
uint32_t u32ValueLuminosityOld = 0u;

uint16_t u16ValueRGB_SetRed = 0u;
uint16_t u16ValueRGB_SetGreen = 0u;
uint16_t u16ValueRGB_SetBlue = 0u;

uint16_t u16TimeTransmissionTemp = 0u;
uint16_t u16TimeOut = 0;
uint16_t u16TimeOutPacket = 0;

uint16_t u16PeriodUSART = 0u;
uint16_t u16PeriodButton = 0u;

uint16_t u16Value_USART = 0u;

uint16_t u16PreviousValueBlinkBtn = 0u;
uint16_t u16PreviousValueBlinkUSART = 0u;

uint8_t u8CMD_DataLuminosity = 0u;
uint8_t u8CMD_DataLed = 0u;
uint8_t u8CMD_DataMotor = 0u;
uint8_t u8CMD_DataRGB = 0u;
uint8_t u8PacketSend[SEND_PACKET_DATA];

uint8_t u8RequestStateValue = 0u;

float fValueLux = 0.00f;


float fValueUSARTForMotor = 0u;
float flValueOnHysteresis = 0.f;
float fValueMotorSteps = 0u;

extern TS_LedConfig ledConfig1;
extern TS_LedConfig ledConfig2;
extern TS_LedConfig ledConfig3;
extern TS_LedConfig ledConfig4;
extern TS_LedConfig ledConfigGreen;

extern TS_PWMConfig Ts_PWMConfig_RGB_Red;
extern TS_PWMConfig Ts_PWMConfig_RGB_Green;
extern TS_PWMConfig Ts_PWMConfig_RGB_Blue;

TE_CommunicationState CommActualState;
ByteBitField byteBitField;


/************************************************************************/
/*!	\fn						TheApp_Init
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
void TheApp_Init(void)
{
	u8RequestStateValue = ACK_BYTE;
	byteBitField.BytesofData.u8FirstBit = 0;
	byteBitField.BytesofData.u8SecondBit = 0;

	CommActualState = NO_COMM;

	u32ValueLuminosityCurrent = LUMINOSITY_MAX;

	fValueLux = CALC_VALUE_TO_LUX(u32ValueLuminosityCurrent);

	u16ValueRGB_SetRed = CONVERT_LUX_TO_RGB_RED(LUMINOSITY_MAX);
	f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Red, &u16ValueRGB_SetRed);
}

/************************************************************************/
/*!	\fn						TheAPP_MainFunction
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
void TheAPP_MainFunction(void)
{

	TheApp_CommunicationStateProtocol();
	TheAPP_GetClickButton();

	if((TIME_TRANSMISSION_TEMP / TASK_PERIOD) <= u16TimeTransmissionTemp++)
	{
		TheApp_SendTemperatureToUSART();
		u16TimeTransmissionTemp = 0;
	}

	if(u16FlagCallBack == true)
	{
		TheApp_VerificationHysteresis();
		u16FlagCallBack = false;
	}
}

/************************************************************************/
/*!	\fn						TheApp_SendTemperatureToUSART
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
void TheApp_SendTemperatureToUSART(void)
{
	u32ValueTemperatureCurrent = Theemistor_GetTemperatureFunction();
	f_USARTCommProt_SendData(u8PacketSend, CMD_TEMPERATURE_VALUE, u32ValueTemperatureCurrent);
}

/************************************************************************/
/*!	\fn						TheApp_VerificationHysteresis
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
void TheApp_VerificationHysteresis(void)
{
	flValueOnHysteresis = CALCULATE_PERCENTAGE_ON_LUMINOSITY(u32ValueLuminosityCurrent);

	if(u32ValueLuminosityCurrent > u32ValueLuminosityOld)
	{
		if((u32ValueLuminosityCurrent + flValueOnHysteresis) > u32ValueLuminosityCurrent)
		{
			TheApp_SetReqForLedRGB(u32ValueLuminosityCurrent);
			TheApp_SetReqForMotor(u32ValueLuminosityCurrent);
			u32ValueLuminosityOld = u32ValueLuminosityCurrent;
		}
	}
	else
	{
		if((u32ValueLuminosityCurrent - flValueOnHysteresis) < u32ValueLuminosityCurrent)
		{
			TheApp_SetReqForLedRGB(u32ValueLuminosityCurrent);
			TheApp_SetReqForMotor(u32ValueLuminosityCurrent);
			u32ValueLuminosityOld = u32ValueLuminosityCurrent;
		}
	}
}

/************************************************************************/
/*!	\fn						TheApp_CommunicationStateProtocol
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
void TheApp_CommunicationStateProtocol(void)
{
	u16TimeOut++;
	switch (CommActualState)
	{
		case NO_COMM:
			if (u16FlagCallBack)
			{
				u16TimeOut = 0;
				CommActualState = NORMAL_COMM;

			}
			if(ACK_BYTE != u8RequestStateValue)
			{
				f_SetValuePeriod(&ledConfigGreen,  NACK_PACKET_BLINK);
				CommActualState = ERROR_COMM;
			}
			else
			{
				f_SetValuePeriod(&ledConfigGreen,  NO_COMM_PACKET_BLINK);
			}
			break;
		case NORMAL_COMM:

			f_SetValuePeriod(&ledConfigGreen,  ACK_PACKET_BLINK);
			if(false != u16FlagCallBack)
			{
				u16TimeOut = 0;
			}

			if(ACK_BYTE != u8RequestStateValue)
			{
				f_SetValuePeriod(&ledConfigGreen,  NACK_PACKET_BLINK);
				CommActualState = ERROR_COMM;
			}
			else if(CHECK_TIMEOUT(u16TimeOut))
			{
				CommActualState = LOST_COMM;
				f_SetValuePeriod(&ledConfigGreen,  NO_COMM_PACKET_BLINK);
				u16TimeOutPacket = ZERO;
			}
			break;

		case LOST_COMM:
			if(u16TimeOutPacket != 0)
			{
				u16TimeOutPacket--;
			}

			if(ACK_BYTE != u8RequestStateValue)
			{
				f_SetValuePeriod(&ledConfigGreen,  NACK_PACKET_BLINK);
				CommActualState = ERROR_COMM;
			}

			else if(false != u16FlagCallBack)
			{
				if(ZERO != u16TimeOutPacket)
				{
					CommActualState = NORMAL_COMM;
				}
				u16TimeOutPacket = TIME_PACKET_TRANSMIT;
				u16TimeOut = ZERO;
			}
			break;

		case ERROR_COMM:
			if (u16FlagCallBack)
			{
				CommActualState = NORMAL_COMM;
			}
			else if(CHECK_TIMEOUT(u16TimeOut))
			{
				CommActualState = LOST_COMM;
				f_SetValuePeriod(&ledConfigGreen,  NO_COMM_PACKET_BLINK);
			}
			break;
	}

}

/************************************************************************/
/*!	\fn						TheApp_SetReqForLedRGB
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
void TheApp_SetReqForLedRGB(float fValue)
{
	if(fValue <= LUMINOSITY_MAX && fValue > LUMINOSITY_MIDDLE)
	{
		u16ValueRGB_SetRed = CONVERT_LUX_TO_RGB_RED(fValue);
	    u16ValueRGB_SetBlue = CONVERT_LUX_TO_RGB_BLUE_UP(fValue);

	    u16ValueRGB_SetBlue = MAXIMUM_PWM_PERCENTAGE - u16ValueRGB_SetRed;
	    f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Red, &u16ValueRGB_SetRed);
	    f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Blue, &u16ValueRGB_SetBlue);

	    u16ValueRGB_SetGreen = 0;
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Green, &u16ValueRGB_SetGreen);

	}
	else if(fValue <= LUMINOSITY_MIDDLE && fValue >= LUMINOSITY_MIN)
	{
		u16ValueRGB_SetGreen = CONVERT_LUX_TO_RGB_GREEN(fValue);
		u16ValueRGB_SetBlue = CONVERT_LUX_TO_RGB_BLUE_DOWN(fValue);

		u16ValueRGB_SetGreen = MAXIMUM_PWM_PERCENTAGE - u16ValueRGB_SetBlue;
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Green, &u16ValueRGB_SetGreen);
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Blue, &u16ValueRGB_SetBlue);

		u16ValueRGB_SetRed = 0;
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Red, &u16ValueRGB_SetRed);
	}
	else
	{

		u16ValueRGB_SetRed = 0;
		u16ValueRGB_SetBlue = 0;
		u16ValueRGB_SetGreen = 0;

		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Red, &u16ValueRGB_SetRed);
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Green, &u16ValueRGB_SetGreen);
		f_PWMDrv_SetVal_RGB(&Ts_PWMConfig_RGB_Blue, &u16ValueRGB_SetBlue);
	}
}

/************************************************************************/
/*!	\fn						TheApp_SetReqForMotor
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
void TheApp_SetReqForMotor(float fValue)
{
	if(fValue >= LUMINOSITY_MIN && fValue <= LUMINOSITY_MAX)
	{
		fValueMotorSteps = (float)CONVERT_LUX_TO_DEGREE(fValue);
		Motor_ConvDegreeToStep_GETValueFromUSART((&fValueMotorSteps));
	}
	else
	{
		fValueMotorSteps = ZERO;
		Motor_ConvDegreeToStep_GETValueFromUSART((&fValueMotorSteps));
	}
}

/************************************************************************/
/*!	\fn						TheAPP_GetClickButton
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
void TheAPP_GetClickButton(void)
{
	u16SysClickBtn = f_GetReturnValuePeriod();
	if(u16PreviousValueBlinkBtn != u16SysClickBtn)
	{
	    f_SetValuePeriod(&ledConfig2, u16SysClickBtn);
		u16PreviousValueBlinkBtn = u16SysClickBtn;
	}
}

/************************************************************************/
/*!	\fn						TheAPP_CallBack_PWM
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
void TheAPP_CallBack_PWM(uint8_t u8CMDDataRGB, uint16_t u16ValueUSART)
{
	u16FlagCallBack = true;
	u8CMD_DataRGB = u8CMDDataRGB;
	u16Value_USART = u16ValueUSART;
}

/************************************************************************/
/*!	\fn						TheAPP_CallBack
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
void TheAPP_CallBack(uint8_t u8CMDData, uint16_t u16Value)
{
	u16FlagCallBack = true;
	u16Value_USART = u16Value;
	u8CMD_DataLed = u8CMDData;
}

/************************************************************************/
/*!	\fn						TheAPP_CallBack_Motor
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
void TheAPP_CallBack_Motor(uint8_t u8CMDDataMotor, float* fValue)
{
	u16FlagCallBack = true;
	fValueUSARTForMotor =  (*fValue);
	u8CMD_DataMotor = u8CMDDataMotor;
}

/************************************************************************/
/*!	\fn						TheAPP_CallBackReqTransmission
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
void TheAPP_CallBackReqTransmission(uint8_t u8RequestValue)
{
	u16FlagCallBack = true;
	u8RequestStateValue = u8RequestValue;
}

/************************************************************************/
/*!	\fn						TheAPP_CallBack_Luminosity
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
void TheAPP_CallBack_Luminosity(uint8_t u8CMDData, uint32_t u32Value)
{
	u16FlagCallBack = true;
	u8CMD_DataLuminosity = u8CMDData;
	u32ValueLuminosityCurrent = u32Value;
}
