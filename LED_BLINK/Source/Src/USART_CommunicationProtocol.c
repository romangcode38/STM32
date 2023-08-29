/*
 * USART_CommunicationProtocol.c
 *
 *  Created on: 3 июл. 2023 г.
 *      Author: romag
 */

#include "USART_CommunicationProtocol.h"

#define TASK_PERIOD				(8u)
#define TIME_OUT				(70u / TASK_PERIOD)

TE_USART_StateMachine ActualState = WAIT_StartByte;

TU_USART_Packet TU_CommPacketData;
uint8_t u8PacketReceived[LENGTH_DATA_ARRAY_RECIVED];

TU_ValuePacketUSARTMotor Tu_ValuePacketUSART_Motor;


uint16_t u16DelayDataBetween;
uint8_t u8LengthReceived;
uint16_t u16DataIndex = 0u;
uint16_t u16UsartSentData = 0u;
uint16_t u16Index = 0;

uint8_t u8ResponseCMD = 0;

/************************************************************************/
/*!	\fn						f_USARTCommProt_Init
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
void f_USARTCommProt_Init(void)
{
	Tu_ValuePacketUSART_Motor.fValuePacketUSARTMotor = 0.f;
}

/************************************************************************/
/*!	\fn						f_USARTCommProt_Main
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
void f_USARTCommProt_Main(void)
{
	bool IsNotEmpty = false;
	uint8_t u8DataReceived = 0u;
	uint8_t u8CRCResult;
	do
	{
		IsNotEmpty = f_USART_GetCharData(&u8DataReceived);

		if(IsNotEmpty != false)
		{

			u16DelayDataBetween = 0;

			switch(ActualState)
			{
				case WAIT_StartByte:
				{
					if(USART_IS_START_BYTE(u8DataReceived))
					{
						TU_CommPacketData.ST_USART_Packet.StartByte = u8DataReceived;
						ActualState = WAIT_CommandByte;
					}
					break;
				}
				case WAIT_CommandByte:
				{
					if(USART_IS_SUPPORTED_CMD(u8DataReceived, CMD_LUMINOSITY_VALUE) || USART_IS_SUPPORTED_CMD(u8DataReceived, (CMD_TRANSMISION_REQUEST | CMD_TEMPERATURE_VALUE)))
					{
						TU_CommPacketData.ST_USART_Packet.CmdByte = u8DataReceived;
						ActualState = WAIT_LengthByte;
					}
					else
					{
						ActualState = WAIT_StartByte;
					}

					break;
				}
				case WAIT_LengthByte:
				{

					if (u8DataReceived > LENGTH_USART_DATA)
					{
						u8ResponseCMD = CMD_TRANSMISION_REQUEST | TU_CommPacketData.ST_USART_Packet.CmdByte;
						f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, STATE_NEDETERMINATION$, u8ResponseCMD);
						TheAPP_CallBackReqTransmission(STATE_NEDETERMINATION$);
						USART_SendBuffer(u8PacketReceived, LENGTH_DATA_ARRAY_RECIVED, &u16UsartSentData);
					}
					TU_CommPacketData.ST_USART_Packet.LengthByte = u8DataReceived;
					ActualState = WAIT_DataByte;

					break;
				}
				case WAIT_DataByte:
				{


					TU_CommPacketData.ST_USART_Packet.DataByte[u16Index] = u8DataReceived;
					u16Index++;
					if(u16Index == TU_CommPacketData.ST_USART_Packet.LengthByte)
					{
						ActualState = WAIT_CRCByte;
						u16Index = 0;
					}


					break;
				}
				case WAIT_CRCByte:
				{

				    u8CRCResult = f_USARTCommProt_IsCRCByte((TU_CommPacketData.u8USARTByteArray), (HEADER_LENGTH + TU_CommPacketData.ST_USART_Packet.LengthByte));
					if(u8DataReceived == u8CRCResult)
					{
						f_USARTCommProt_IsProcessData();

						if((CMD_TRANSMISION_REQUEST & TU_CommPacketData.ST_USART_Packet.CmdByte) == 0)
						{
							u8ResponseCMD = CMD_TRANSMISION_REQUEST | TU_CommPacketData.ST_USART_Packet.CmdByte;
						    f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, ACK_BYTE, u8ResponseCMD);
							USART_SendBuffer(u8PacketReceived, LENGTH_DATA_ARRAY_RECIVED, &u16UsartSentData);

						}
						else
						{
							TheAPP_CallBackReqTransmission(TU_CommPacketData.ST_USART_Packet.DataByte[0]);
						}
					}

					else
					{
						u8ResponseCMD = CMD_TRANSMISION_REQUEST | TU_CommPacketData.ST_USART_Packet.CmdByte;

						if((CMD_TRANSMISION_REQUEST & TU_CommPacketData.ST_USART_Packet.CmdByte) == 0)
						{
							u8ResponseCMD = CMD_TRANSMISION_REQUEST | TU_CommPacketData.ST_USART_Packet.CmdByte;
							f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, NACK_BYTE, u8ResponseCMD);
							TheAPP_CallBackReqTransmission(NACK_BYTE);
							USART_SendBuffer(u8PacketReceived, LENGTH_DATA_ARRAY_RECIVED, &u16UsartSentData);

						}
					}

					ActualState = WAIT_StartByte;
					break;
				}
			}

		}
		else
		{
			if(ActualState != WAIT_StartByte)
			{
				u16DelayDataBetween++;
			}
			if(USART_CHECK_TIMEOUT(u16DelayDataBetween))
			{
				u16DelayDataBetween = 0u;
				ActualState = WAIT_StartByte;
			}
		}


	}
	while(IsNotEmpty);
}

/************************************************************************/
/*!	\fn						f_USARTCommProt_IsCRCByte
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
uint8_t f_USARTCommProt_IsCRCByte(uint8_t* CommPacketData, uint8_t u8LengthPacket)
{
	uint8_t lu8Index = 0;
	uint8_t lu8ResultCRC = 0u;

	for (lu8Index = 0; lu8Index < u8LengthPacket; lu8Index++)
	{
		lu8ResultCRC = CommPacketData[lu8Index] ^ lu8ResultCRC;
	}
	return lu8ResultCRC;
}

/************************************************************************/
/*!	\fn						f_USARTCommProt_ClrByte
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
void f_USARTCommProt_ClrByte(TU_USART_Packet* TU_CommPacketData, uint8_t u8PositionToClean)
{
	uint8_t lu8index;
	for(lu8index = 0; lu8index < u8PositionToClean; lu8index++)
	{
		TU_CommPacketData->ST_USART_Packet.DataByte[lu8index] = 0;
		TU_CommPacketData->u8USARTByteArray[lu8index] = 0;
	}
}

/************************************************************************/
/*!	\fn						f_USARTCommProt_IsProcessData
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
void f_USARTCommProt_IsProcessData()
{
	uint16_t u16InformationData = 0;
	uint32_t u32InformationData = 0;
	uint16_t u16IndexDataMotor;
	uint16_t u16IndexDataByte = 3;

	if((TU_CommPacketData.ST_USART_Packet.CmdByte  & 0x7F) == CMD_SET_LED_PERIOD)
	{
		u16InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 8;
		u16InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1];
		TheAPP_CallBack(CMD_SET_LED_PERIOD, u16InformationData);

	}
	if((TU_CommPacketData.ST_USART_Packet.CmdByte & 0x7F) == CMD_SET_STEP_MOTOR)
	{

		for (u16IndexDataMotor = 0; u16IndexDataMotor < DATA_LENGTH_MOTOR; u16IndexDataMotor++)
		{
			Tu_ValuePacketUSART_Motor.TS_ValueUSART.u8ArrayDataMotor[u16IndexDataMotor] = TU_CommPacketData.ST_USART_Packet.DataByte[u16IndexDataByte];
			u16IndexDataByte--;
		}
		TheAPP_CallBack_Motor(CMD_SET_STEP_MOTOR, &Tu_ValuePacketUSART_Motor.fValuePacketUSARTMotor);
	}

	if((TU_CommPacketData.ST_USART_Packet.CmdByte & 0x7F) == CMD_SET_PWM_RGB_RED)
	{
		u16InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 8;
		u16InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1];
		TheAPP_CallBack_PWM(CMD_SET_PWM_RGB_RED, u16InformationData);
	}
	if((TU_CommPacketData.ST_USART_Packet.CmdByte & 0x7F) == CMD_SET_PWM_RGB_GREEN)
	{
		u16InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 8;
		u16InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1];
		TheAPP_CallBack_PWM(CMD_SET_PWM_RGB_GREEN, u16InformationData);
	}
	if((TU_CommPacketData.ST_USART_Packet.CmdByte & 0x7F) == CMD_SET_PWM_RGB_BLUE)
	{
		u16InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 8;
		u16InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1];
		TheAPP_CallBack_PWM(CMD_SET_PWM_RGB_BLUE, u16InformationData);
	}
	if((TU_CommPacketData.ST_USART_Packet.CmdByte & 0x7F) == CMD_LUMINOSITY_VALUE)
	{
		 u32InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 24;
		 u32InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1] << 16;
		 u32InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[2] << 8;
		 u32InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[3];
		 TheAPP_CallBack_Luminosity(CMD_LUMINOSITY_VALUE, u32InformationData);
	}
}

/************************************************************************/
/*!	\fn						f_USARTCommProt_IsDatPacketTightening
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
void f_USARTCommProt_IsDatPacketTightening(uint8_t* u8PacketReceived, uint8_t u8DataReceiver, uint8_t u8CMD_RequestTransm)
{
	u8PacketReceived[0] = START_BYTE_VALUE;
	u8PacketReceived[1] = u8CMD_RequestTransm;
	u8PacketReceived[2] = SIZE_BYTE_LENGTH;
	u8PacketReceived[3] = u8DataReceiver;
	u8PacketReceived[4] = f_USARTCommProt_IsCRCByte(u8PacketReceived, (LENGTH_DATA_ARRAY_RECIVED - 1));

}

/************************************************************************/
/*!	\fn						f_USARTCommProt_SendData
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
void f_USARTCommProt_SendData(uint8_t* u8PacketSend, uint8_t u8CMDSend, uint32_t u32DataSend)
{
	u8PacketSend[0] = START_BYTE_VALUE;
	u8PacketSend[1] = u8CMDSend;
	u8PacketSend[2] = SIZE_BYTE_LENGTH_DATA;
	u8PacketSend[6] = u32DataSend;
	u8PacketSend[5] = u32DataSend >> 8;
	u8PacketSend[4] = u32DataSend >> 16;
	u8PacketSend[3] = u32DataSend >> 24;
	u8PacketSend[7] = f_USARTCommProt_IsCRCByte(u8PacketSend, (LENGTH_DATA_ARRAY_SEND - 1));
	USART_SendBuffer(u8PacketSend, LENGTH_DATA_ARRAY_SEND, &u16UsartSentData);
}
