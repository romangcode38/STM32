/*
 * LedDrv.h
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#ifndef LEDDRV_H_
#define LEDDRV_H_

#include "main.h"
#include "stdbool.h"

typedef struct {
	GPIO_TypeDef* Ledx_Port;
    uint32_t u32Ledx_Pin;
    uint16_t u16Ledx_Period;
    uint16_t u16Ledx_Timer;
}TS_LedConfig;

void LedDrv_Init(TS_LedConfig* ledConfig, GPIO_TypeDef* Port, uint16_t Pin);
void LedDrv_MainFunction(TS_LedConfig* ledConfig);
void f_SetValuePeriod(TS_LedConfig* ledConfig, uint16_t u16BlinkLed);



#endif /* LEDDRV_H_ */
