/*
 * LedDrv.h
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#ifndef LEDDRV_H_
#define LEDDRV_H_

#include "main.h"

void LedDrv_Init(void);
void LedDrv_MainFunction(void);
void f_ConfigValueSet(unsigned int u16Sts, unsigned int u16IdLed, unsigned int u16Period);



#endif /* LEDDRV_H_ */
