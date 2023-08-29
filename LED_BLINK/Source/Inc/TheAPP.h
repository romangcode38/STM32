/*
 * TheAPP.h
 *
 *  Created on: Jun 27, 2023
 *      Author: romag
 */

#ifndef INC_THEAPP_H_
#define INC_THEAPP_H_

#include "main.h"
#include "USARTDrv.h"
#include "CDD_Thermistor_CalcValue.h"
#include "USART_CommunicationProtocol.h"
#include "LedDrv.h"
#include "ButtonDrv.h"
#include "MotorDrvStepper.h"
#include "Motor_ConverterDegreeToStep.h"
#include "PWMDrv.h"


#define DATA_FOR_LED		(0x01)
#define DATA_FOR_STEP_MOTOR	(0x02)



#define SEND_PACKET_DATA	(9u)

#define OFFSET_VALUE_FOR_LUMINOSITY	(1000u)

#define LUMINOSITY_MAX				(10000000u)
#define LUMINOSITY_MIDDLE			(5000u)
#define LUMINOSITY_MIN				(30u)
#define ZERO						(0u)
#define POSITION_DREGEE_MAX_MOTOR	(90u)

#define TIME_TRANSMISSION_TEMP		(500u)


#define ACK_PACKET_BLINK			(1000u)
#define NACK_PACKET_BLINK			(100u)
#define NO_COMM_PACKET_BLINK		(500u)


#define CALC_VALUE_TO_LUX(Value)		((float) Value)
#define CONVERT_LUX_TO_DEGREE(Value)	(((((Value) - LUMINOSITY_MIN) * POSITION_DREGEE_MAX_MOTOR) / (LUMINOSITY_MAX - LUMINOSITY_MIN)))


#define CONVERT_LUX_TO_RGB_RED(Value)			(((Value - LUMINOSITY_MIDDLE) * 1000) / (LUMINOSITY_MAX - LUMINOSITY_MIDDLE))
#define CONVERT_LUX_TO_RGB_BLUE_UP(Value)		(((Value - LUMINOSITY_MIDDLE) * 1000) / (LUMINOSITY_MAX - LUMINOSITY_MIDDLE))

#define CONVERT_LUX_TO_RGB_GREEN(Value)			(((Value - LUMINOSITY_MIN) * 1000) / (LUMINOSITY_MIDDLE - LUMINOSITY_MIN))
#define CONVERT_LUX_TO_RGB_BLUE_DOWN(Value)		(((Value - LUMINOSITY_MIN) * 1000) / (LUMINOSITY_MIDDLE - LUMINOSITY_MIN))

#define CALCULATE_PERCENTAGE_ON_LUMINOSITY(Value) 	((Value * 10) / 100)

#define CHECK_TIMEOUT(ValueTime)		((ValueTime > TIME_OUT_PACKET) ? true : false)


typedef union
{
	struct
	{
		uint8_t u8FirstBit;
		uint8_t u8SecondBit;
	}BytesofData;
	uint16_t u16InfoBits;
}ByteBitField;


typedef enum
{
	NO_COMM = 0,			/*500/500*/
	NORMAL_COMM,			/*1000/1000 TRECE IN NORMAL DIN NO_COMM CHIND PRIMESTE 1 PACKET*/
	LOST_COMM,				/*500/500 1 SECUNDA DACA NU A PRIMIT NICI UN PACKET, DIN LOST_COM IN NORMAL_COMM CHIND A PRIMIT 2 PACKETE LA RIND*/
	ERROR_COMM 				/*100/100*/
}TE_CommunicationState;

void TheApp_Init(void);
void TheAPP_MainFunction(void);
void TheAPP_GetClickButton(void);
void TheApp_VerificationHysteresis(void);
void TheApp_CommunicationStateProtocol(void);
void TheAPP_CallBackReqTransmission(uint8_t u8RequestValue);
void TheApp_SendTemperatureToUSART(void);
void TheApp_SetReqForMotor(float fValue);
void TheApp_SetReqForLedRGB(float fValue);
void TheAPP_CallBack_PWM(uint8_t u8CMDDataRGB, uint16_t u16ValueUSART);
void TheAPP_CallBack(uint8_t u8CMDData, uint16_t u16Value);
void TheAPP_CallBack_Motor(uint8_t u8CMDDataMotor, float* fValue);
void TheAPP_CallBack_Luminosity(uint8_t u8CMDData, uint32_t u32Value);

#endif /* INC_THEAPP_H_ */
