/*
 * ButtonDrv.c
 *
 *  Created on: Jun 6, 2023
 *      Author: romag
 */

#include "LedDrv.h"
#include "main.h"

#define CLICK1		(1u)
#define CLICK2		(2u)
#define CLICK3		(3u)

static volatile unsigned int ru32_SysClick = 0u;

void ButtonDrv_Init(void)
{
	ButtonDrv_MainFunction();
}

void ButtonDrv_MainFunction(void)
{
	switch(ru32_SysClick)
		{
		case CLICK1:
		{
			LedDrv_MainFunction1();
			break;
		}
		case CLICK2:
		{

			LedDrv_MainFunction2();
			break;
		}
		case CLICK3:
		{
			LedDrv_MainFunction3();
			break;
		}
		default:
		{
			ru32_SysClick = 0;
		}
	}
}

void ButtonDrv_SysClickCallback(void)
{
	ru32_SysClick++;
}
