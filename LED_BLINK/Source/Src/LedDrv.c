/*
 * LedDrv.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#include "main.h"


unsigned int ru32_LedTimer = 0u;
volatile unsigned int uLedBlink = 0;

typedef struct {
    uint16_t u16LedSts;
    uint16_t u16LedId;
    uint16_t u16LedPeriod;
}LedConfig;


LedConfig ledConfig;

void LedDrv_Init(void)
{
	LED_GREEN_GPIO_Port ->BRR = LED_GREEN_Pin;
//	LED_RED_GPIO_Port ->BRR = LED_RED_Pin;

}

void f_ConfigValueSet(unsigned int u16Sts,unsigned int u16Id, unsigned int u16Period)
{
	ledConfig.u16LedSts = u16Sts;
	ledConfig.u16LedId = u16Id;
	ledConfig.u16LedPeriod = u16Period;
}

void LedDrv_MainFunction(void)
{
	if(ledConfig.u16LedSts != 0u)
	{
		if (ledConfig.u16LedId == 2)
		{
			uLedBlink = 1000 / ledConfig.u16LedPeriod;
			if(uLedBlink <= ru32_LedTimer++)
			{
				uint32_t odr = READ_REG(LED_RED_GPIO_Port->ODR);
				WRITE_REG(LED_RED_GPIO_Port->BSRR, ((odr & LED_RED_Pin) << 16u) | (~odr & LED_RED_Pin));
				ru32_LedTimer = 0u;
			}
		}
		else if (ledConfig.u16LedId == 1)
		{
			uLedBlink = 1000 / ledConfig.u16LedPeriod;
			if(uLedBlink <= ru32_LedTimer++)
			{
				uint32_t odr = READ_REG(LED_GREEN_GPIO_Port->ODR);
				WRITE_REG(LED_GREEN_GPIO_Port->BSRR, ((odr & LED_GREEN_Pin) << 16u) | (~odr & LED_GREEN_Pin));
				ru32_LedTimer = 0u;
			}
		}
	}
}
