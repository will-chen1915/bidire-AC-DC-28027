/******************************************************************************* 
* $HeadURL$                  The full URL of this file in the repository
*
********************************************************************************
* File:        mid_inputMonitor.h
*
* $Revision$                 Revision of last known commit
* $Date$                     Date of last known commit
* $Author$                   Author who made the last known commit
*******************************************************************************/
#ifndef __MID_INPUTMONITOR_H
#define __MID_INPUTMONITOR_H

/******************************** INCLUDES **********************************/
//#include ""
#include "stdint.h"
#include "stdbool.h"



/********************************* EXPORTS************************************/
extern void analog_ChkZeroCross(void);
extern void analog_ChkInputFreq(void);
extern void analog_ChkInputCalc(void);



/************************** FUNCTION DECLARATIONS ****************************/
static inline void avg_15_of_16(uint32_t u32CurrValue, uint32_t *u32PrevAvg)
{
	*u32PrevAvg = ((uint64_t)u32CurrValue + ((uint64_t)(*u32PrevAvg))*15)>>4;
}

static inline void avg_31_of_32(uint32_t u32CurrValue, uint32_t * u32PrevAvg)
{
	*u32PrevAvg = ((uint64_t)u32CurrValue + ((uint64_t)(*u32PrevAvg))*31)>>5;
}


/*
static uint64_t u64SampleSum;
static uint32_t avg_movingAvg(uint32_t u32CurrSample, uint32_t u32Buff[], uint32_t u32BuffSize, uint32_t *bufPtr)
{

	
	u64SampleSum -= u32Buff[*bufPtr];
	u64SampleSum += u32CurrSample;
	u32Buff[*bufPtr] = u32CurrSample;

	*bufPtr = (*bufPtr + 1)%u32BuffSize;
	
	return u64SampleSum/u32BuffSize;
	
}
*/
#endif	/* __filename */

