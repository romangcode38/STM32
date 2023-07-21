/*
 * ADC_ConverterValue.c
 *
 *  Created on: Jul 14, 2023
 *      Author: romag
 */

#include "ADC_ConverterValue.h"

#define VREFANALOG_VOLTAGE	(3300u)
#define ADC_RESOLUTION		(4095u)
#define ADC_VOLTAGE(ADC_GetData)	((ADC_GetData * VREFANALOG_VOLTAGE) / ADC_RESOLUTION)

uint16_t u16VolageAdc;

void Adc_ConverterValue_Init(void)
{
	u16VolageAdc = 0;
}

uint16_t AdcCalculateVOLTAGE(void)
{
	return u16VolageAdc = ADC_VOLTAGE(AdcSetConverter_Value());
}


void AdcConverterValue_MainFunction(void)
{
	AdcCalculateVOLTAGE();
}
