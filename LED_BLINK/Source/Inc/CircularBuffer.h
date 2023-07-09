/*
 * CircularBuffer.h
 *
 *  Created on: Jun 21, 2023
 *      Author: romag
 */

#ifndef CIRCULARBUFFER_INC_CIRCULARBUFFER_H_
#define CIRCULARBUFFER_INC_CIRCULARBUFFER_H_

#include "stdbool.h"

#define BUFFER_SIZE 50u

typedef struct{
	uint16_t u16_BufferSize;
	uint16_t u16Tail;
	uint16_t u16Head;
	uint8_t Buffer[BUFFER_SIZE];
}CircularFIFOBuffer;


bool f_getElemFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer, uint8_t* theElement);
bool f_addElemFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer, uint8_t data);
bool f_isEmptyFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer);
bool f_isFullFIFOBuffer(CircularFIFOBuffer* CircularFIFOBuffer);
uint16_t f_getNumberOfElementsFIFO(CircularFIFOBuffer* CircularFIFOBuffer);






#endif /* CIRCULARBUFFER_INC_CIRCULARBUFFER_H_ */
