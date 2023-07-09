/*
 * USART_CommunicationProtocol.c
 *
 *  Created on: 3 июл. 2023 г.
 *      Author: romag
 */

#include "USART_CommunicationProtocol.h"


TE_USART_StateMachine ActualState = WAIT_StartByte;
TU_USART_Packet TU_CommPacketData;
uint8_t u8PacketReceived[LENGTH_DATA_ARRAY_RECIVED];


uint16_t u16DelayDataBetween;
uint8_t u8LengthReceived;
uint16_t u16DataIndex = 0u;
uint16_t u16UsartSentData = 0u;
uint16_t u16Index = 0;

/*---------------------------------------------------------*/

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
					if(USART_IS_SUPPORTED_CMD(u8DataReceived, CMD_SET_LED_PERIOD))
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

						f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, STATE_NEDETERMINATION$);
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
				    u8CRCResult = f_USARTCommProt_IsCRCByte((&TU_CommPacketData.u8USARTByteArray), (HEADER_LENGTH + TU_CommPacketData.ST_USART_Packet.LengthByte));
					if(u8CRCResult == u8DataReceived)
					{
						f_USARTCommProt_IsProcessData();
						f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, ACK_BYTE);
						USART_SendBuffer(u8PacketReceived, LENGTH_DATA_ARRAY_RECIVED, &u16UsartSentData);

					}
					else
					{
						f_USARTCommProt_IsDatPacketTightening(u8PacketReceived, NACK_BYTE);
						USART_SendBuffer(u8PacketReceived, LENGTH_DATA_ARRAY_RECIVED, &u16UsartSentData);
					}
					ActualState = WAIT_StartByte;
					break;
				}
			}
		}
		else if(USART_CHECK_TIMEOUT(u16DelayDataBetween))
		{
			u16DelayDataBetween = 0u;
			ActualState = WAIT_StartByte;
		}

		u16DelayDataBetween++;
	}
	while(IsNotEmpty);
}

/*---------------------------------------------------------*/

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

/*---------------------------------------------------------*/

void f_USARTCommProt_ClrByte(TU_USART_Packet* TU_CommPacketData, uint8_t u8PositionToClean)
{
	uint8_t lu8index;
	for(lu8index = 0; lu8index < u8PositionToClean; lu8index++)
	{
		TU_CommPacketData->ST_USART_Packet.DataByte[lu8index] = 0;
		TU_CommPacketData->u8USARTByteArray[lu8index] = 0;
	}
}

/*---------------------------------------------------------*/

void f_USARTCommProt_IsProcessData()
{
	uint16_t u16InformationData = 0;

	if(TU_CommPacketData.ST_USART_Packet.CmdByte == CMD_SET_LED_PERIOD)
	{
		u16InformationData = TU_CommPacketData.ST_USART_Packet.DataByte[0] << 8;
		u16InformationData |= TU_CommPacketData.ST_USART_Packet.DataByte[1];
		TheAPP_CallBack(u16InformationData);

	}
}

/*---------------------------------------------------------*/


void f_USARTCommProt_IsDatPacketTightening(uint8_t* u8PacketReceived, uint8_t u8DataReceiver)
{
	u8PacketReceived[0] = START_BYTE_VALUE;
	u8PacketReceived[1] = CMD_TRANSMISION_REQUEST;
	u8PacketReceived[2] = SIZE_BYTE_LENGTH;
	u8PacketReceived[3] = u8DataReceiver;
	u8PacketReceived[4] = f_USARTCommProt_IsCRCByte(u8PacketReceived, (LENGTH_DATA_ARRAY_RECIVED - 1));

}
