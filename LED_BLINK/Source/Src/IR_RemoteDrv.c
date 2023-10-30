/*
 * IR_RemoteDrv.c
 *
 *  Created on: Sep 1, 2023
 *      Author: romag
 */

#include "IR_RemoteDrv.h"

#define TIME_PERIOD_IR_REMOTE	(1000u)	//1ms
#define TIME_TASK_IR_REMOTE		(4u / TIME_PERIOD_IR_REMOTE)

volatile uint8_t u8LocalIndexForIRPacket = 0u;
volatile uint32_t u32DataStorage = 0u;
uint16_t u16TimeForTask = 0u;

uint16_t* u16TemptDataStorage = 0u;
uint16_t u16UserCode = 0u;
uint16_t u16DataCode = 0u;

uint16_t u16TimeIR_Package = 0u;

uint8_t* u8TemptDataStorage = 0u;
uint8_t u8UserCodeLow = 0u;
uint8_t u8UserCodeHight = 0u;
uint8_t u8DataCodeLow = 0u;
uint8_t u8DataCodeHight = 0u;


volatile TE_IRStatePacket IRStatePacket;
TS_IR_Config IR_Config1;


/************************************************************************/
/*!	\fn				IR_RemoteDrv_Init
 *	\brief
 *
 *	\details
 *
 *	@param[in]		IR_Config
 *					TIMx
 *					u32TIMx_Pin
 *					INPUTx_Port
 *					u32INPUTx_Pin
 *
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void IR_RemoteDrv_Init(TS_IR_Config* IR_Config, TIM_TypeDef* TIMx, uint32_t u32TIMx_Pin, GPIO_TypeDef* INPUTx_Port, uint32_t u32INPUTx_Pin)
{

	IR_Config1.IR_TIMx = TIMx;
	IR_Config1.u32IR_TIMx_Pin = u32TIMx_Pin;
	IR_Config1.IR_INPUTx_Port = INPUTx_Port;
	IR_Config1.u32IR_INPUTx_Pin = u32INPUTx_Pin;

	IRStatePacket = WaitStartEdge;
	LL_TIM_EnableCounter(TIM2);

}

/************************************************************************/
/*!	\fn				IR_RemoteDrv_CallBack
 *	\brief
 *
 *	\details
 *
 *	@param[in]		u8DetectFront
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void IR_RemoteDrv_CallBack(uint8_t u8DetectFront)
{
	IR_RemoteDrv_Unpacking(u8DetectFront);
}

/************************************************************************/
/*!	\fn				IR_RemoteDrv_Unpacking
 *	\brief
 *
 *	\details
 *
 *	@param[in]		u8DataComm
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void IR_RemoteDrv_Unpacking(uint8_t u8DataComm)
{
	uint16_t u16TimeForState = 0u;

	switch(IRStatePacket)
	{
		case WaitStartEdge:
		{
			if(RISSING_FRONT != u8DataComm)
			{
				CLEAR_REG(TIM2->CNT);
				IRStatePacket = WaitStartPulseHight;
			}
			break;
		}
		case WaitStartPulseHight:
		{
			u16TimeForState = LL_TIM_GetCounter(IR_Config1.IR_TIMx);
			CLEAR_REG(TIM2->CNT);
			if((RESULT_RANGE(START_BIT_TIME) + START_BIT_TIME > u16TimeForState) && (START_BIT_TIME - RESULT_RANGE(START_BIT_TIME) < u16TimeForState))
			{
				IRStatePacket = WaitStartPulseLow;
			}
			else
			{
				IRStatePacket = WaitStartEdge;
			}
			break;
		}
		case WaitStartPulseLow:
		{
			u16TimeForState = LL_TIM_GetCounter(IR_Config1.IR_TIMx);
			CLEAR_REG(TIM2->CNT);
			if((RESULT_RANGE(STOP_BIT_TIME) + STOP_BIT_TIME > u16TimeForState) && (STOP_BIT_TIME - RESULT_RANGE(STOP_BIT_TIME) < u16TimeForState))
			{
				u8LocalIndexForIRPacket = 0u;
				u32DataStorage = 0u;
				IRStatePacket = WAIT_LOW_BIT;
			}
			else
			{
				IRStatePacket = WaitStartEdge;
			}

			break;
		}
		case WAIT_LOW_BIT:
		{
			u16TimeForState = LL_TIM_GetCounter(IR_Config1.IR_TIMx);
			CLEAR_REG(TIM2->CNT);

			if((RESULT_RANGE(LOW_BIT_TIME) + LOW_BIT_TIME > u16TimeForState) && (LOW_BIT_TIME - RESULT_RANGE(LOW_BIT_TIME) < u16TimeForState))
			{
				IRStatePacket = WaitHightBit;
			}

			else
			{
				IRStatePacket = WaitStartEdge;
			}


			break;
		}
		case WaitHightBit:
		{
			u16TimeForState = LL_TIM_GetCounter(IR_Config1.IR_TIMx);
			CLEAR_REG(TIM2->CNT);

			if((RESULT_RANGE(LOW_BIT_TIME) + LOW_BIT_TIME > u16TimeForState) && (LOW_BIT_TIME - RESULT_RANGE(LOW_BIT_TIME) < u16TimeForState))
			{
				u32DataStorage &= ~((uint32_t)(1u << u8LocalIndexForIRPacket));
				u8LocalIndexForIRPacket++;

				if(SIZE_DATA_IR == u8LocalIndexForIRPacket)
				{
					/* CALLBACK */
					IR_RemoteDrv_CallBackDataArrangement(u32DataStorage);
					IRStatePacket = WaitStartEdge;
				}
				else
				{
					IRStatePacket = WAIT_LOW_BIT;
				}
			}
			else if((RESULT_RANGE(HIGHT_BIT_TIME) + HIGHT_BIT_TIME > u16TimeForState) && (HIGHT_BIT_TIME - RESULT_RANGE(HIGHT_BIT_TIME) < u16TimeForState))
			{
				u32DataStorage |= ((uint32_t)(1u << u8LocalIndexForIRPacket));
				u8LocalIndexForIRPacket++;

				if(SIZE_DATA_IR == u8LocalIndexForIRPacket)
				{
					/* CALLBACK */
					IR_RemoteDrv_CallBackDataArrangement(u32DataStorage);
					IRStatePacket = WaitStartEdge;
				}
				else
				{
					IRStatePacket = WAIT_LOW_BIT;
				}
			}
			else
			{
				IRStatePacket = WaitStartEdge;
			}
			break;
		}
	}
}

/************************************************************************/
/*!	\fn				IR_RemoteDrv_CallBackDataArrangement
 *	\brief
 *
 *	\details
 *
 *	@param[in]		u32ValueStorage
 *	@param[out]		No output parameters
 *
 *	\return			No return value for this function

 *	\attention		No special attention
 *
 *	\note
 ************************************************************************/
void IR_RemoteDrv_CallBackDataArrangement(uint32_t u32ValueStorage)
{

/*	We save bits with the help of pointers - 8bits
	u8TemptDataStorage = (uint8_t*)&u32ValueStorage;

	u8UserCodeLow = REVERS_DATA_BITE_IR(*((uint8_t*)u8TemptDataStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8UserCodeLow);

	u8UserCodeHight = REVERS_DATA_BITE_IR(*((uint8_t*)++u8TemptDataStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8UserCodeHight);

	u8TemptDataStorage = u8TemptDataStorage + 2;
	u8DataCodeHight = REVERS_DATA_BITE_IR(*((uint8_t*)u8TemptDataStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8DataCodeHight);

	u8DataCodeLow = REVERS_DATA_BITE_IR(*((uint8_t*)--u8TemptDataStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8DataCodeLow);
*/

/* Setting bits using the MASC
	u8UserCodeLow = REVERS_DATA_BITE_IR(MASC_USER_CODE_LOW(u32ValueStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8UserCodeLow);

	u8UserCodeHight = REVERS_DATA_BITE_IR(MASC_USER_CODE_HIGHT(u32ValueStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8UserCodeHight);

	u8DataCodeHight = REVERS_DATA_BITE_IR(MASC_DATA_CODE_HIGHT(u32ValueStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8DataCodeHight);

	u8DataCodeLow = REVERS_DATA_BITE_IR(MASC_DATA_CODE_LOW(u32ValueStorage));
	f_addElemFIFOBuffer(&CircularFIFOBuffer_IR_Remote, u8DataCodeLow);
*/

	u16TemptDataStorage = (uint16_t*)&u32ValueStorage;
	u16UserCode = REVERS_DATA_BITE_IR(*((uint16_t*)u16TemptDataStorage));
	u16DataCode = REVERS_DATA_BITE_IR(*((uint16_t*)++u16TemptDataStorage));

	if(IS_SUPPORTED_COMMAND_IR(u16UserCode, IR_REMOTE_CONTROL_ORIGINAL))
	{
		TheAPP_CallBack_GetIR_Remote_Value(u32ValueStorage);
	}
}

void IR_RemoteDrv_MainFunction(void)
{
	if(TIME_TASK_IR_REMOTE <= u16TimeForTask)
	{
		if(IRStatePacket == WaitStartEdge)
		{
			u16TimeIR_Package = 0;
		}
		else if(TIME_CHECKOUT_PACKAGE_IR(u16TimeIR_Package))
		{
			u16TimeIR_Package = 0;
			IRStatePacket = WaitStartEdge;
		}
		else
		{
			u16TimeIR_Package++;
		}
		u16TimeForTask= 0;
	}
	else
	{
		u16TimeForTask++;
	}
}
