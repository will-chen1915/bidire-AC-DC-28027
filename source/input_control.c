/******************************** INCLUDES **********************************/

#include "input_control.h"		       // module header file
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File



/********************************* DEFINES ***********************************/

/*
 * As the real VDDA is near the supply us for VREFINT calibration.
 * It will be -2 < corr < 2, therefore we can hold the factor as Q2.14
 */


// Period of time between measurements/caculation.
#define K32_IpVolt_INTERVAL         hptsc_MsToTicks(15)
#define K32_TEMP_INTERVAL  				  hptsc_MsToTicks(1)
#define K32_AC_IIN_VOLT_INTERVAL 		hptsc_UsToTicks(250)
#define K32_AC_HALF_PERIOD_MIN    	hptsc_MsToTicks(6.7)
#define K32_AC_HALF_PERIOD_MAX    	hptsc_MsToTicks(12.5)
#define K32_MEASURABLE_PERIOD_MAX   hptsc_MsToTicks(13.5)
#define K32_FREQ_TEST_T             (K32_AC_HALF_PERIOD_MAX * 3)



#define K16_VOL_ERROR               IP_V(15)
#define K16_ZC_TH             			IP_V(55)
#define K16_ZC_MARGIN         			IP_V(14.6)

#define K16_ZC_ACWAVE_TH            IP_V(60)


#define K32_PFC_OK_TIME             hptsc_MsToTicks(50)
#define K32_PFC_NOK_TIME            hptsc_MsToTicks(50)

#define K32_AC_OV_TIME						  hptsc_MsToTicks(100)

//#define K32_AC_OV_TIME						  hptsc_MsToTicks(1)

#define K32_AC_OV_CLR_TIME				  hptsc_MsToTicks(30)
//#define K32_AC_OV_CLR_TIME				  hptsc_MsToTicks(1)

#define INPUT_VOL_MARGIN            IP_V(90)

#define K32_200US_INTERVAL            hptsc_UsToTicks(200)
#define K32_1MS_INTERVAL            hptsc_MsToTicks(1)

/******************************** TYPEDEFS ***********************************/


/********************************* IMPORTS************************************/

/********************************* EXPORTS************************************/

/********************************* GLOBALS ***********************************/
static bool bZeroCrossing = FALSE;
uint32_t u32AcHalfPeriodAvg;
uint32_t u32AcHalfPeriod;
FreqStateType    InputFreqState_e = INPUT_FREQUENCY_LOW;

uint16_t u16IpVoltRMS = 0;
uint16_t u16IpVoltRMSAvg = 0;
uint32_t u32IpVoltSumOfSquare = 0;
u16 u8IpSampleCnt=0;


/********************************** LOCALS ***********************************/
static uint32_t analog_calcRMS ( uint32_t u32SqrtArgSum, uint32_t u32SampleCnt );


//Average samples or RMS
//static T_movingAvg32 s_avgInstVolt;
static T_movingAvg32 s_avgAcHalfPeriod;
//static T_movingAvg32 s_avgRMSCurrent;
static T_movingAvg32 s_avgRMSVolt;
//static T_movingAvg32 s_avgIpPower;
//static T_movingAvg32 s_avgADCHeatSinkTemperature;
//static T_movingAvg32 s_avgAmbientTemperature;
//static T_movingAvg32 s_avgBulkVolt;

uint32_t test = 0;
/*
uint32_t	atimer_timer_us;
uint32_t	atimer_timer_ms;
uint32_t	atimer_us_ms;
*/
/*************************** SOURCE CODE INCLUDES ****************************/

/*note for ADC2Temperature_table:
note 1: NTC ADC should be shifted (adc_corr[ADC_NTC_TEMP_IDX]>>2), limit it to 10bits
note 2: In order to report a positive temperature, added +50 degree(offset) in below table
on secondary side, should remove this offset(-50) before reporting
*/
/*******************************************************************************
* uint32_t movingAvg32(uint32_t u32CurrSample, T_movingAvg32 *pTmovingAvg)
*
* Input  :  Sample data and T_movingAvg32 structure
*
* Output :  32 Moving Averageed data
*
* Description: only for 32 Moving Averageed
*
* Notes:
******************************************************************************/
static uint32_t movingAvg32 ( uint32_t u32CurrSample, T_movingAvg32* pTmovingAvg )
{
	if ( pTmovingAvg == NULL )
	{
		return 0;
	}
	pTmovingAvg->u64SampleSum -= pTmovingAvg->u32Buff[pTmovingAvg->bufPtr];
	pTmovingAvg->u64SampleSum += u32CurrSample;
	pTmovingAvg->u32Buff[pTmovingAvg->bufPtr] = u32CurrSample;

	//#define K8_MOVING_AVG_BUFF_SIZE 32	//Array size is 32
	pTmovingAvg->bufPtr = ( pTmovingAvg->bufPtr +1 ) %K8_MOVING_AVG_BUFF_SIZE;

	return pTmovingAvg->u64SampleSum>>5;
}
/*******************************************************************************
* void analog_calcRMS(uint32_t u32SqrtArgSum, uint32_t u32SampleCnt)
*
* Input: Squared data and number of samples
*
* Description: calculate root of square data, return Q15 data
*       .
*
* Notes:
*******************************************************************************/
static  uint32_t analog_calcRMS ( uint32_t u32SqrtArgSum, uint32_t u32SampleCnt )
{
	uint32_t u32Rootsq, x;
	uint32_t u32TempVal;
	uint32_t u32SqrtArg;

	if ( u32SampleCnt <= 0 )
	{
		return 0;
	}

	u32SqrtArg = ( uint32_t ) ( ( double ) u32SqrtArgSum/u32SampleCnt+0.5 );
	uAvgSqVin_z1 = (u32SqrtArg>>16);

	if ( u32SqrtArg == 0 )
	{
		return 0;    // undefined result
	}
	if ( u32SqrtArg == 1 )
	{
		return 1;    // identity
	}
	u32Rootsq = 0;                     							  // integer square root

	for ( x=0x8000; x>0; x=x>>1 )
	{
		// 16 bit shift
		u32Rootsq |= x;             									// possible bit in root
		u32TempVal = u32Rootsq*u32Rootsq; 						// fast unsigned multiply
		if ( u32TempVal == u32SqrtArg )
		{
			break;    // exact, found it
		}
		if ( u32TempVal > u32SqrtArg )
		{
			u32Rootsq ^= x;    // too large, reverse bit
		}
	}
	//Screen by kylegao 2015-11-17
	//return (u32Rootsq<<2); // approximate root, 13bits<<2
	return ( u32Rootsq<<3 ); // approximate root, 12bits<<3
}

/*******************************************************************************
* void analog_ChkZeroCross(void)
*
* Input  :  u16IpRectVoltInstQ15
*
* Output :  bZeroCrossing
*
* Description: Check if Ac input voltage is at zerocrossing
*  And measure the input ac half period time
*
* Notes: This subroutine shall be run in mainloop
******************************************************************************/
void analog_ChkZeroCross ( void )
{
	static HptscTicks_t ts_ticketSum;
	static HptscTicks_t ts_AcPeriodElapsedTicket = 0;    		// AC Period Elapsed from last time
	ts_ticketSum += hptsc_ElapsedTicket ( &ts_AcPeriodElapsedTicket );
	if ( bZeroCrossing == TRUE )
	{
		//#define K16_ZC_TH             			IP_V(55)
		//#define K16_ZC_MARGIN         			IP_V(14.6)
		// For Cisco 770w RSP2
		//#define IPV_RANGE   		(442.6)	// Input voltage measurable range, V
		//#define IP_V(x)     		((uint16_t)((double)x*RESOLUTION/IPV_RANGE)) // Input voltage scale in Q15
		// x*2.67/(10+2.67) = 3.3  x = 15.65955056
		// x*(1.65+1.65)/(499*2+1.65+1.65) = 15.65955056
		//                               x =
		// For Cisco 650w RSP1
		// x*20/(20+1) = 3.3 x = 3.465
		// x*(7.5+7.5)/(301*4+7.5+7.5) = 3.465
		//                            x = 281.589
		if ( u16Xvin > ( K16_ZC_TH + K16_ZC_MARGIN ) )
		{
			bZeroCrossing = FALSE;
		}

	}
	else
	{
		if ( u16Xvin < K16_ZC_TH )
		{
			bZeroCrossing   = TRUE;
			u32AcHalfPeriod = ts_ticketSum;
			ts_ticketSum  = 0;
			ts_AcPeriodElapsedTicket = 0;//Reset timer
		}
	}
	// Limit ts_ticketSum
	//#define K32_MEASURABLE_PERIOD_MAX   hptsc_MsToTicks(13.5)
	if ( ts_ticketSum > K32_MEASURABLE_PERIOD_MAX )
	{
		u32AcHalfPeriod = K32_MEASURABLE_PERIOD_MAX;
		ts_ticketSum = K32_MEASURABLE_PERIOD_MAX;
	}
}

/*******************************************************************************
* analog_ChkInputFreq
*
* Input: u16AcHalfPeriod
*
* Output: InputFreqState_e
*
* Description: Check if Ac input frequency is too high or too low
*
* Notes: This subroutine shall be run in mainloop
*******************************************************************************/
void analog_ChkInputFreq ( void )
{
	static HptscTicks_t ts_ticketSum;
	static HptscTicks_t ts_AcFreqElapsedTicket = 0;    	 		// AC frequency Elapsed from last time
	ts_ticketSum += hptsc_ElapsedTicket ( &ts_AcFreqElapsedTicket );

	switch ( InputFreqState_e )
	{
		case INPUT_FREQUENCY_LOW:
		{
			/*Freq is abnormal, assume AcHalfPeriodAvg is half period max*/
			//#define K32_AC_HALF_PERIOD_MAX    	hptsc_MsToTicks(12.5)
			u32AcHalfPeriodAvg = K32_AC_HALF_PERIOD_MAX;// maybe influence the sequence of shutdown if remove it

			if ( u32AcHalfPeriod < K32_AC_HALF_PERIOD_MAX )
			{
				// Freq is higher than mininum vale
				//#define K32_FREQ_TEST_T             (K32_AC_HALF_PERIOD_MAX * 3)
				if ( ts_ticketSum > K32_FREQ_TEST_T )
				{
					// Need to change state, check period to determine which state
					//#define K32_AC_HALF_PERIOD_MIN    	hptsc_MsToTicks(6.7)
					if ( u32AcHalfPeriod < K32_AC_HALF_PERIOD_MIN )
					{
						InputFreqState_e = INPUT_FREQUENCY_HIGH;
					}
					else
					{
						InputFreqState_e = INPUT_FREQUENCY_NORMAL;
					}
					ts_ticketSum = 0;
					ts_AcFreqElapsedTicket=0;//Reset timer
				}
			}
			else
			{
				ts_ticketSum = 0;
				ts_AcFreqElapsedTicket=0;//Reset timer
			}
			break;
		}

		case INPUT_FREQUENCY_NORMAL:
		{
			if ( u32AcHalfPeriod > K32_AC_HALF_PERIOD_MAX ||
			        u32AcHalfPeriod < K32_AC_HALF_PERIOD_MIN )
			{
				// Freq is not normal
				//#define K32_FREQ_TEST_T             (K32_AC_HALF_PERIOD_MAX * 3)
				if ( ts_ticketSum > K32_FREQ_TEST_T )
				{
					// Need to change state, check period to determine which state
					if ( u32AcHalfPeriod < K32_AC_HALF_PERIOD_MIN )
					{
						InputFreqState_e = INPUT_FREQUENCY_HIGH;
					}
					else
					{
						InputFreqState_e = INPUT_FREQUENCY_LOW;
					}
					ts_ticketSum = 0;
					ts_AcFreqElapsedTicket=0;//Reset timer
				}
			}
			else
			{

				ts_ticketSum = 0;
				ts_AcFreqElapsedTicket=0;//Reset timer
			}
			break;
		}

		case INPUT_FREQUENCY_HIGH:
		{
			/*Freq is abnormal, assume AcHalfPeriodAvg is half period max*/
			u32AcHalfPeriodAvg = K32_AC_HALF_PERIOD_MAX;//maybe influence the sequence of shutdown if remove it


			if ( u32AcHalfPeriod > K32_AC_HALF_PERIOD_MIN )
			{
				// Freq is not normal
				if ( ts_ticketSum > K32_FREQ_TEST_T )
				{
					// Need to change state, check period to determine which state
					if ( u32AcHalfPeriod < K32_AC_HALF_PERIOD_MAX )
					{
						InputFreqState_e = INPUT_FREQUENCY_NORMAL;
					}
					else
					{
						InputFreqState_e = INPUT_FREQUENCY_LOW;		// history 5
					}
					ts_ticketSum = 0;
					ts_AcFreqElapsedTicket=0;//Reset timer
				}
			}
			else
			{
				ts_ticketSum = 0;
				ts_AcFreqElapsedTicket=0;//Reset timer
			}
			break;
		}
		default:
		{
			InputFreqState_e = INPUT_FREQUENCY_NORMAL;
			break;
		}
	}
}

/*******************************************************************************
* analog_CalcIpParameters(void)
*
* Input: u16IpVoltSumOfSq, u16IpCurSumOfSq, u16IpPowerSum, u16ACSampleCnt
*
* Output: u16IpCurRms, u16IpVoltRms, u16IpPower, u16IpCurRmsAvg,
*           u16IpVoltRmsAvg, u16IpPowerAvg
*
* Description: Calculate input parameters V, I, Power rms values and Average
*               values. Also update IpScalingFactor for PFC control
*
* Notes:
*******************************************************************************/
static void analog_CalcIpParameters ( void )
{

	//uint16_t u16IpCurrentRMS=0;
	//uint16_t u16IpPower = 0;
	//static uint8_t u8TSETAssertcount = 0;
	//static uint16_t u16IpVoltRMSTempAvg=0;

	//Calculate average ac half period
	u32AcHalfPeriodAvg = movingAvg32 ( u32AcHalfPeriod, &s_avgAcHalfPeriod );
	//If input is normal,u8IpSampleCnt is approximately equal to 190 :190K/100
	u16IpVoltRMS = analog_calcRMS ( u32IpVoltSumOfSquare, u8IpSampleCnt ); //Q15
	u16IpVoltRMSAvg = movingAvg32 ( u16IpVoltRMS, &s_avgRMSVolt ); //Q15

	//u16IpCurrentRMS = analog_calcRMS ( u32IpCurrSumOfSquare, u8IpSampleCnt ); //Q15
	//u16IpCurrentRMSAvg = movingAvg32 ( u16IpCurrentRMS, &s_avgRMSCurrent );	//Q15

	//Screen by kylegao 2015-11-19
	//u16IpPower = (u32IpPowerSum/u8IpSampleCnt)>>11;	//Q15
	//u16IpPower = (u32IpPowerSum/u8IpSampleCnt)>>9;	//Q15

	//u16IpPowerAvg = movingAvg32(u16IpPower, &s_avgIpPower);


	//u16IpVoltRMSTempAvg = (u16IpVoltRMSTempAvg+u16IpVoltRMS)>>1;


	u32IpVoltSumOfSquare = 0;

	u8IpSampleCnt = 0;
	//u32IpCurrInstSampleCnt = 0;
	//u32IpPowerInstSampleCnt = 0;
}

/*******************************************************************************
* void analog_ChkInputCalc(void)
*
* Input: InputFreqState_e, bZeroCrossing
*
* Description: Check if it is the time to calculate Input ac parameters
*       If input frequency is okay, calculate the parameter right after ZC is
*       detected. If input frequency is abnormal, calculate the parameter in a
*       fix time interval.
*
* Notes: This subroutine shall be run in mainloop
*******************************************************************************/
void analog_ChkInputCalc ( void )
{
	static HptscTicks_t ts_ticketSum;
	static HptscTicks_t ts_AcRMSCalcElapsedTicket = 0;   		// RMS Calculation Elapsed from last time
	ts_ticketSum += hptsc_ElapsedTicket ( &ts_AcRMSCalcElapsedTicket );

	if ( InputFreqState_e == INPUT_FREQUENCY_NORMAL )
	{
		if ( bZeroCrossing == TRUE )
		{
			//#define hptsc_UsToTicks(us) hptsc_UsToTicksUserType(HptscTicks_t, us)
			//#define hptsc_UsToTicksUserType(type, us) \
			//        ROUND_TO(type, (double) CONFIG_HPTSC_HZ * (us) / 1000000.0)
			//#define CONFIG_HPTSC_HZ                 (SYSTEM_CLOCK_HZ / 8)
			//#define SYSTEM_CLOCK_HZ                 48000000
			//#define ROUND_TO(type, val) \
			//        ((type) ((val) < 0 ? (val) - 0.5 : (val) + 0.5))
			// CONFIG_HPTSC_HZ = 48000000/8 = 6000000
			// 6000000*0.5/1000000 = 3
			// ROUND_TO(type, 3) = 3+0.5 = 3.5
			//if(ts_ticketSum > (u32AcHalfPeriodAvg - hptsc_UsToTicks(0.5)))
			if ( ts_ticketSum > ( u32AcHalfPeriodAvg - hptsc_MsToTicks ( 0.5 ) ) )
			{
				analog_CalcIpParameters();
				ts_ticketSum = 0;
				ts_AcRMSCalcElapsedTicket=0;//Reset timer
				uPFCFlags.b.bus_ctl = 1;
			}
		}
	}
	/*
		else if(ts_ticketSum > K32_MEASURABLE_PERIOD_MAX ||
			ts_ticketSum > (u32AcHalfPeriodAvg + hptsc_MsToTicks(1)))
	{
	    analog_CalcIpParameters();
	    ts_ticketSum = 0;
			  ts_AcRMSCalcElapsedTicket=0;//Reset timer
	}
		*/ //Maybe influence the shoutdown sequence if swap with below code
	if ( ( ts_ticketSum > (u32)K32_AC_HALF_PERIOD_MAX )
	        || ( ts_ticketSum > ( u32AcHalfPeriodAvg + hptsc_MsToTicks ( 1 ) ) ) )
	{
		analog_CalcIpParameters();
		ts_ticketSum = 0;
		ts_AcRMSCalcElapsedTicket=0;//Reset timer
	}
}

void Vbus_Ref_Control_Process(void)
{		unsigned int _num;
	//		if (uPFCFlags.b.pri_bus_up) {uVbus_Ref_Target = PRI_VBUS_DEFAULT_REF_HIGH;}
	//		else {uVbus_Ref_Target = PRI_VBUS_DEFAULT_REF;}
		
		_num = uVbus_Ref - uVbus_Ref_Target;
		if ((signed int)_num == 0) {}
		else if ((signed int)_num > 0) {uVbus_Ref--; uPFCFlags.b.ramp = 0;}
		else if ((signed int)_num < -PRI_VBUS_ADJ_HYST) {uVbus_Ref += PRI_VBUS_ADJ_SLOPE; uPFCFlags.b.ramp = 1;}
		else {uVbus_Ref += 5;}
}

void period_200us_repetitive ( void )
{

	static HptscTicks_t ts_200us = 0;
	//200us interval => calc all corrected values
	if ( hptsc_IsElapsedRepetitive ( &ts_200us, K32_200US_INTERVAL ) )
	{
		uPFCFlags.b.t200us_Triger = 1;
	}

}

void period_1ms_repetitive ( void )
{

	static HptscTicks_t ts_1ms = 0;
	//1ms interval => calc all corrected values
	if ( hptsc_IsElapsedRepetitive ( &ts_1ms, K32_1MS_INTERVAL ) )
	{
		uPFCFlags.b.t1ms_Triger = 1;
	}

}



