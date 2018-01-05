/*
 * Timer.c
 *
 *  Created on: 2017Äê9ÔÂ4ÈÕ
 *      Author: zxid
 */


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
//#include "CAN_SAEJ1939_Application.h"

//u16  Avg_u16_V_lowbattery;
//u16  Avg_u16_V_Highbattery;
//u16  Avg_u16_V_Boostout;
//u16  Avg_u16_V_24v;
//u16  Avg_u16_V_tempurtaion;
//u16  Avg_u16_I_LLC1;
//u16  Avg_u16_l_boost;

//u16  AD_u16_V_lowbattery;
//u16  AD_u16_V_Highbattery;
//u16  AD_u16_V_Boostout;
//u16  AD_u16_V_24v;
//u16  AD_u16_I_LLC1;
//u16  AD_u16_I_LLC2;
//u16  AD_u16_V_tempurtaion;
//u16  AD_u16_l_boost1;
//u16  AD_u16_l_boost2;


//u16  Cnt_boost_chargeonce;

//u16  Cnt_low_batt_uv;
//u16  Cnt_low_batt_uv_clear;

//u16  Cnt_charge_oc;
//u16  Cnt_charge_oc_clear;

////////////////////////////////////
u16  Cnt_boost_power;

u16	AD_u16_I_AC;
u16	AD_u16_CALI_I_ZRO;
u16	AD_u16_U_HV_FB;
u16	AD_u16_U_AC_L_FB;
u16	AD_u16_U_AC_N_FB;
u16	AD_u16_U_3V_REF;

u16	AVG_TEMP_AD_u16_I_AC;
u16	AVG_TEMP_AD_u16_U_HV_FB;
u16	AVG_TEMP_AD_u16_U_AC_L_FB;
u16	AVG_TEMP_AD_u16_U_AC_N_FB;
u16	AVG_TEMP_AD_u16_U_3V_REF;

u16	AVG_AD_u16_I_AC;
//u16	AVG_AD_u16_U_HV_FB;
u16	AVG_AD_u16_U_AC_L_FB;
u16	AVG_AD_u16_U_AC_N_FB;
u16	AVG_AD_u16_U_3V_REF;

u16	uIctl_Ref;
u16	u16Xvin;
u16	u16Xiin;
u16	uIsenseAdj = 0;
u16 uVbus_Ref_Target = 0;

u16 Flag_Txd = 0;



//POWER_FLAGS POWERFlags;

Machine Charge_process;

volatile T_AllTimers 	t_Timers;

void Filter_date ( void )
{
	//all ADC data remiained in low 12 bit
	AVG_TEMP_AD_u16_I_AC = AVG_TEMP_AD_u16_I_AC - (AVG_TEMP_AD_u16_I_AC>>2) + (AD_u16_I_AC);	
	AVG_TEMP_AD_u16_U_HV_FB = AVG_TEMP_AD_u16_U_HV_FB - (AVG_TEMP_AD_u16_U_HV_FB>>1) + (AD_u16_U_HV_FB);	
	AVG_TEMP_AD_u16_U_3V_REF = AVG_TEMP_AD_u16_U_3V_REF - (AVG_TEMP_AD_u16_U_3V_REF>>2) + (AD_u16_U_3V_REF);	

	AVG_AD_u16_I_AC = (AVG_TEMP_AD_u16_I_AC>>2);
	u16AvgVbus = (AVG_TEMP_AD_u16_U_HV_FB>>1);
	AVG_AD_u16_U_3V_REF = (AVG_TEMP_AD_u16_U_3V_REF>>2);

}

/************************************************************************************
***
*
*********************************************************************************/
/*
void Fault_check ( void )
{
	if ( Avg_u16_V_lowbattery>OV_LOW_BATTERY )
	{
		POWERFlags.b.Low_battery_ov=True;
		//	LED_RED_TOGGLE;
	}
	else if ( Avg_u16_V_lowbattery<OV_LOW_BATTERY_clear )
	{
		POWERFlags.b.Low_battery_ov=Fause;
	}

	if ( Avg_u16_V_lowbattery<UV_LOW_BATTERY )
	{
		POWERFlags.b.Low_battery_uv=True;
	}
	else if ( Avg_u16_V_lowbattery>UV_LOW_BATTERY_clear )
	{
		POWERFlags.b.Low_battery_uv=Fause;
	}

	if ( Avg_u16_V_Boostout>1000 )
	{
		POWERFlags.b.VBOOST_OV=True;
	}
	else if ( Avg_u16_V_Boostout<1000 )
	{
		POWERFlags.b.VBOOST_OV=Fause;
	}

	if ( Avg_u16_V_Highbattery>OV_HIGH_BATTERY )
	{
		POWERFlags.b.High_battery_ov=True;
	}
	else if ( Avg_u16_V_Highbattery<OV_HIGH_BATTERY_clear )
	{
		POWERFlags.b.High_battery_ov=Fause;
	}

	if ( Avg_u16_V_Highbattery<UV_HIGH_BATTERY )
	{
		POWERFlags.b.High_battery_uv=True;//True;
	}
	else if ( Avg_u16_V_Highbattery>UV_HIGH_BATTERY_clear )
	{
		POWERFlags.b.High_battery_uv=Fause;
	}

	if ( Avg_u16_V_24v<UV_24V_LOST )
	{
		POWERFlags.b.U24V_UV=True;
	}
	else if ( Avg_u16_V_24v>UV_24V_LOST_RECOVER )
	{
		POWERFlags.b.U24V_UV=Fause;
	}

	if ( Avg_u16_I_LLC1>Chare_oc_value )
	{
		Cnt_charge_oc++;
		Cnt_charge_oc_clear--;
		if ( Cnt_charge_oc>100 )
		{
			Cnt_charge_oc=100;
			POWERFlags.b.Charger_oc=True;
		}
	}
	else if ( Avg_u16_I_LLC1<Chare_oc_value_clear )
	{
		Cnt_charge_oc_clear++;
		Cnt_charge_oc--;

		if ( Cnt_charge_oc_clear>100 )
		{
			Cnt_charge_oc_clear=100;
			POWERFlags.b.Charger_oc=Fause;
		}
	}
}

*/
/******************************************************************************
 * Overview:       Function loads the timer value with the selected byThreadLevel
 *****************************************************************************/

void LoadTimer_GS ( T_Timer* pT_Timer, WORD wTimerVar )
{
	pT_Timer->wTimerValue = wTimerVar;
	pT_Timer->tTimerFlags.bits.TimerExpired =Fause;
}
/*****************************************************************/
/*
void Timer_Handler_GS ( void )
{
	int i,Temp;
	T_Timer* ptTimer_x ;
	Temp=sizeof ( T_AllTimers_1ms );
	ptTimer_x= ( T_Timer* ) &t_Timers.t_Timers_1ms;

	for ( i=0; i<Temp; i++ )
	{
		if ( ( ptTimer_x->wTimerValue > 0 ) && ( ptTimer_x->wTimerValue != 0xFFFF ) )
		{
			( ptTimer_x->wTimerValue )--;

		}

		if ( ptTimer_x->wTimerValue==0 )
		{
			ptTimer_x->tTimerFlags.bits.TimerExpired=True;
		}
		ptTimer_x++;
	}

	if ( ( ++t_Timers.by10msecCounter ) >= END_VALUE_10MSEC )
	{
		t_Timers.by10msecCounter=0;
		Temp=sizeof ( T_AllTimers_10ms );
		ptTimer_x= ( T_Timer* ) &t_Timers.t_Timers_10ms;
		for ( i=0; i<Temp; i++ )
		{
			if ( ( ptTimer_x->wTimerValue > 0 ) && ( ptTimer_x->wTimerValue != 0xFFFF ) )
			{
				( ptTimer_x->wTimerValue )--;
			}

			if ( ptTimer_x->wTimerValue==0 )
			{
				ptTimer_x->tTimerFlags.bits.TimerExpired=True;
			}
		}
	}

//	LED_RED_TOGGLE;
}


void Thread_Handler_GS ( void )
{

	if ( t_Timers.t_Timers_1ms.t_Fault_check_Task.tTimerFlags.bits.TimerExpired )
	{
		t_Timers.t_Timers_1ms.t_Fault_check_Task.tTimerFlags.bits.TimerExpired=Fause;

		Fault_check();

		LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_Fault_check_Task ),
		               Fault_check_time_1MS_5 );
	}

	if ( t_Timers.t_Timers_1ms.t_High_Level_Task_1.tTimerFlags.bits.TimerExpired )
	{
		t_Timers.t_Timers_1ms.t_High_Level_Task_1.tTimerFlags.bits.TimerExpired=Fause;

		LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_High_Level_Task_1 ),
		               PSU_process_time_1MS_1 );

//		PSU_process();
	}

	if ( t_Timers.t_Timers_1ms.t_filter_Task.tTimerFlags.bits.TimerExpired )
	{
		t_Timers.t_Timers_1ms.t_filter_Task.tTimerFlags.bits.TimerExpired=Fause;

		Filter_date();
		LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_filter_Task ),
		               PSU_process_time_1MS_1 );
	}
}



void PSU_process ( void )
{

//LED_RED_TOGGLE;


#ifdef Test_duty

	Charge_process=Charge__low_battery;
#endif
	switch ( Charge_process )
	{
		case Battery_STANDBY:
			Charge_process=Check_batery;
			LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_High_Level_Task_1 ),
			               PSU_process_time_1MS_100 );
			POWERFlags.b.Charge_enable=0;
			break;

		case Check_batery:
			if ( ( !POWERFlags.b.High_battery_ov ) && ( !POWERFlags.b.High_battery_uv ) )
			{
//				uPFlags.b.Charge_ONCE=True;
			}
			if ( ( !POWERFlags.b.High_battery_ov ) && ( !POWERFlags.b.High_battery_uv ) && ( !POWERFlags.b.Low_battery_ov ) && ( !POWERFlags.b.U24V_UV ) )
			{
				Charge_process=Charge__low_battery;

				uPowerState=STATE_RESTART_INIT;
//				uPFlags.b.LLC_power =1;
//				uPFlags.b.SR_ON=Fause;
//				uPFlags.b.Boost_power=1;
				u16LLC_frequence=EPWM_LLC_SW_HI_FREQUENCY;
				u16LLC_frequence_deadtime=EPWM_LLC_DRV_DEAD_BAND_normal;
			}

//			if ( ( POWERFlags.b.High_battery_uv ) && ( !POWERFlags.b.U24V_UV ) && ( uPFlags.b.Charge_ONCE ) )
			{
				PFC_Off();
				Charge_process=Boost_batter;
				Cnt_boost_power=0;

				u16LLC_frequence=EPWM_LLC_SW_FREQUENCY_boost;
				u16LLC_frequence_deadtime=EPWM_LLC_DRV_DEAD_BAND;
			}
			break;

		case Boost_batter:

			//	LED_RED_TOGGLE;
			PFC_Off();
			Cnt_boost_power++;

			if ( Cnt_boost_power>12000 ) //12000
			{
				Charge_process=Stop_charge;
				PFC_Off();
			}

			if ( POWERFlags.b.Low_battery_uv )
			{
				Charge_process=Stop_charge;
				PFC_Off();
			}
			LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_High_Level_Task_1 ),
			               PSU_process_time_1MS_10 );

//			uPFlags.b.Charge_ONCE=Fause;



			break;


		case Charge__low_battery:
//			uPFlags.b.Charge_ONCE=True;

			Power_state_control();

			if ( ( POWERFlags.b.High_battery_ov ) || ( POWERFlags.b.High_battery_uv ) || ( POWERFlags.b.Low_battery_ov ) || ( POWERFlags.b.U24V_UV ) )
			{

				Charge_process=Stop_charge;

//				uPFlags.b.SR_ON=Fause;
				PFC_Off();
			}

//			if ( ( POWERFlags.b.High_battery_uv ) && ( !POWERFlags.b.U24V_UV ) && ( uPFlags.b.Charge_ONCE ) )
			{
				PFC_Off();
				Charge_process=Boost_batter;
				//LED_RED_TOGGLE;
				Cnt_boost_power=0;

				u16LLC_frequence=EPWM_LLC_SW_FREQUENCY_boost;
				u16LLC_frequence_deadtime=EPWM_LLC_DRV_DEAD_BAND;
			}


			if ( Avg_u16_l_boost>2000 )
			{
//				uPFlags.b.SR_ON=True;
			}

			break;

		case Stop_charge:
			PFC_Off();

			POWERFlags.b.Charge_enable=0;

			LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_High_Level_Task_1 ),
			               PSU_process_time_1MS_10 );

			Charge_process=Battery_STANDBY;
			break;
			
		default:
			Charge_process=Battery_STANDBY;
			break;

	}
}
*/

/************************************************************************************
***/


/*

void InitThread ( void )
{
	LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_Fault_check_Task ),
	               Fault_check_time_1MS_5 );

	LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_High_Level_Task_1 ),
	               PSU_process_time_1MS_1 );

	LoadTimer_GS ( ( T_Timer* ) & ( t_Timers.t_Timers_1ms.t_filter_Task ),
	               PSU_process_time_1MS_1 );
}

*/
