/*
 * AdcDrv.h
 *
 *  Created on: 8 июл. 2023 г.
 *      Author: romag
 */

#ifndef INC_ADCDRV_H_
#define INC_ADCDRV_H_

#include "main.h"

void AdcDrv_Init(void);
void AdcDrv_MainFunction(void);
uint16_t AdcSetConverter_Value(void);

#endif /* INC_ADCDRV_H_ */
