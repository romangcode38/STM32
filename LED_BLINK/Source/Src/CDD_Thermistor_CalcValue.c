/*
 * CDD_Thermistor_CalcValue.c
 *
 *  Created on: Jul 14, 2023
 *      Author: romag
 */
#include "CDD_Thermistor_CalcValue.h"

#define VREFANALOG_VOLTAGE		(3300u)
#define RESISTENCE_VALUE		(10000u) //Resistence 10k
#define RESOLUTION_SCALE		(1000000u)
#define OFFSET_VALUE			(10000u)


#define ROWS		(218u)
#define COLUMNS     (2u)

uint32_t u32ResistanceOfSensor;
uint16_t u16VoltageOfSensor;
uint16_t u16IndexForARRAY;
uint16_t u16TemperatureOnTheSensor = 0u;

uint16_t u16TabelsOfGrades[ROWS][COLUMNS] =
{
		{	0		,	25067	},	//	-10
		{	500		,	24583	},	//	-9,5
		{	1000	,	24110	},	//	-9
		{	1500	,	23648	},	//	-8,5
		{	2000	,	23197	},	//	-8
		{	2500	,	22755	},	//	-7,5
		{	3000	,	22324	},	//	-7
		{	3500	,	21903	},	//	-6,5
		{	4000	,	21491	},	//	-6
		{	4500	,	21088	},	//	-5,5
		{	5000	,	20695	},	//	-5
		{	5500	,	20310	},	//	-4,5
		{	6000	,	19933	},	//	-4
		{	6500	,	19565	},	//	-3,5
		{	7000	,	19206	},	//	-3
		{	7500	,	18854	},	//	-2,5
		{	8000	,	18509	},	//	-2
		{	8500	,	18173	},	//	-1,5
		{	9000	,	17843	},	//	-1
		{	9500	,	17521	},	//	-0,5
		{	10000	 ,	17206	},	//	0
		{	10500	,	16897	},	//	0,5
		{	11000	,	16595	},	//	1
		{	11500	,	16300	},	//	1,5
		{	12000	,	16011	},	//	2
		{	12500	,	15728	},	//	2,5
		{	13000	,	15451	},	//	3
		{	13500	,	15180	},	//	3,5
		{	14000	,	14914	},	//	4
		{	14500	,	14654	},	//	4,5
		{	15000	,	14400	},	//	5
		{	15500	,	14151	},	//	5,5
		{	16000	,	13907	},	//	6
		{	16500	,	13668	},	//	6,5
		{	17000	,	13434	},	//	7
		{	17500	,	13205	},	//	7,5
		{	18000	,	12981	},	//	8
		{	18500	,	12761	},	//	8,5
		{	19000	,	12546	},	//	9
		{	19500	,	12335	},	//	9,5
		{	20000	,	12128	},	//	10
		{	20500	,	11925	},	//	10,5
		{	21000	,	11727	},	//	11
		{	21500	,	11532	},	//	11,5
		{	22000	,	11342	},	//	12
		{	22500	,	11155	},	//	12,5
		{	23000	,	10972	},	//	13
		{	23500	,	10793	},	//	13,5
		{	24000	,	10617	},	//	14
		{	24500	,	10444	},	//	14,5
		{	25000	,	10275	},	//	15
		{	25500	,	10110	},	//	15,5
		{	26000	,	9947	},	//	16
		{	26500	,	9788	},	//	16,5
		{	27000	,	9632	},	//	17
		{	27500	,	9478	},	//	17,5
		{	28000	,	9328	},	//	18
		{	28500	,	9181	},	//	18,5
		{	29000	,	9036	},	//	19
		{	29500	,	8894	},	//	19,5
		{	30000	,	8755	},	//	20
		{	30500	,	8619	},	//	20,5
		{	31000	,	8485	},	//	21
		{	31500	,	8353	},	//	21,5
		{	32000	,	8224	},	//	22
		{	32500	,	8098	},	//	22,5
		{	33000	,	7974	},	//	23
		{	33500	,	7852	},	//	23,5
		{	34000	,	7733	},	//	24
		{	34500	,	7615	},	//	24,5
		{	35000	,	7500	},	//	25
		{	35500	,	7387	},	//	25,5
		{	36000	,	7276	},	//	26
		{	36500	,	7167	},	//	26,5
		{	37000	,	7060	},	//	27
		{	37500	,	6955	},	//	27,5
		{	38000	,	6852	},	//	28
		{	38500	,	6751	},	//	28,5
		{	39000	,	6651	},	//	29
		{	39500	,	6554	},	//	29,5
		{	40000	,	6458	},	//	30
		{	40500	,	6364	},	//	30,5
		{	41000	,	6271	},	//	31
		{	41500	,	6180	},	//	31,5
		{	42000	,	6091	},	//	32
		{	42500	,	6003	},	//	32,5
		{	43000	,	5917	},	//	33
		{	43500	,	5832	},	//	33,5
		{	44000	,	5749	},	//
		{	44500	,	5668	},	//	34,5
		{	45000	,	5587	},	//	35
		{	45500	,	5508	},	//	35,5
		{	46000	,	5431	},	//	36
		{	46500	,	5355	},	//	36,5
		{	47000	,	5280	},	//	37
		{	47500	,	5206	},	//	37,5
		{	48000	,	5134	},	//	38
		{	48500	,	5063	},	//	38,5
		{	49000	,	4993	},	//	39
		{	49500	,	4924	},	//	39,5
		{	50000	,	4857	},	//	40
		{	50500	,	4790	},	//	40,5
		{	51000	,	4725	},	//	41
		{	51500	,	4661	},	//	41,5
		{	52000	,	4598	},	//	42
		{	52500	,	4535	},	//	42,5
		{	53000	,	4474	},	//	43
		{	53500	,	4414	},	//	43,5
		{	54000	,	4355	},	//	44
		{	54500	,	4297	},	//	44,5
		{	55000	,	4240	},	//	45
		{	55500	,	4184	},	//	45,5
		{	56000	,	4129	},	//	46
		{	56500	,	4074	},	//	46,5
		{	57000	,	4021	},	//	47
		{	57500	,	3968	},	//	47,5
		{	58000	,	3916	},	//	48
		{	58500	,	3865	},	//	48,5
		{	59000	,	3815	},	//	49
		{	59500	,	3766	},	//	49,5
		{	60000	,	3717	}	//	50

};

/************************************************************************/
/*!	\fn					Thermistor_InitFunction
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
void Thermistor_InitFunction(void)
{
	u32ResistanceOfSensor = 0;
	u16VoltageOfSensor = 0;
}

/************************************************************************/
/*!	\fn					Thermistor_CalculateResistance
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
void Thermistor_CalculateResistance(void)
{
	u16VoltageOfSensor = AdcCalculateVOLTAGE();
	u32ResistanceOfSensor = ((u16VoltageOfSensor * RESOLUTION_SCALE) / (((uint32_t)(VREFANALOG_VOLTAGE - u16VoltageOfSensor) * RESOLUTION_SCALE) / RESISTENCE_VALUE));
}

/************************************************************************/
/*!	\fn					Thermistor_CalculateGradeCelsius
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
void Thermistor_CalculateGradeCelsius(void)
{

	uint8_t u8NextIndexElement = 0u;
/*
//  Metoda de trecere prin LookUpTable si gasirea doar celui mai mare element fata ce cel venit.
 * 	uint8_t u8TempFound = 0u;
 *	uint8_t u8IndexArray = 0u;
    while(u8TempFound == 0)
    {
    	if(u32ResistanceOfSensor >= u16TabelsOfGrades[u8IndexArray][1])
    	{
//          u16TemperatureOnTheSensor = ((u16TabelsOfGrades[u8IndexArray][0]) - OFFSET_VALUE) / 1000;
      		u16TemperatureOnTheSensor = (u16TabelsOfGrades[u8IndexArray][0]);
    		u8TempFound = 1;
    	}
    	u8IndexArray++;
    }
 */
	for (u16IndexForARRAY = 0; u16IndexForARRAY < ROWS; u16IndexForARRAY++)
	{
		u8NextIndexElement = u16IndexForARRAY + 1;
		if((u32ResistanceOfSensor >= u16TabelsOfGrades[u8NextIndexElement][1]) && (u32ResistanceOfSensor <= u16TabelsOfGrades[u16IndexForARRAY][1]))
		{
			u16TemperatureOnTheSensor = (u16TabelsOfGrades[u16IndexForARRAY][0] + u16TabelsOfGrades[u8NextIndexElement][0]) / 2;
			u16IndexForARRAY = ROWS;
		}
	}
}

/************************************************************************/
/*!	\fn					Theemistor_GetTemperatureFunction
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
uint16_t Theemistor_GetTemperatureFunction(void)
{
	return u16TemperatureOnTheSensor;
}

/************************************************************************/
/*!	\fn					Thermistor_MainFunction
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
void Thermistor_MainFunction(void)
{
	Thermistor_CalculateResistance();
	Thermistor_CalculateGradeCelsius();
}
