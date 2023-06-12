/*
 * ButtonDrv.h
 *
 *  Created on: Jun 6, 2023
 *      Author: romag
 */

#ifndef INC_BUTTONDRV_H_
#define INC_BUTTONDRV_H_

#include <stdbool.h>


void ButtonDrv_Init(void);
uint16_t SetPeriod(void);
void ButtonDrv_MainFunction(void);
void ChangeButtonVallue(uint16_t u16IdBtn, uint32_t u32_CurrentTick);
void ButtonDrv_SysClickCallback(void);




#endif /* INC_BUTTONDRV_H_ */
