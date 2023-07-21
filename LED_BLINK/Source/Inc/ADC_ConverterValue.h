/*
 * ADC_ConverterValue.h
 *
 *  Created on: Jul 14, 2023
 *      Author: romag
 */

#ifndef INC_ADC_CONVERTERVALUE_H_
#define INC_ADC_CONVERTERVALUE_H_

#include "main.h"
#include "AdcDrv.h"

void Adc_ConverterValue_Init(void);
uint16_t AdcCalculateVOLTAGE(void);
void AdcConverterValue_MainFunction(void);



#endif /* INC_ADC_CONVERTERVALUE_H_ */
