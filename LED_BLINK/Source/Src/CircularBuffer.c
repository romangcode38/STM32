/*
 * CircularBuffer.c
 *
 *  Created on: Jun 21, 2023
 *      Author: romag
 */

#include "main.h"
#include "CircularBuffer.h"



bool f_isFullFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer)
{
	if (CircularFIFOBuffer->u16_BufferSize == (BUFFER_SIZE - 1))
	{
		return true ;
	}
	else
	{
		return false;
	}
}

bool f_isEmptyFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer)
{
	if (CircularFIFOBuffer->u16_BufferSize == 0)

	{
		return true ;
	}
	else
	{
		return false;
	}
}


bool f_addElemFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer, uint8_t data)
{
	if (f_isFullFIFOBuffer(CircularFIFOBuffer) != true)
	{
		CircularFIFOBuffer->Buffer[CircularFIFOBuffer->u16Head] = data;

		if (CircularFIFOBuffer->u16Head < (BUFFER_SIZE - 1) )
		{
			CircularFIFOBuffer->u16Head++;

		}
		else
		{
			CircularFIFOBuffer->u16Head = 0;
		}
		CircularFIFOBuffer->u16_BufferSize++;
		return true;
	}
	else
	{
		return false;
	}
}

bool f_getElemFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer, uint8_t* theElement)
{
	if (f_isEmptyFIFOBuffer(CircularFIFOBuffer) != true)
	{
		*theElement = CircularFIFOBuffer->Buffer[CircularFIFOBuffer->u16Tail];
		if (CircularFIFOBuffer->u16Tail < (BUFFER_SIZE-1))
		{
			CircularFIFOBuffer->u16Tail++;
		}
		else
		{
			CircularFIFOBuffer->u16Tail = 0;
		}
		CircularFIFOBuffer->u16_BufferSize--;
	}
	else
	{
		return false;
	}
	return true;
}

