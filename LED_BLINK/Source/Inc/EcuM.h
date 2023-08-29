/*
 * Ecum.h
 *
 *  Created on: Jun 5, 2023
 *      Author: romag
 */

#ifndef ECUM_H_
#define ECUM_H_

#include <stdbool.h>
#include "main.h"
#include "stm32g0xx_ll_rcc.h"
#include "Ecum_Callouts.h"

#define SCHM_BASE_DIV_1
#define SCHM_BASE_DIV_2		(0x01u)
#define SCHM_BASE_DIV_4		(0x02u)
#define SCHM_BASE_DIV_8		(0x04u)
#define SCHM_BASE_DIV_16	(0x08u)
#define SCHM_BASE_DIV_32	(0x10u)

void EcuM_Init(void);
void EcuM_MainFunction(void);
void EcuM_MainFunction(void);
void EcuM_SysTickCallBack(void);

#endif /* ECUM_H_ */
