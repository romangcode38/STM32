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

/************************************************************************/
/*!	\fn				Adc_ConverterValue_Init
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void Adc_ConverterValue_Init(void)
{
	u16VolageAdc = 0;
}

/************************************************************************/
/*!	\fn				AdcCalculateVOLTAGE
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
uint16_t AdcCalculateVOLTAGE(void)
{
	return u16VolageAdc = ADC_VOLTAGE(AdcSetConverter_Value());
}

/************************************************************************/
/*!	\fn				AdcConverterValue_MainFunction
 *	\brief
 *
 *	\details
 *
 *	@param[in]		No input parameters
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void AdcConverterValue_MainFunction(void)
{
	AdcCalculateVOLTAGE();
}
