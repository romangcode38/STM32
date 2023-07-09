/*
 * AdcDrv.h
 *
 *  Created on: 8 июл. 2023 г.
 *      Author: romag
 */

#ifndef INC_ADCDRV_H_
#define INC_ADCDRV_H_

void AdcDrv_Init(void);
void AdcDrv_MainFunction(void);
void AdcConverter_Value(void);
uint8_t AdcExtract_Value(void);

#endif /* INC_ADCDRV_H_ */
