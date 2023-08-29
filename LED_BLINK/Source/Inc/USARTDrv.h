/*
 * USARTDrv.h
 *
 *  Created on: Jun 20, 2023
 *      Author: romag
 */

#ifndef INC_USARTDRV_H_
#define INC_USARTDRV_H_


#include "main.h"
#include "stdio.h"
#include "stdbool.h"
#include "CircularBuffer.h"
#include "LedDrv.h"

void USARTDrv_Init(void *Ptr_USART_Init);
void USARTDrv_MainFunction(void);
void USART_SendBuffer(uint8_t* Data, uint16_t Len, uint16_t* RecievedLen);
void USART_ReceiverBuffer(uint8_t* Data, uint16_t Len, uint16_t* RecievedLen);

void USART_TxHandlerIsr(void);
void USART_RxHandlerIsr(void);

bool f_USART_GetCharData(uint8_t* u8DataInformation);
void USART_SysCallBack(void);



#endif /* INC_USARTDRV_H_ */
