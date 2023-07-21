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
#include "LedDrv.h"

typedef union
{
	struct
	{
		uint8_t u8FirstBit;
		uint8_t u8SecondBit;
	}BytesofData;
	uint16_t u16InfoBits;
}ByteBitField;

void TheApp_Init(void);
void TheAPP_MainFunction(void);
void TheAPP_GetClickButton(void);

void TheAPP_GetDataFromUSART(uint8_t* BufferData, uint16_t Len, uint16_t* RecievedLen);
uint16_t TheAPP_SetPeriodParameters(uint16_t u16ValueSet);

void TheAPP_CallBack(uint8_t u8CMDData, uint16_t u16Value);
void TheAPP_CallBack_Motor(uint8_t u8CMDDataMotor, float* fValue);




#endif /* INC_THEAPP_H_ */
