/*
 * control_loop.c
 *
 *  Created on: 2017��9��4��
 *      Author: zxid
 */

#include "DSP28x_Project.h"


//u16 u16LLC_frequence;
//u16 u16LLC_frequence_deadtime;

//u16  V_charge_target;
//u16  I_charge_target;


//u32  Max_power_target;

//u16 V_charge_ref;
//u16 I_charge_ref;


//u32 u32AvgVbus;
u16 u16AvgVbus;
i16 iVbus_Err;
u16 uVbus_Area;
u16 uVbus_Ref;
u16 uVbus_Gain_Adj_AC;
u16 uAvgSqVin_z1;
u16 uAvgVbusCnt = 0;

CTRL2P2Z_coeff  CTRL2P2Z_COEFF_VOLTAGE_LOOP;
CTRL2P2Z_coeff  CTRL2P2Z_COEFF_current_LOOP;
//CTRL2P2Z_coeff  CTRL2P2Z_COEFF_inter_LOOP;


PFC_FLAGS uPFCFlags;
//P_FLAGS uPFlags;

/********************************************************************************/
void PFC_ON ( void )
{
	EALLOW;
//	EPwm1Regs.TZCLR.bit.OST = TZ_ENABLE;//BOOST 1
	EDIS;
}
/********************************************************************************/
void PFC_OFF ( void )
{
	EALLOW;
//	EPwm1Regs.TZFRC.bit.OST = TZ_ENABLE;//BOOST1
	EDIS;
}

void Vbus_Control_Init ( void )
{
//	uPhaseFiltCnt = PFC_BUS_PHASE_SHED_WAIT;
	uVbus_Ref = 0;
	uVbus_Area = 0;
//	uVBus_Error_z1 = 0;
	iVbus_Err = 0;
//	uPfc_bus_area_high_lim = PFC_BUS_AREA_HIGH_LIM;
	CTRL2P2Z_COEFF_VOLTAGE_LOOP.inter_A1=3600;//1600;//16000
	CTRL2P2Z_COEFF_VOLTAGE_LOOP.inter_A2=-3400;//-1400;//-14000
	CTRL2P2Z_COEFF_VOLTAGE_LOOP.inter_A3=0;//2;//10
}


//short PI_Boost_internal ( int Voutref, int VoutT,int32 Max_out,CTRL2P2Z_coeff* CTRL2p2z,int32 U32Min_out )
short PI_Boost_internal ( int16 error, int32 Max_out,CTRL2P2Z_coeff* CTRL2p2z,int32 U32Min_out )
{
	/* Compute PI for Boost Mode */
	/* Every time the PI order sets extreme values then CTMax or CTMin are managed */
	unsigned short  pid_out;
	int32 temp1,temp2,temp3;
//	int16 error;

//	error =  Voutref- VoutT ;
	if ( ( error<3270 ) || ( error> ( -3270 ) ) )
	{
		error = error*10;
	}

	temp1 = CTRL2p2z->inter_A1 * ( int32 ) error ;
	temp2= ( CTRL2p2z->inter_A2 * ( int32 ) CTRL2p2z->error_z1 );
	temp2= ( temp1+temp2 ) <<1; //it is fraid

	temp3= ( CTRL2p2z->inter_A3 * ( int32 ) CTRL2p2z->error_z2 ) <<1;
	temp2=temp2+temp3;
	temp2=temp2+CTRL2p2z->Uout_z1;

	if ( temp2>Max_out )
	{
		temp2=Max_out;
	}
	else if ( temp2<U32Min_out )
	{
		temp2=U32Min_out;
	}
	CTRL2p2z->Uout_z1=temp2;
	CTRL2p2z->error_z2= ( int16 ) CTRL2p2z->error_z1;
	CTRL2p2z->error_z1= ( int16 ) error;

	pid_out= ( int16 ) ( CTRL2p2z->Uout_z1>>16 );

	return  pid_out;
}

short PI_VBus ( i16 error, int32 Max_out,CTRL2P2Z_coeff* CTRL2p2z,int32 U32Min_out )
{
	/* Compute PI for Boost Mode */
	/* Every time the PI order sets extreme values then CTMax or CTMin are managed */
	unsigned short  pid_out;
	int32 temp1,temp2,temp3;

//	error =  Voutref- VoutT ;

	temp1 = CTRL2p2z->inter_A1 * ( int32 ) error ;
	temp2= ( CTRL2p2z->inter_A2 * ( int32 ) CTRL2p2z->error_z1 );
	temp2= ( temp1+temp2 ) <<1; //it is fraid

	temp3= ( CTRL2p2z->inter_A3 * ( int32 ) CTRL2p2z->error_z2 ) <<1;
	temp2=temp2+temp3;
	temp2=temp2+CTRL2p2z->Uout_z1;

	if ( temp2>Max_out )
	{
		temp2=Max_out;
	}
	else if ( temp2<U32Min_out )
	{
		temp2=U32Min_out;
	}
	CTRL2p2z->Uout_z1=temp2;
	CTRL2p2z->error_z2= ( int16 ) CTRL2p2z->error_z1;
	CTRL2p2z->error_z1= ( int16 ) error;

	pid_out= ( int16 ) ( CTRL2p2z->Uout_z1>>16 );

	return  pid_out;
}

void Vbus_Feedforward_Scaling ( void )
{
	unsigned long ref;
	if (  uAvgSqVin_z1 < PFC_BUS_VSQUARE_SAT )
	{
		uVbus_Gain_Adj_AC = PFC_BUS_VSQUARE_SAT;
	}
	else
	{
		uVbus_Gain_Adj_AC =  uAvgSqVin_z1 ;
	}
	//ref = ( unsigned long ) ( uVbus_Area ) * 4096;

	//uIctl_Ref = ref/uVbus_Gain_Adj_AC;

	uIctl_Ref = uVbus_Area;

	uPFCFlags.b.bus_ctl = 0;

}

void Check_Fast_Bus_Voltage_Conditions ( void )
{
	if (  u16AvgVbus  < PRI_VBUS_OV_WARN )
	{
		uAvgVbusCnt++;
		if ( uAvgVbusCnt>2 )
		{
			uPFCFlags.b.VbusOVFault = 0;
			uAvgVbusCnt = 0;
		}
	}
	else if (  u16AvgVbus  > PRI_VBUS_OV_FAULT )
	{
		uPFCFlags.b.VbusOVFault = 1; //mVbus_Stall();
		uAvgVbusCnt = 0;

		uIctl_Ref = 0;
//		uIctl_Area = 0;//Current loop I(Integral) value
		//	uVbus_Area = 0;
	}

}

void Vbus_Generate_Err ( void )
{
//	uVbus_Err = uVbus_Ref - u16AvgVbus;
	//iVbus_Err = PRI_VBUS_60V - u16AvgVbus;
}

void Vbus_Control ( void )
{
//	unsigned int temp_err;
	// temp_err=uVbus_Err>>4;
	//DAC_write(temp_err);
	short temp_duty_V;
	static short cnt_Bus_soft_start=0;
	//TODO

	if ( uPFCFlags.b.AC_UV == 1 )
	{
		uVbus_Ref=u16AvgVbus;
	}
	else
	{
//		if ( cnt_Bus_soft_start++>10 )
		if ( cnt_Bus_soft_start++>150 )
		{
			cnt_Bus_soft_start=0;
			if ( uVbus_Ref<PRI_VBUS_350V )
			{
				uVbus_Ref=uVbus_Ref+5;
			}
			else if ( uVbus_Ref<PRI_VBUS_380V )
			{
				uVbus_Ref++;

			}
			else
			{
				uVbus_Ref = PRI_VBUS_380V;

			}
		}
	}


	iVbus_Err = uVbus_Ref - u16AvgVbus;

	if ( iVbus_Err>PRI_VBUS_30V )
	{
		iVbus_Err=iVbus_Err*3;
	}
	else if ( iVbus_Err< ( 0-PRI_VBUS_30V ) )
	{
		iVbus_Err=iVbus_Err*3;
	}



//	temp_duty_V = PI_VBus ( ( int16 ) iVbus_Err, (u32)(65500<<16), &CTRL2P2Z_COEFF_VOLTAGE_LOOP, 0 );	//0x4E1FB1E0 = 20000*2^16
	temp_duty_V = PI_VBus ( iVbus_Err, ( 0x7FEE0000 ), &CTRL2P2Z_COEFF_VOLTAGE_LOOP, 0 );	//0x4E1FB1E0 = 20000*2^16
	if ( PRI_VBUS_100V <u16AvgVbus )
	{
//		LED_TOGGLE();
	}
	uVbus_Area = temp_duty_V;


	//	temp_duty_I=PI_Boost_internal ( I_charge_ref,AD_u16_I_LLC1,u32Max_duty_soft,&CTRL2P2Z_COEFF_current_LOOP,0x30000 );
	/*
		if (  ( uAvgSqVin_z1 ) < PFC_BUS_VSQUARE_SAT )
		{
			uVbus_Gain_Adj_AC = PFC_BUS_VSQUARE_SAT;
		}
		else
		{
			uVbus_Gain_Adj_AC = _high ( uAvgSqVin_z1 );
		}


		asm ( move.w      uVbus_Err,A );
		if ( !uPFCFlags.b.gain )
		{asm ( asrr.l      #1,A);}


		asm	{
					asrr.l      #PFC_BUS_PI_PRE_GAIN,A
					rnd			A
					move.w      A1,Y0
					cmp.w       #23,Y0
					ble         VbusCtl_01
					move.w      #23,Y0
					bra         VbusCtl_02
			VbusCtl_01:
					cmp.w       #-8,Y0
					bge         VbusCtl_02
					move.w      #-8,Y0
			VbusCtl_02:
					and.w       #31,Y0
					moveu.w     Y0,R0
					adda        #ucPFC_Vbus_z0,R0,R0
					move.w      P:(R0)+,B
					add.w       uVbus_Area,B
					moveu.w     uVBus_Error_z1,R0
					adda        #ucPFC_Vbus_z1,R0,R0
					move.w      P:(R0)+,A
					add       	A,B
					brclr       #$8000,B1, VbusCtl_03
					clr         B
					clr.w       Y0
					bra         VbusCtl_04
			VbusCtl_03:
					cmp.w       uPfc_bus_area_high_lim,B
					bls         VbusCtl_04
					move.w      uPfc_bus_area_high_lim,B
			VbusCtl_04:
					move.w      Y0,uVBus_Error_z1
					move.w      B1,uVbus_Area
				}
	*/
}

