/*
 * USARTDrv.c
 *
 *  Created on: Jun 20, 2023
 *      Author: romag
 */

#include "USARTDrv.h"


#define TIMER_TASK (1000 / 1)

uint8_t BufferTx[15];
uint8_t BufferRx[15];

//uint16_t u16USART_Timer = 0u;

int counter = 0;

CircularFIFOBuffer Tx_CircularFIFOBuffer;
volatile uint16_t u16Temp;
CircularFIFOBuffer Rx_CircularFIFOBuffer;

/************************************************************************/
/*!	\fn						USARTDrv_Init
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USARTDrv_Init(void *Ptr_USART_Init)
{
	void (*MX_USART_INIT)(void) = Ptr_USART_Init;
	(*MX_USART_INIT)();

	LL_USART_EnableIT_RXNE(USART1);
	u16Temp = 10;
	Tx_CircularFIFOBuffer.u16Head = 0u;
	Tx_CircularFIFOBuffer.u16Tail = 0u;

	Rx_CircularFIFOBuffer.u16Head = 0u;
	Rx_CircularFIFOBuffer.u16Tail = 0u;
}



/*	Function for checking the work of the USART
void USARTDrv_MainFunction(void)
{
	 uint16_t u16_length = 0u;

	 if(u16USART_Timer > TIMER_TASK)
	 {
		 u16USART_Timer=0;
		 counter++;
		 u16_length = sprintf((uint8_t *)BufferTx, "String :%d\n", counter);

		 USART_SendBuffer(BufferTx, 15, &u16_length);

	}
	 u16USART_Timer++;
}
*/

/************************************************************************/
/*!	\fn						USART_SendBuffer
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USART_SendBuffer(uint8_t* Data, uint16_t Len, uint16_t* RecievedLen)
{
	uint16_t u16_Len = 0u;
	*RecievedLen = 0u;

	__disable_irq();
	while( (!f_isFullFIFOBuffer(&Tx_CircularFIFOBuffer)) &&  (Len > (u16_Len)) )
	{

		f_addElemFIFOBuffer(&Tx_CircularFIFOBuffer, *Data);
		Data++;
		u16_Len++;
		(*RecievedLen)++;
	}
	USART_TxHandlerIsr();
	__enable_irq();
}

/************************************************************************/
/*!	\fn						USART_ReceiverBuffer
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USART_ReceiverBuffer(uint8_t* Data, uint16_t Len, uint16_t* RecievedLen)
{
	uint16_t u16_Len = 0u;
	*RecievedLen = 0u;

	while((!f_isEmptyFIFOBuffer(&Rx_CircularFIFOBuffer)) && (Len > u16_Len))
	{
		f_getElemFIFOBuffer(&Rx_CircularFIFOBuffer, Data);
//		LL_USART_TransmitData8(USART1, Data);

		Data++;
		u16_Len++;
		(*RecievedLen)++;
	}

}

/************************************************************************/
/*!	\fn						USART_SysCallBack
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USART_SysCallBack(void)
{
	__disable_irq();
	  /*Reset parity error*/
	  	if( (0u != LL_USART_IsActiveFlag_PE(USART1)) && (0u != LL_USART_IsEnabledIT_PE(USART1)) )
	  	{
	  		LL_USART_ClearFlag_PE(USART1);
	  	}

	  	/*Reset frame error*/
	  	if( (0u != LL_USART_IsActiveFlag_FE(USART1)) && (0u != LL_USART_IsEnabledIT_ERROR(USART1)) )
	  	{
	  		LL_USART_ClearFlag_FE(USART1);
	  	}

	  	/*Reset noise error*/
	  	if( (0u != LL_USART_IsActiveFlag_NE(USART1)) && (0u != LL_USART_IsEnabledIT_ERROR(USART1)) )
	  	{
	  		LL_USART_ClearFlag_NE(USART1);
	  	}

	  	/*Reset Over-run error*/
	  	if( (0u != LL_USART_IsActiveFlag_ORE(USART1)) && (0u != LL_USART_IsEnabledIT_ERROR(USART1)) )
	  	{
	  		LL_USART_ClearFlag_ORE(USART1);
	  	}

	  	/*RX interrupt*/
	  	if( (0u != LL_USART_IsActiveFlag_RXNE(USART1)) && (0u != LL_USART_IsEnabledIT_RXNE(USART1)) )
	  	{

	  		USART_RxHandlerIsr();

	  	}

	  	/*TX buffer empty interrupt*/
		if( (0u != LL_USART_IsActiveFlag_TXE(USART1)) && (0u != LL_USART_IsEnabledIT_TXE(USART1)) )
	  	{
	  		LL_USART_DisableIT_TXE(USART1);
	  		USART_TxHandlerIsr();

	  	}

	  	/*TX completed interrupt*/
	  	if( (0u != LL_USART_IsActiveFlag_TC(USART1)) && (0u != LL_USART_IsEnabledIT_TC(USART1)) )
	  	{
	  		LL_USART_DisableIT_TC(USART1);
	  		LL_USART_ClearFlag_TC(USART1);
	  	}
	  	__enable_irq();
}

/************************************************************************/
/*!	\fn						USART_RxHandlerIsr
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USART_RxHandlerIsr(void)
{
//	__disable_irq();
	f_addElemFIFOBuffer(&Rx_CircularFIFOBuffer, LL_USART_ReceiveData8(USART1));
//	__enable_irq();
}

/************************************************************************/
/*!	\fn						USART_TxHandlerIsr
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
void USART_TxHandlerIsr(void)
{
	uint8_t u8LocalElements;
	while( (!f_isEmptyFIFOBuffer(&Tx_CircularFIFOBuffer)) && ( 0u != LL_USART_IsActiveFlag_TXE(USART1) ) )
	{
		f_getElemFIFOBuffer(&Tx_CircularFIFOBuffer, &u8LocalElements);
		LL_USART_TransmitData8(USART1, u8LocalElements);
	}

	if(!f_isEmptyFIFOBuffer(&Tx_CircularFIFOBuffer))
	{
		LL_USART_EnableIT_TXE(USART1);
	}
	else
	{
		LL_USART_EnableIT_TC(USART1);
	}
}

/************************************************************************/
/*!	\fn						f_USART_GetCharData
 *	\brief
 *
 *	\details
 *
 *	@param[in]
 *	@param[out]
 *
 *	\return

 *	\attention
 *
 *	\note
 ************************************************************************/
bool f_USART_GetCharData(uint8_t* u8DataInformation)
{
	bool lbReturnValue = false;
	__disable_irq();
	if(!f_isEmptyFIFOBuffer(&Rx_CircularFIFOBuffer))
	{
		f_getElemFIFOBuffer(&Rx_CircularFIFOBuffer, u8DataInformation);
		lbReturnValue = true;
	}
	__enable_irq();
	return lbReturnValue;
}
