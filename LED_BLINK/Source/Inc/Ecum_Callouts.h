/*
 * Ecum_Callouts.h
 *
 *  Created on: Jul 13, 2023
 *      Author: romag
 */

#ifndef INC_ECUM_CALLOUTS_H_
#define INC_ECUM_CALLOUTS_H_

#include "LedDrv.h"
#include "ButtonDrv.h"
#include "USARTDrv.h"
#include "TheAPP.h"
#include "USART_CommunicationProtocol.h"
#include "Test.h"
#include "AdcDrv.h"
#include "ADC_ConverterValue.h"
#include "CDD_Thermistor_CalcValue.h"
#include "MotorDrvStepper.h"
#include "Motor_ConverterDegreeToStep.h"
#include "PWMDrv.h"

void f_Ecum_InitBaseTask(void);
void f_Ecum_BaseRecurenceTask(void);
void f_Ecum_BaseRecurenceTaskDiv2(void);
void f_Ecum_BaseRecurenceTaskDiv4(void);
void f_Ecum_BaseRecurenceTaskDiv8(void);
void f_Ecum_BaseRecurenceTaskDiv16(void);
void f_Ecum_BaseRecurenceTaskDiv32(void);


#endif /* INC_ECUM_CALLOUTS_H_ */
