/*
 * LedDrv.h
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#ifndef LEDDRV_H_
#define LEDDRV_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef* LedPort;
    uint32_t u32LedPin;
    uint16_t u16LedPeriod;
    uint16_t u16LedTimer;
}TS_LedConfig;

void LedDrv_Init(TS_LedConfig* ledConfig, GPIO_TypeDef* Port, uint16_t Pin);
void LedDrv_MainFunction(TS_LedConfig* ledConfig);
void f_SetValuePeriod(TS_LedConfig* ledConfig, uint16_t u16BlinkLed);



#endif /* LEDDRV_H_ */
