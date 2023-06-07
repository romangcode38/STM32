/*
 * LedDrv.c
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#include "main.h"
#include "LedDrv.h"

#define TASK_PERIOD1		(1u)
#define TASK_PERIOD2		(5u)
#define TASK_PERIOD3		(20u)

#define LED_BLINK1		(1000u/TASK_PERIOD1)
#define LED_BLINK2		(1000u/TASK_PERIOD2)
#define LED_BLINK3		(1000u/TASK_PERIOD3)

static unsigned int ru32_LedTimer = 0u;

void LedDrv_Init(void)
{
//	LL_GPIO_SetOutputPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	LED_GREEN_GPIO_Port ->BSRR = LED_GREEN_Pin;
}

void LedDrv_MainFunction1(void)
{
	ru32_LedTimer++;
	if(LED_BLINK1 <= ru32_LedTimer)
	{
//		LL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		uint32_t odr = READ_REG(LED_GREEN_GPIO_Port->ODR);
		WRITE_REG(LED_GREEN_GPIO_Port->BSRR, ((odr & LED_GREEN_Pin) << 16u) | (~odr & LED_GREEN_Pin));
		ru32_LedTimer = 0u;
	}
}

void LedDrv_MainFunction2(void)
{
	ru32_LedTimer++;
	if(LED_BLINK2 <= ru32_LedTimer)
	{
		uint32_t odr = READ_REG(LED_GREEN_GPIO_Port->ODR);
		WRITE_REG(LED_GREEN_GPIO_Port->BSRR, ((odr & LED_GREEN_Pin) << 16u) | (~odr & LED_GREEN_Pin));
		ru32_LedTimer = 0u;
	}
}

void LedDrv_MainFunction3(void)
{
	ru32_LedTimer++;
	if(LED_BLINK3 <= ru32_LedTimer)
	{
		uint32_t odr = READ_REG(LED_GREEN_GPIO_Port->ODR);
		WRITE_REG(LED_GREEN_GPIO_Port->BSRR, ((odr & LED_GREEN_Pin) << 16u) | (~odr & LED_GREEN_Pin));
		ru32_LedTimer = 0u;
	}
}
