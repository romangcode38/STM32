/*
 * CDD_Thermistor_CalcValue.h
 *
 *  Created on: Jul 14, 2023
 *      Author: romag
 */

#ifndef INC_CDD_THERMISTOR_CALCVALUE_H_
#define INC_CDD_THERMISTOR_CALCVALUE_H_

#include "main.h"
#include "ADC_ConverterValue.h"


void Thermistor_InitFunction(void);
uint16_t Theemistor_GetTemperatureFunction(void);
void Thermistor_MainFunction(void);


#endif /* INC_CDD_THERMISTOR_CALCVALUE_H_ */
