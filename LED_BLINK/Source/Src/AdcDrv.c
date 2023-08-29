/*
 * AdcDrv.c
 *
 *  Created on: 8 июл. 2023 г.
 *      Author: romag
 */

#include "AdcDrv.h"

#define ELEMENTS_OF_ARRAY (10u)

uint16_t u16ArrayElementsAdc[ELEMENTS_OF_ARRAY];
uint8_t u8Index = 0;
uint16_t u16AdcGetData = 0;

/************************************************************************/
/*!	\fn				AdcDrv_Init
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
void AdcDrv_Init(void *Ptr_Adc_Init)
{
	 void (*MX_ADC1_INIT)(void) = Ptr_Adc_Init;

	 (*MX_ADC1_INIT)();

	LL_ADC_StartCalibration(ADC1);
	while(LL_ADC_IsCalibrationOnGoing(ADC1)){}
	LL_ADC_Enable(ADC1);
}

/************************************************************************/
/*!	\fn				AdcSetConverter_Value
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
uint16_t AdcSetConverter_Value(void)
{
	return u16AdcGetData;
}

/************************************************************************/
/*!	\fn				AdcDrv_MainFunction
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
void AdcDrv_MainFunction(void)
{
	uint16_t lu16LocalVarInArray;
	uint8_t lu8LocalIndex;
	LL_ADC_REG_StartConversion(ADC1);
	while (!LL_ADC_IsActiveFlag_EOC(ADC1)){}

	u16ArrayElementsAdc[u8Index] = LL_ADC_REG_ReadConversionData12(ADC1);
	u8Index++;
	if(u8Index == ELEMENTS_OF_ARRAY)
	{

		u8Index = 0;
	}

	for(lu8LocalIndex = 0; lu8LocalIndex < ELEMENTS_OF_ARRAY; lu8LocalIndex++)
	{
		lu16LocalVarInArray += u16ArrayElementsAdc[lu8LocalIndex];

	}
	u16AdcGetData = lu16LocalVarInArray / ELEMENTS_OF_ARRAY;
}
