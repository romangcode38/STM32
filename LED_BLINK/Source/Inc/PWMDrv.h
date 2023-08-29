/*
 * PWMDrv.h
 *
 *  Created on: Jul 22, 2023
 *      Author: romag
 */

#ifndef INC_PWMDRV_H_
#define INC_PWMDRV_H_

#include "main.h"
#include "stdbool.h"
#include "Std_Types.h"
#include "TheAPP.h"

typedef struct
{
	TIM_TypeDef* TIM_Port;
	uint32_t u32TIM_Pin;
	uint16_t u16TIM_ActualValue;
	void *f_SetCompare;
}TS_PWMConfig;

void f_PWMDrv_Init(TS_PWMConfig* PWM_Config, TIM_TypeDef* TIMx_Port, uint32_t u32TIMx_Pin, uint16_t u16TIMx_ActualValue, TFP_SetCompare SetCompare);
void f_PWMDrv_SetVal_RGB(TS_PWMConfig* Ts_PWMConfig_RGB, uint16_t* u16Percentage);
void f_PWMDrv_MainFunction(void);


#endif /* INC_PWMDRV_H_ */
