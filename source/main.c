//###########################################################################
//
// FILE:    Example_2802xEPwm3UpAQ.c
//
// TITLE:   Action Qualifier Module Upcount mode.
//
// ASSUMPTIONS:
//
//     This program requires the f2802x header files.
//
//     Monitor the ePWM1 - ePWM3 pins on a oscilloscope as
//     described below.
//
//        EPWM1A is on GPIO0
//        EPWM1B is on GPIO1
//
//        EPWM2A is on GPIO2
//        EPWM2B is on GPIO3
//
//        EPWM3A is on GPIO4
//        EPWM3B is on GPIO5
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait		 !=0x55AA        X
//      I/O		     0x55AA	         0x0000
//      SCI		     0x55AA	         0x0001
//      Wait 	     0x55AA	         0x0002
//      Get_Mode	 0x55AA	         0x0003
//      SPI		     0x55AA	         0x0004
//      I2C		     0x55AA	         0x0005
//      OTP		     0x55AA	         0x0006
//      Wait		 0x55AA	         0x0007
//      Wait		 0x55AA	         0x0008
//      SARAM		 0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash		 0x55AA	         0x000B
//	    Wait		 0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
// DESCRIPTION:
//
//    This example configures ePWM1, ePWM2, ePWM3 to produce an
//    waveform with independent modulation on EPWMxA and
//    EPWMxB.
//
//    The compare values CMPA and CMPB are modified within the ePWM's ISR
//
//    The TB counter is in upmode for this example.
//
//    View the EPWM1A/B, EPWM2A/B and EPWM3A/B waveforms
//    via an oscilloscope
//
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//typedef struct
//{
//	volatile struct EPWM_REGS* EPwmRegHandle;
//	uint16_t EPwm_CMPA_Direction;
//	uint16_t EPwm_CMPB_Direction;
//	uint16_t EPwmTimerIntCount;
//	uint16_t EPwmMaxCMPA;
//	uint16_t EPwmMinCMPA;
//	uint16_t EPwmMaxCMPB;
//	uint16_t EPwmMinCMPB;
//} EPWM_INFO;

// Prototype statements for functions found within this file.
__interrupt void adc_isr ( void );
void analog_ChkZeroCross ( void );
void analog_ChkInputFreq ( void );
void analog_ChkInputCalc ( void );
void CBC_Config_L ( void );
void CBC_Config_N ( void );

//__interrupt void epwm1_isr ( void );
//__interrupt void epwm2_isr ( void );
//__interrupt void epwm3_isr ( void );
//void update_compare ( EPWM_INFO* );

// Global variables used in this example
//EPWM_INFO epwm1_info;
//EPWM_INFO epwm2_info;
//EPWM_INFO epwm3_info;

u16 temp_vin_UV=0;
u16 temp_vin_UV_Clr=0;
u16 temp1=0;
u16 temp2=0;
u16 Flag_Txd_cnt= 0;



void main ( void )
{
// WARNING: Always ensure you call memcpy before running any functions from RAM
// InitSysCtrl includes a call to a RAM based function and without a call to
// memcpy first, the processor will go "into the weeds"
	memcpy ( &RamfuncsRunStart, &RamfuncsLoadStart, ( size_t ) &RamfuncsLoadSize );
	InitFlash();    // Call the flash wrapper init function

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the f2802x_SysCtrl.c file.
	InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the f2802x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
	InitGpio();  // Skipped for this example

// For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
// These functions are in the f2802x_EPwm.c file
	InitEPwmGpio();

	InitCpuTimers();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the f2802x_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in f2802x_DefaultIsr.c.
// This function is found in f2802x_PieVect.c.
	InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
//	PieVectTable.EPWM1_INT = &epwm1_isr;
//	PieVectTable.EPWM2_INT = &epwm2_isr;
	PieVectTable.ADCINT1 = &adc_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers


// Step 4. Initialize all the Device Peripherals:
//  init the ADC
	InitAdc();
	AdcOffsetSelfCal();
	ConfigureADC();
	InitComp();

//initialize the SCI
	InitSci();

// initialize the ePWM
	InitEPwm();
	PFC_ON();
	RELAY_OFF();
	IO_2_SEC_PFC_OFF();
	GH_SR_ClrVal();
	GL_SR_ClrVal();

	PFC_PROTECT1_EN();
	PFC_PROTECT2_EN();
	PFC_PROTECT3_EN();

//	PFC_PROTECT1_DIS();
//	PFC_PROTECT2_DIS();
//	PFC_PROTECT3_DIS();

	TEST_CLR();
	LED_ON();
	uPFCFlags.b.AC_UV =1;

	Vbus_Control_Init();

	CTRL2P2Z_COEFF_current_LOOP.inter_A1= ( ( signed short ) ( ( double ) 24000*0.8 ) ); //30000//1600;
	CTRL2P2Z_COEFF_current_LOOP.inter_A2= ( ( signed short ) ( ( double )-17600*0.8 ) ); //-22000;//-23000//-25000//-28000;
	CTRL2P2Z_COEFF_current_LOOP.inter_A3= ( ( signed short ) ( ( double ) 5*0.8 ) );


// Step 5. User specific code, enable interrupts:

// Enable ADCINT1 in PIE
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// Enable INT 1.1 in the PIE
	IER |= M_INT1; 						// Enable CPU Interrupt 1

// Enable CPU INT3 which is connected to EPWM1-3 INT:
//	IER |= M_INT3;
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
//	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	StartCpuTimer0();

// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM


// Step 6. IDLE loop. Just sit and loop forever (optional):
	for ( ;; )
	{
//		LED_TOGGLE();
//		PFC_PROTECT1_DIS();
//		PFC_PROTECT2_DIS();
//		PFC_PROTECT3_DIS();


		analog_ChkZeroCross();
		analog_ChkInputFreq();
		analog_ChkInputCalc();

		period_200us_repetitive();
		period_1ms_repetitive ();

		if ( uPFCFlags.b.t200us_Triger )
		{
			uPFCFlags.b.t200us_Triger = 0;
			Filter_date();
			Power_state_control();
			Check_Fast_Bus_Voltage_Conditions();
			Vbus_Generate_Err();

			Vbus_Control();

			Vbus_Feedforward_Scaling();

//			LED_TOGGLE();

#if 0
			temp++;
			if ( temp>50 )
			{
				AD_u16_U_AC_L_FB=200;
				AD_u16_U_AC_N_FB=300;
			}
			else
			{
				AD_u16_U_AC_L_FB=300;
				AD_u16_U_AC_N_FB=200;
			}
			if ( temp>100  )
			{
				temp=0;
			}
#endif
		}


		if ( uPFCFlags.b.t1ms_Triger )
		{
			uPFCFlags.b.t1ms_Triger = 0;

			temp1++;
			if ( temp1>10 )	//once 10ms
			{
				temp1=0;
				SCICommu_Control(); 			// SCI Communication(46K80)
			}

//		IO_2_SEC_PFC_OFF();
			


		}

//		uPFCFlags.b.AC_UV = 1;
		if ( uPFCFlags.b.AC_UV )
		{
//			PFC_PROTECT1_EN();
//			PFC_PROTECT2_EN();
//			PFC_PROTECT3_EN();

			LED_ON();
		}
		else
		{
			PFC_PROTECT1_DIS();
			PFC_PROTECT2_DIS();
			PFC_PROTECT3_DIS();

			LED_OFF();
		}




		if ( uPFCFlags.b.bus_ctl )
		{
			uPFCFlags.b.bus_ctl = 0;
//			Vbus_Control();

		}

	}
}

__interrupt void adc_isr ( void )
{
	//Low periorty interrupt
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

//	LED_ON();

	//add code here
	i16 temp_I_ref,temp_duty_I,I_error;
	static u16 uFlag_turn_on=1;
	static u16 Latch_counter=0;
	static u16 u16Negitive_Cnt=0;
	static u16 u16Positive_Cnt=0;
	static u16 Once_Secondary=0;
	u16 temp_out;
	u32 u32_I_error;
	i16 I_error_temp;
//	static long u32Max_duty_soft=0x1b00000;//432*16 //48%//0x1950000;//405*16;//45%

	AD_u16_I_AC 	= AdcResult.ADCRESULT0;
	AD_u16_U_AC_L_FB	= AdcResult.ADCRESULT1;
	AD_u16_U_AC_N_FB	= AdcResult.ADCRESULT2;
	AD_u16_U_HV_FB	= AdcResult.ADCRESULT3;
	AD_u16_U_3V_REF	= AdcResult.ADCRESULT4;


#if 1
	if ( AD_u16_U_AC_L_FB > AD_u16_U_AC_N_FB )		//L > N
	{
		u16Xvin = AD_u16_U_AC_L_FB - AD_u16_U_AC_N_FB;
		u16Negitive_Cnt++;
		u16Positive_Cnt=0;
		if ( u16Negitive_Cnt>2 )
		{
			uPFCFlags.b.Is_N_greater_than_L = FALSE;
//			GL_SR_ClrVal();
//			GH_SR_SetVal();
		}
	}
	else											//N > L
	{
		u16Xvin = AD_u16_U_AC_N_FB - AD_u16_U_AC_L_FB;
		u16Negitive_Cnt=0;
		u16Positive_Cnt++;
		if ( u16Positive_Cnt>2 )
		{
			uPFCFlags.b.Is_N_greater_than_L = TRUE ;
//			GL_SR_ClrVal();
//			GH_SR_SetVal();
		}
	}

	if ( uPFCFlags.b.Is_N_greater_than_L!=uFlag_turn_on )
	{
//		LED_TOGGLE();
		uFlag_turn_on=uPFCFlags.b.Is_N_greater_than_L;
		Latch_counter=0;
		if ( uPFCFlags.b.Is_N_greater_than_L )		//N > L
		{
//			LED_ON();
			CBC_Config_N();
			uPFCFlags.b.PFC_Neg_off=1;
			uPFCFlags.b.PFC_Pos_off=0;
			EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;		// Select SOC from PRD
//			EPWM1A_DB = EPWM_PFC_SW_FREQUENCY;
			PFC_EPWMxA_CMPA = ( DUTY_EPWMA_OFF );
			//TESTEnd1();

		}
		else										//L > N
		{
//			LED_OFF();
			CBC_Config_L();
			uPFCFlags.b.PFC_Pos_off=1;
			uPFCFlags.b.PFC_Neg_off=0;
			EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;		// Select SOC from PRD
//			EPWM1B_DB = EPWM_PFC_SW_FREQUENCY;
			PFC_EPWMxB_CMPB = DUTY_EPWMB_OFF;
			//	TESTBegin1();
		}

	}


	if ( AD_u16_I_AC > AD_u16_CALI_I_ZRO )
	{
		u16Xiin = AD_u16_I_AC - AD_u16_CALI_I_ZRO;
	}
	else
	{
		u16Xiin = AD_u16_CALI_I_ZRO - AD_u16_I_AC;
	}

	//u16Xiin=0;



	//PFC current loop
	//uIsenseAdj to be optimized
	//uIctl_Ref=65500;
	//u16Xvin=10;
	uIsenseAdj=0;


	/*
	temp_I_ref = uIsenseAdj + ( u16 ) (  ( (( u32 )uIctl_Ref)*u16Xvin ) >>16 );


	temp_duty_I = PI_Boost_internal ( temp_I_ref, u16Xiin, ( ( ( u32 ) MAX_PFC_DUTY ) <<16 ), &CTRL2P2Z_COEFF_current_LOOP, ( ( ( u32 ) MIN_PFC_DUTY ) <<16 ) );
	*/

#ifdef  Vol_loop_only
	temp_duty_I = ( uIctl_Ref>>5 );		//MAX Duty = 1015/1500
#else

	temp_I_ref = uIsenseAdj + ( u16 ) (  ( ( ( u32 ) uIctl_Ref ) *u16Xvin ) >>12 );


//	temp_I_ref = u16Xiin + 10;

	//	error =  Voutref- VoutT
	I_error = temp_I_ref - u16Xiin;

//	I_error = -190;
//		u16Xiin=200;


	if ( u16Xiin>67 )
	{
		I_error_temp = ( 476-u16Xiin );
		if ( I_error_temp<200 )
		{
			I_error_temp=200;
		}

		if ( I_error > 0 )
		{
			u32_I_error = ( ( ( u32 ) I_error )  );
			u32_I_error = ( ( I_error_temp*u32_I_error ) >>9 );
			I_error = ( u16 ) ( u32_I_error );
		}
		else
		{
			I_error= ( -I_error );
			u32_I_error = ( ( ( u32 ) I_error ) );
			u32_I_error = ( ( I_error_temp*u32_I_error ) >>9 );
			I_error = ( u16 ) ( u32_I_error );
			I_error= ( -I_error );
		}
	}

//	temp_duty_I = PI_Boost_internal ( I_error, ( ( ( u32 ) MAX_PFC_DUTY ) <<16 ), &CTRL2P2Z_COEFF_current_LOOP, ( ( ( u32 ) MIN_PFC_DUTY ) <<16 ) );
//	temp_duty_I = PI_Boost_internal ( int16 error, int32 Max_out,CTRL2P2Z_coeff* CTRL2p2z,int32 U32Min_out )

	temp_duty_I = PI_Boost_internal ( I_error, ( ( ( u32 ) MAX_PFC_DUTY ) <<16 ), &CTRL2P2Z_COEFF_current_LOOP, ( ( ( u32 ) MIN_PFC_DUTY ) <<16 ) );

#endif

//	temp_duty_I= 300;

//	if ( u16Xvin > ( AD_u16_U_HV_FB-37 ) )
//	{
//		temp_duty_I = MIN_PFC_DUTY;
//	}

//	if ( u16Xiin > 800 )	//CBC
//	{
//		//		PFC_Off();
//		uPFCFlags.b.CBC_OC = 1;
//		temp_duty_I = MIN_PFC_DUTY;
//	}

	if ( u16AvgVbus > PRI_VBUS_420V )	//CBC
	{
		uPFCFlags.b.CBC_OC = 1;
		CTRL2P2Z_COEFF_current_LOOP.Uout_z1 = 0;
		temp_duty_I = MIN_PFC_DUTY;
	}



//temp1++;

//if((temp1)>1)
//{
//	temp_duty_I =(u16)(MAX_PFC_DUTY*0.6) ;
//}
//else
//{
//	temp_duty_I =(u16)(MAX_PFC_DUTY*0.4) ;
//}

//if((temp1)>=3)
//{	temp1=0;}

//	temp_duty_I = ( EPWM_PFC_SW_FREQUENCY-MAX_PFC_DUTY );
//	temp_duty_I = EPWM_PFC_SW_FREQUENCY-( EPWM_PFC_SW_FREQUENCY>>3 );

	Latch_counter++;

	if ( Latch_counter<8 )
	{
//		LED_TOGGLE();
		if ( uPFCFlags.b.PFC_Pos_off )
		{

			temp_out = ( ( MAX_PFC_DUTY>>3 ) *Latch_counter );
			CTRL2P2Z_COEFF_current_LOOP.Uout_z1 = ( ( ( i32 ) temp_out ) <<16 );
			if ( u16AvgVbus > PRI_VBUS_420V )
			{
				PFC_EPWMxA_CMPA= DUTY_EPWMA_OFF;	//
				PFC_EPWMxB_CMPB = DUTY_EPWMB_OFF;
			}
			else
			{
				PFC_EPWMxA_CMPA= EPWM_PFC_SW_FREQUENCY - temp_out;	//
				PFC_EPWMxB_CMPB = DUTY_EPWMB_OFF;
			}
		}
		else if ( uPFCFlags.b.PFC_Neg_off )
		{
			temp_out = ( ( MAX_PFC_DUTY>>3 ) *Latch_counter );
			CTRL2P2Z_COEFF_current_LOOP.Uout_z1 = ( ( ( i32 ) temp_out ) <<16 );

			if ( u16AvgVbus > PRI_VBUS_420V )
			{
				PFC_EPWMxA_CMPA= DUTY_EPWMA_OFF;	//
				PFC_EPWMxB_CMPB = DUTY_EPWMB_OFF;
			}
			else
			{
				PFC_EPWMxB_CMPB =  temp_out;
				PFC_EPWMxA_CMPA = ( DUTY_EPWMA_OFF );
			}
		}
		GH_SR_ClrVal();
		GL_SR_ClrVal();
	}
	else
	{
		//Latch_counter=10;
		if ( uPFCFlags.b.PFC_Neg_off )
		{
//			LED_TOGGLE();
			PFC_EPWMxB_CMPB = temp_duty_I ;
			PFC_EPWMxA_CMPA = ( DUTY_EPWMA_OFF );

			if ( Latch_counter>50 ) //40
			{
//				PFC_EPWMxA_CMPA = temp_duty_I + EPWM_PFC_DRV_DEAD_BAND;
			}
		}
		else
		{
			PFC_EPWMxA_CMPA = EPWM_PFC_SW_FREQUENCY -  temp_duty_I + EPWM_PFC_DRV_DEAD_BAND;
			PFC_EPWMxB_CMPB = DUTY_EPWMB_OFF;

			if ( Latch_counter>50 )
			{
//				PFC_EPWMxB_CMPB = EPWM_PFC_SW_FREQUENCY - temp_duty_I;
			}
		}
	}

//	temp_duty=PI_Boost_internal ( temp_duty,AD_u16_l_boost1,u32Max_duty_soft,&CTRL2P2Z_COEFF_inter_LOOP,0x30000 );

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*******************************************//

	if ( Once_Secondary++>1 )
	{
		Once_Secondary=0;
		if ( !Flag_Txd )
		{
#if 1
			Txd_buf[Flag_Txd_cnt]=0x55;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xiin>>8 );
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xiin&0x00ff );
			Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xvin>>8 );
//		Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xvin&0x00ff );
//		Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_duty_I>>8 );
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_duty_I&0x00ff );
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_I_ref>>8 );
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_I_ref&0x00ff );
			Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( CTRL2P2Z_COEFF_current_LOOP.error_z1>>8 );
//		Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( CTRL2P2Z_COEFF_current_LOOP.error_z1&0x00ff );
//		Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( uVbus_Ref>>8 );
//		Flag_Txd_cnt++;
//		Txd_buf[Flag_Txd_cnt]= ( char ) ( uVbus_Ref&0x00ff );
//		Flag_Txd_cnt++;

#else
			Txd_buf[Flag_Txd_cnt]=0x55;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xvin>>8 );
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xvin&0x00ff );
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_I_ref>>8 );;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_I_ref&0x00ff );;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_duty_I>>8 );;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( temp_duty_I&0x00ff );;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( uVbus_Area>>8 );;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( uVbus_Area&0x00ff );;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16AvgVbus>>8 );;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16AvgVbus&0x00ff );;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xiin>>8 );;
			Flag_Txd_cnt++;
			Txd_buf[Flag_Txd_cnt]= ( char ) ( u16Xiin&0x00ff );;
			Flag_Txd_cnt++;

			Txd_buf[Flag_Txd_cnt]= ( char ) ( uPowerState&0x00ff );;
			Flag_Txd_cnt++;

#endif
			if ( Flag_Txd_cnt> ( test_cnt-20 ) )
			{
				Flag_Txd=1;
				Flag_Txd_cnt=0;
			}
		}

	}




	if ( u16Xvin<700 )	//50VRMS~300ADC	260~60V	540~120V 	700~180V
	{
		if ( temp_vin_UV>100 )
		{
			uPFCFlags.b.AC_UV = 1;
//					LED_ON();
			temp_vin_UV_Clr = 0;
		}
		else
		{
			temp_vin_UV++;
		}

	}
	else
	{
		temp_vin_UV = 0;
		if ( temp_vin_UV_Clr > 100 )
		{
			uPFCFlags.b.AC_UV = 0;
//					LED_OFF();
			temp_vin_UV_Clr = 0;
		}
		else
		{
			temp_vin_UV_Clr++;
		}
	}





//****************************************************************************************//

	u32IpVoltSumOfSquare += u16Xvin*u16Xvin;
	u8IpSampleCnt++;

	if ( u8IpSampleCnt >= 255 )
	{
		u8IpSampleCnt = 255;
	}

//	LED_TOGGLE();

#endif
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE


//	LED_OFF();
}

//==================================================================

void CBC_Config_L()
{
	EALLOW;
	Comp1Regs.DACVAL.bit.DACVAL = 365;//100;					// Set DAC output to midpoint  (10 bits)
	Comp1Regs.COMPCTL.bit.CMPINV = 1;						//0~immd	1~invt
	EDIS;
}

void CBC_Config_N()
{
	EALLOW;
	Comp1Regs.DACVAL.bit.DACVAL = 552;//900;					// Set DAC output to midpoint  (10 bits)
	Comp1Regs.COMPCTL.bit.CMPINV = 0;						//0~immd	1~invt
	EDIS;
}


//===========================================================================
// No more.
//===========================================================================
