/*
 * LedDrv.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#include "LedDrv.h"
volatile unsigned int uLedBlink = 0;


#define TIME_TASK	(4u)



TS_LedConfig ledConfig1;
TS_LedConfig ledConfig2;
TS_LedConfig ledConfig3;
TS_LedConfig ledConfig4;

void LedDrv_Init(TS_LedConfig* ledConfig, GPIO_TypeDef* Port, uint16_t Pin)
{
	ledConfig->LedPort = Port;
	ledConfig->u32LedPin = Pin;
	ledConfig->u16LedPeriod = 0;
	ledConfig->u16LedTimer = 0;

	Port ->BRR = Pin;
}



void f_SetValuePeriod(TS_LedConfig* ledConfig, uint16_t u16BlinkLed)
{
	ledConfig->u16LedPeriod = u16BlinkLed;
}

void LedDrv_MainFunction(TS_LedConfig* ledConfig)
{
 	if(ledConfig->u16LedPeriod <= ledConfig->u16LedTimer++)
	{
		LL_GPIO_TogglePin(ledConfig->LedPort, ledConfig->u32LedPin);
		ledConfig->u16LedTimer = 0;
	}
}
