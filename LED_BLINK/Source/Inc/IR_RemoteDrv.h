/*
 * IR_RemoteDrv.h
 *
 *  Created on: Sep 1, 2023
 *      Author: romag
 */

#ifndef INC_IR_REMOTEDRV_H_
#define INC_IR_REMOTEDRV_H_

#include "main.h"
#include "TheAPP.h"
#include "CircularBuffer.h"


#define TIME_ONE_MS						(1000)
#define TIME_FOR_TASK					(4u)
#define TIME_DELAY_PACKAGE				(100u)
#define TIME_CHECKOUT_PACKAGE_IR(Value) ((TIME_DELAY_PACKAGE <= Value) ? true : false)

#define RISSING_FRONT	(1u)
#define FALLING_FRONT	(0u)
#define VALUE_RANGE		(30u)
#define START_BIT_TIME	(57600u)
#define STOP_BIT_TIME	(28800u)
#define LOW_BIT_TIME	(3600u)
#define HIGHT_BIT_TIME	(10800u)
#define SIZE_DATA_IR	(32u)

#define MASC_USER_CODE_HIGHT(Value)     (Value & 0x000000FF)
#define MASC_USER_CODE_LOW(Value)       ((Value & 0x0000FF00) >> 8)
#define MASC_DATA_CODE_HIGHT(Value)     ((Value & 0x00FF0000) >> 16)
#define MASC_DATA_CODE_LOW(Value)       ((Value & 0xFF000000) >> 24)

#define REVERS_DATA_BITE_IR(Value)	(Value ^ 0xFFFF)
#define RESULT_RANGE(Value)	((Value * VALUE_RANGE) / 100)

#define IR_REMOTE_CONTROL_ORIGINAL		(0x00FF)

#define IS_SUPPORTED_COMMAND_IR(ValueIN, ValueEXIST)	(ValueIN == ValueEXIST)

typedef struct
{
    TIM_TypeDef* IR_TIMx;
    uint32_t u32IR_TIMx_Pin;
	GPIO_TypeDef* IR_INPUTx_Port;
	uint32_t u32IR_INPUTx_Pin;
}TS_IR_Config;

typedef enum
{
	WaitStartEdge = 0,
	WaitStartPulseHight,
	WaitStartPulseLow,
	WAIT_LOW_BIT,
	WaitHightBit
}TE_IRStatePacket;

void IR_RemoteDrv_Init(TS_IR_Config* IR_Config, TIM_TypeDef* TIMx, uint32_t u32TIMx_Pin, GPIO_TypeDef* INPUTx_Port, uint32_t u32INPUTx_Pin);
void IR_RemoteDrv_CallBack(uint8_t u8DetectFront);
void IR_RemoteDrv_CallBackDataArrangement(uint32_t u32ValueStorage);

void IR_RemoteDrv_Unpacking(uint8_t u8DataComm);
void IR_RemoteDrv_MainFunction(void);

#endif /* INC_IR_REMOTEDRV_H_ */
