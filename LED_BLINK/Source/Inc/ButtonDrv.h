/*
 * ButtonDrv.h
 *
 *  Created on: Jun 6, 2023
 *      Author: romag
 */

#ifndef INC_BUTTONDRV_H_
#define INC_BUTTONDRV_H_

#include <stdbool.h>
#include "LedDrv.h"
#include "main.h"

typedef struct
{
	GPIO_TypeDef* Port;
	uint32_t Pin;
	uint16_t PrevState;

}ButtonConfig;


void ButtonDrv_Init(ButtonConfig* buttonConfig, GPIO_TypeDef* Port, uint32_t Pin);
void SetPeriod(uint16_t u16StateBtn);
uint32_t f_ReturnValuePeriod();
void ButtonDrv_MainFunction(void);
void ChangeButtonVallue(uint16_t u16IdBtn, uint32_t u32_CurrentTick);
void ButtonDrv_SysClickCallback(void);
uint32_t f_GetReturnValuePeriod();




#endif /* INC_BUTTONDRV_H_ */
