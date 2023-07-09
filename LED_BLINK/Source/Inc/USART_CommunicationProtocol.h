/*
 * USART_CommunicationProtocol.h
 *
 *  Created on: 3 июл. 2023 г.
 *      Author: romag
 */

#ifndef INC_USART_COMMUNICATIONPROTOCOL_H_
#define INC_USART_COMMUNICATIONPROTOCOL_H_

#include "main.h"
#include "TheAPP.h"
#include "USARTDrv.h"
#include "stdbool.h"


#define LENGTH_DATA_ARRAY		(2u)
#define LENGTH_USART_DATA (LENGTH_DATA_ARRAY + 4u)
#define LENGTH_DATA_ARRAY_RECIVED (5u)

#define TIME_OUT				(100u)


#define START_BYTE_VALUE		(0xAA)
#define ACK_BYTE				(0x06)
#define NACK_BYTE				(0x15)
#define STATE_NEDETERMINATION$	(0x24)

#define CMD_TRANSMISION_REQUEST	(0x81)

#define CMD_SET_LED_PERIOD		(0x01)
#define CMD_SET_MOTOR_DR		(0x02)
#define CMD_SET_MOTOR_DL		(0x03)

#define USART_IS_START_BYTE(Byte)			((Byte == START_BYTE_VALUE) ? true : false)
#define USART_IS_SUPPORTED_CMD(Byte,CMD)	((Byte == CMD) ? true : false)
#define USART_CHECK_TIMEOUT(ValueTime)		((ValueTime >= TIME_OUT) ? true : false)



#define BUFFER_LENGTH	(10u)
#define START_BYTE_LENGTH	(1u)
#define SIZE_BYTE_LENGTH	(1u)
#define CMD_BYTE_LENGTH	(1u)
#define HEADER_LENGTH	(START_BYTE_LENGTH + SIZE_BYTE_LENGTH + CMD_BYTE_LENGTH)
#define DATA_LENGTH		(BUFFER_LENGTH - HEADER_LENGTH)
#define HEADER_LENGHT_DATA	(HEADER_LENGTH + SIZE_LENGTH)

typedef enum
{
	WAIT_StartByte,
	WAIT_CommandByte,
	WAIT_LengthByte,
	WAIT_DataByte,
	WAIT_CRCByte,
	ProcessDataByte
}TE_USART_StateMachine;

typedef union
{
	uint8_t u8USARTByteArray[LENGTH_USART_DATA];
	struct
	{
		uint8_t StartByte;
		uint8_t CmdByte;
		uint8_t LengthByte;
		uint8_t DataByte[DATA_LENGTH];
	}ST_USART_Packet;
}TU_USART_Packet;


uint8_t f_USARTCommProt_IsCRCByte(uint8_t* CommPacketData, uint8_t u8LengthPacket);
void f_USARTCommProt_Main(void);
void f_USARTCommProt_ClrByte(TU_USART_Packet* TU_CommPacketData, uint8_t u8PositionToClean);
void f_USARTCommProt_IsProcessData();
void f_USARTCommProt_IsDatPacketTightening(uint8_t* u8PacketReceived, uint8_t u8DataReceiver);


#endif /* INC_USART_COMMUNICATIONPROTOCOL_H_ */


