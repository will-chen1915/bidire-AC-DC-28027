//###########################################################################
//
// FILE:   F2806x_EPwm.c
//
// TITLE:  F2806x EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2802x_Device.h"     // Headerfile Include File
#include "f2802x_examples.h"   // Examples Include File

void InitEPwm1 ( void );
void InitEPwm2 ( void );
void InitEPwm3 ( void );
void InitEPwm4 ( void );
void InitEPwm5 ( void );
void InitEPwm6 ( void );

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the EPwm(s) to a known state.
//
void InitEPwm ( void )
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;

	// Initialize EPwm1/2/3/4/5/6/7/8
	InitEPwm1();//PFC PWM 
//	InitEPwm2();//
//	InitEPwm3();//3A 3B LLC_SR1
//	InitEPwm4();//4A 4B LLC_SR2
//	InitEPwm5();//5A BOOST1
//	InitEPwm6();//6A BOOST2

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio ( void )
{
#if DSP28_EPWM1
	InitEPwm1Gpio();
#endif // endif DSP28_EPWM1
#if DSP28_EPWM2
//	InitEPwm2Gpio();
#endif // endif DSP28_EPWM2
//#if DSP28_EPWM3
//	InitEPwm3Gpio();
//#endif // endif DSP28_EPWM3
//#if DSP28_EPWM4
//	InitEPwm4Gpio();
//#endif // endif DSP28_EPWM4
//#if DSP28_EPWM5
//	InitEPwm5Gpio();
//#endif // endif DSP28_EPWM5
//#if DSP28_EPWM6
//	InitEPwm6Gpio();
//#endif // endif DSP28_EPWM6
//   #if DSP28_EPWM7
//       InitEPwm7Gpio();
//   #endif // endif DSP28_EPWM7
//   #if DSP28_EPWM8
//       InitEPwm8Gpio();
//   #endif // endif DSP28_EPWM8
}

#if DSP28_EPWM1
void InitEPwm1Gpio ( void )
{
	EALLOW;

	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

	/* Configure EPWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

	EDIS;
}
#endif // endif DSP28_EPWM1

#if DSP28_EPWM2
void InitEPwm2Gpio ( void )
{
	EALLOW;

	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

	/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

	EDIS;
}
#endif // endif DSP28_EPWM2

#if DSP28_EPWM3
void InitEPwm3Gpio ( void )
{
	EALLOW;

	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

	/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

	EDIS;
}
#endif // endif DSP28_EPWM3

#if DSP28_EPWM4
void InitEPwm4Gpio ( void )
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

	/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

	EDIS;
}
#endif // endif DSP28_EPWM4

#if DSP28_EPWM5
void InitEPwm5Gpio ( void )
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO8 (EPWM5A)
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO9 (EPWM5B)

	/* Configure EPWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM5 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
//    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

	EDIS;
}
#endif // endif DSP28_EPWM5

#if DSP28_EPWM6
void InitEPwm6Gpio ( void )
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
	//GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)

	/* Configure EPWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM6 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
  //  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B

	EDIS;
}
#endif // endif DSP28_EPWM6

#if DSP28_EPWM7
void InitEPwm7Gpio ( void )
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;	   // Disable pull-up on GPIO30 (EPWM7A)
	GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;    // Disable pull-up on GPIO40 (EPWM7A)
//  GpioCtrlRegs.GPBPUD.bit.GPIO58 = 1;	   // Disable pull-up on GPIO58 (EPWM7A)

	GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;    // Disable pull-up on GPIO41 (EPWM7B)
//  GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;	   // Disable pull-up on GPIO44 (EPWM7B)

	/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;   // Configure GPIO30 as EPWM7A
	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;   // Configure GPIO40 as EPWM7A
//  GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3;   // Configure GPIO58 as EPWM7A

	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;   // Configure GPIO41 as EPWM7B
//  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;   // Configure GPIO44 as EPWM7B

	EDIS;
}
#endif // endif DSP28_EPWM7

#if DSP28_EPWM8
void InitEPwm8Gpio ( void )
{
	EALLOW;
	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;	   // Disable pull-up on GPIO30 (EPWM8A)
	GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;    // Disable pull-up on GPIO42 (EPWM8A)
	GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1;    // Disable pull-up on GPIO43 (EPWM8B)

	/* Configure EPWM-7 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM7 functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;   // Configure GPIO30 as EPWM8A
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;   // Configure GPIO42 as EPWM8A
	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1;   // Configure GPIO43 as EPWM8B

	EDIS;
}
#endif // endif DSP28_EPWM8

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm Synch pins
//

void InitEPwmSyncGpio ( void )
{

//   EALLOW;

	/* Configure EPWMSYNCI  */

	/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;     // Enable pull-up on GPIO6 (EPWMSYNCI)
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up on GPIO32 (EPWMSYNCI)

	/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
	GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

	/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Configures GPIO6 for EPWMSYNCI operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Configures GPIO32 for EPWMSYNCI operation.

	/* Configure EPWMSYNC0  */

	/* Disable internal pull-up for the selected output pins
	   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWMSYNCO)
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;   // Disable pull-up on GPIO33 (EPWMSYNCO)

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;   // Configures GPIO6 for EPWMSYNCO
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;  // Configures GPIO33 for EPWMSYNCO

}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio ( void )
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO42 = 0;	  // Enable pull-up on GPIO42 (TZ1)
// GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;	  // Enable pull-up on GPIO50 (TZ1)
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0;	  // Enable pull-up on GPIO43 (TZ2)
// GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;    // Enable pull-up on GPIO51 (TZ2)
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)
// GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;    // Enable pull-up on GPIO52 (TZ3)

	/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO42 = 3;  // Asynch input GPIO42 (TZ1)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 3;  // Asynch input GPIO50 (TZ1)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 3;  // Asynch input GPIO43 (TZ2)
// GpioCtrlRegs.GPBQAEL2.bit.GPIO51 = 3;  // Asynch input GPIO51 (TZ2)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)
// GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 3;  // Asynch input GPIO52 (TZ3)


	/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
// GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 2;  // Configure GPIO42 as TZ1
// GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 3;  // Configure GPIO50 as TZ1
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
// GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 2;  // Configure GPIO43 as TZ2
// GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 3;  // Configure GPIO51 as TZ2
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3
// GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 3;  // Configure GPIO52 as TZ3

	EDIS;

}
void InitEPwm1()		//LLC1 DRV
{
	// Setup TBCLK
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
//	EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm1Regs.TBPRD = EPWM_PFC_SW_FREQUENCY;		// Set Switching frequency
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;			// Set as master
	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;			// Set as master, phase =0
	EPwm1Regs.TBCTR = 0x0000;                  // Clear counter

	// Setup shadow register load on ZERO
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;			// Load on CTR=PRD
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;			// Load on CTR=PRD

	// Set Compare values
	EPwm1Regs.CMPA.half.CMPA = ( EPWM_PFC_SW_FREQUENCY>>1 ) + EPWM_PFC_DRV_DEAD_BAND;	// Set duty as 50%
	EPwm1Regs.CMPB = ( EPWM_PFC_SW_FREQUENCY>>1 );			// Set duty as 25%

	// Set actions
	EPwm1Regs.AQCTLA.bit.CAU =	AQ_SET; 					// Set PWM1A on Zero
	EPwm1Regs.AQCTLA.bit.CAD =	AQ_CLEAR; 				// Clear PWM1A on event A, up count
	EPwm1Regs.AQCTLB.bit.CBU =  AQ_CLEAR;				// Clear PWM1B on PRD
	EPwm1Regs.AQCTLB.bit.CBD = 	AQ_SET;					// Set PWM1B on event A, up count

//	// Set Dead-band
//	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;				// EPWMxA is the source for both delays
//	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;		// Enable Dead-band module
//	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;			// Active High Complementary (AHC)
//	EPwm1Regs.DBRED = EPWM_PFC_DRV_DEAD_BAND;				// Set Dead-band initially
//	EPwm1Regs.DBFED = EPWM_PFC_DRV_DEAD_BAND;				// Set Dead-band initially

	//SYNC BOOST
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module

	// Trig ADC;
	EPwm1Regs.ETSEL.bit.SOCAEN	= ET_ENABLE;		// Enable SOC on A group --ADC_B1~I_Boost_1
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;		// Select SOC from PRD
	EPwm1Regs.ETPS.bit.SOCAPRD	= ET_2ND;		// Generate pulse on 1st event

	// Configure TZ1 for software control
	EALLOW;
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWM1A to low at fault
	EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// set EPWM1B to low at fault instant
	EPwm1Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt
	//EPwm1Regs.TZEINT.bit.CBC=TZ_INT_ENABLE;

	

	// Define an event (DCAEVT2) for Current CBC
	EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;        // DCAH = Comparator 1 output
	EPwm1Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm1Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;			// set EPWMxB to low at fault
	EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm1Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
	EPwm1Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm1Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path

	EPwm1Regs.TZEINT.bit.DCAEVT2=ET_ENABLE;
	EPwm1Regs.TZEINT.bit.DCBEVT2=ET_ENABLE;
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Select INT on Zero event
//	EPwm1Regs.ETSEL.bit.INTEN = ET_ENABLE;			// Enable INT
//	EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;				// Generate INT on 3rd event
	
}

void InitEPwm2()		//
{
	// Setup TBCLK
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
//	EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm2Regs.TBPRD = EPWM_PFC_SW_FREQUENCY;		// Set Switching frequency
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Set as master
	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;			// Set as master, phase =0
	EPwm2Regs.TBCTR = 0x0000;				   // Clear counter

	// Setup shadow register load on ZERO
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;			// Load on CTR=PRD
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;			// Load on CTR=PRD

	// Set Compare values
	EPwm2Regs.CMPA.half.CMPA = ( EPWM_PFC_SW_FREQUENCY>>1 ) + EPWM_PFC_DRV_DEAD_BAND;	// Set duty as 50%
	EPwm2Regs.CMPB = ( EPWM_PFC_SW_FREQUENCY>>1 );			// Set duty as 25%

	// Set actions
	EPwm2Regs.AQCTLA.bit.CAU =	AQ_SET; 					// Set PWM1A on Zero
	EPwm2Regs.AQCTLA.bit.CAD =	AQ_CLEAR;				// Clear PWM1A on event A, up count
	EPwm2Regs.AQCTLB.bit.CBU =	AQ_CLEAR;				// Clear PWM1B on PRD
	EPwm2Regs.AQCTLB.bit.CBD =	AQ_SET; 				// Set PWM1B on event A, up count

//	// Set Dead-band
//	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_RED_DBB_FED;				// EPWMxA is the source for both delays
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;		// Enable Dead-band module
//	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;			// Active High Complementary (AHC)
//	EPwm2Regs.DBRED = EPWM_PFC_DRV_DEAD_BAND;				// Set Dead-band initially
//	EPwm2Regs.DBFED = EPWM_PFC_DRV_DEAD_BAND;				// Set Dead-band initially

	//SYNC BOOST
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module

	// Trig ADC;
	EPwm2Regs.ETSEL.bit.SOCAEN	= ET_ENABLE;		// Enable SOC on A group --ADC_B1~I_Boost_1
	EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;		// Select SOC from PRD
	EPwm2Regs.ETPS.bit.SOCAPRD	= ET_1ST;		// Generate pulse on 1st event

	// Configure TZ1 for software control
	EALLOW;
	EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWM1A to low at fault
	EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// set EPWM1B to low at fault instant
	EPwm2Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt
	//EPwm2Regs.TZEINT.bit.CBC=TZ_INT_ENABLE;

	

	// Define an event (DCAEVT2) for Current CBC
//	EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;		  // DCAH = Comparator 1 output
//	EPwm2Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
//	EPwm2Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;			// set EPWMxB to low at fault
//	EPwm2Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;			  // DCAL = TZ2
//	EPwm2Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
//	EPwm2Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI; 			 // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
//	EPwm2Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;				  // DCAEVT1 = DCAEVT1 (not filtered)
//	EPwm2Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC; 	  // Take async path

//	EPwm2Regs.TZEINT.bit.DCAEVT2=ET_ENABLE;
//	EPwm2Regs.TZEINT.bit.DCBEVT2=ET_ENABLE;
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Select INT on Zero event
//	EPwm2Regs.ETSEL.bit.INTEN = ET_ENABLE;			// Enable INT
//	EPwm2Regs.ETPS.bit.INTPRD = ET_3RD; 			// Generate INT on 3rd event

}


/*
void InitEPwm3()		//LLC1 SR
{
	// Setup TBCLK
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
//	EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm3Regs.TBPRD = EPWM_LLC_SW_FREQUENCY;       // Set Switching frequency
	EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;			// Set as master
	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;			// Set as master, phase =0
	EPwm3Regs.TBCTR = 0x0000;                  // Clear counter

	// Setup shadow register load on ZERO
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;			// Load on CTR=PRD
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;			// Load on CTR=PRD

	// Set Compare values
	EPwm3Regs.CMPA.half.CMPA = ( EPWM_LLC_SW_FREQUENCY>>1 ) + EPWM_LLC_SR_DEAD_BAND;	// Set duty as 50%
	EPwm3Regs.CMPB = ( EPWM_LLC_SW_FREQUENCY>>1 ) - EPWM_LLC_SR_DEAD_BAND;			// Set duty as 25%

	// Set actions
	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET; 					// Set PWM1A on Zero
	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR; 				// Clear PWM1A on event A, up count
	EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR; 				// Clear PWM1B on PRD
	EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;					// Set PWM1B on event A, up count

	// Set Dead-band
//	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// EPWMxA is the source for both delays
//	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;		// Enable Dead-band module
//	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;			// Active High Complementary (AHC)
//	EPwm3Regs.DBRED = EPWM_LLC_DRV_DEAD_BAND;				// Set Dead-band initially
//	EPwm3Regs.DBFED = EPWM_LLC_DRV_DEAD_BAND;				// Set Dead-band initially

	//SYNC BOOST
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through

	// Configure TZ1 for software control
	EALLOW;
	EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWM1A to low at fault
	EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// set EPWM1B to low at fault instant
	EPwm3Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt

	// Define an event (DCAEVT2) for Current CBC
	EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;        // DCAH = Comparator 1 output
	EPwm3Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm3Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;			// set EPWMxB to low at fault
	EPwm3Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm3Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
	EPwm3Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm3Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm3Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
//	EPwm3Regs.ETSEL.bit.INTEN = ET_ENABLE;                // Enable INT
//	EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}

void InitEPwm4()		//LLC2 SR
{
	// Setup TBCLK
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
//	EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm4Regs.TBPRD = EPWM_LLC_SW_FREQUENCY;       // Set Switching frequency
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;						// Slave module
	EPwm4Regs.TBPHS.half.TBPHS = ( EPWM_LLC_SW_FREQUENCY>>1 );	// Phase is 90 deg
	EPwm4Regs.TBCTR = 0x0000;                  // Clear counter

	// Setup shadow register load on ZERO
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;			// Load on CTR=PRD
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;			// Load on CTR=PRD

	// Set Compare values
	EPwm4Regs.CMPA.half.CMPA = ( EPWM_LLC_SW_FREQUENCY>>1 ) + EPWM_LLC_SR_DEAD_BAND;	// Set duty as 50%
	EPwm4Regs.CMPB = ( EPWM_LLC_SW_FREQUENCY>>1 ) - EPWM_LLC_SR_DEAD_BAND;			// Set duty as 25%

	// Set actions
	EPwm4Regs.AQCTLA.bit.CAU = AQ_SET; 					// Set PWM1A on Zero
	EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR; 				// Clear PWM1A on event A, up count
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR; 				// Clear PWM1B on PRD
	EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;					// Set PWM1B on event A, up count

	// Set Dead-band
//	EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;				// EPWMxA is the source for both delays
//	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;		// Enable Dead-band module
//	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;			// Active High Complementary (AHC)
//	EPwm4Regs.DBRED = EPWM_LLC_SR_DEAD_BAND;				// Set Dead-band initially
//	EPwm4Regs.DBFED = EPWM_LLC_SR_DEAD_BAND;				// Set Dead-band initially

	//SYNC BOOST
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through

	// Configure TZ1 for software control
	EALLOW;
	EPwm4Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWM1A to low at fault
	EPwm4Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// set EPWM1B to low at fault instant
	EPwm4Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt

	// Define an event (DCAEVT2) for Current CBC
	EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;        // DCAH = Comparator 1 output
	EPwm4Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm4Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;			// set EPWMxB to low at fault
	EPwm4Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm4Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
	EPwm4Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm4Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm4Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
//	EPwm4Regs.ETSEL.bit.INTEN = ET_ENABLE;                // Enable INT
//	EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}

void InitEPwm5()
{
	// Setup TBCLK
	EPwm5Regs.TBPRD = EPWM_BOOST_SW_FREQUENCY;       // Set Switching frequency
	EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;    // Master module
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm5Regs.TBPHS.half.TBPHS = 0x0000;       // Phase is 0
	EPwm5Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm5Regs.CMPA.half.CMPA = 0; 	// Duty control
	EPwm5Regs.CMPB = 0;           // Set Compare B value

	// Set Actions
	EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;         //Set PWM3A on Zero, up count
	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // Clear PWM3A on event B, up count

	//SYNC BOOST
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down-stream module

	// Trig ADC;
	EPwm5Regs.ETSEL.bit.SOCAEN	= ET_ENABLE;		// Enable SOC on A group --ADC_B1~I_Boost_1
	EPwm5Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPB;		// Select SOC from CMPB on upcount
	EPwm5Regs.ETPS.bit.SOCAPRD	= ET_1ST;		// Generate pulse on 1st event

	// Configure TZ1 for software control
	EALLOW;
	EPwm5Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWMxA to low at fault
//	EPwm5Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// set EPWMxB to low at fault instant
	EPwm5Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt

	// Define an event (DCAEVT2) for Current CBC
	EPwm5Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP2OUT;        // DCAH = Comparator 1 output
	EPwm5Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm5Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
	EPwm5Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm5Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm5Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm5Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	//Define an event (DCBEVT2) for OVP CBC
	EPwm5Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP3OUT;        // DCAH = Comparator 1 output
	EPwm5Regs.TZCTL.bit.DCBEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm5Regs.TZSEL.bit.DCBEVT2 = TZ_ENABLE;			// oneshot source
	EPwm5Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm5Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm5Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm5Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on event B, up count
//	EPwm5Regs.ETSEL.bit.INTEN = ET_ENABLE;                // Enable INT
//	EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on every event
}

void InitEPwm6()
{
	// Setup TBCLK
	EPwm6Regs.TBPRD = EPWM_BOOST_SW_FREQUENCY;       // Set Switching frequency
	EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;    // Slave module
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm6Regs.TBPHS.half.TBPHS = ( EPWM_BOOST_SW_FREQUENCY>>1 ); // Phase = 180 deg
	EPwm6Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;   // Clock ratio to SYSCLKOUT
	EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm6Regs.CMPA.half.CMPA = 0; // Duty control
	EPwm6Regs.CMPB = 0;           // Set Compare B value

	// Set Actions
	EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;         //Set PWM3A on Zero, up count
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // Clear PWM3A on event B, up count

	//SYNC BOOST
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through

	// Trig ADC;
	EPwm6Regs.ETSEL.bit.SOCAEN	= ET_ENABLE;		// Enable SOC on A group --ADC_B1~I_Boost_1
	EPwm6Regs.ETSEL.bit.SOCASEL = ET_CTRU_CMPB;		// Select SOC from CMPB on upcount
	EPwm6Regs.ETPS.bit.SOCAPRD	= ET_1ST;		// Generate pulse on 1st event

	// Configure TZ1 for software control
	EALLOW;
	EPwm6Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// set EPWMxA to low at fault
	//	EPwm6Regs.TZCTL.bit.TZB = TZ_NO_CHANGE;			//
	EPwm6Regs.TZEINT.bit.OST = TZ_INT_DISABLE;		// Disable TZ interrupt
	
	// Define an event (DCAEVT2) for Current CBC
	EPwm6Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP2OUT;        // DCAH = Comparator 1 output
	EPwm6Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
	EPwm6Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
	EPwm6Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;             // DCAL = TZ2
	EPwm6Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
	EPwm6Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
	EPwm6Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	//Define an event (DCBEVT2) for OVP CBC
//	EPwm6Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP3OUT;        // DCAH = Comparator 1 output
//	EPwm6Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_LO;			// set EPWMxA to low at fault
//	EPwm6Regs.TZSEL.bit.DCAEVT2 = TZ_ENABLE;			// oneshot source
//	EPwm6Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;             // DCAL = TZ2
//	EPwm6Regs.TZDCSEL.bit.DCBEVT2 = TZ_DCAH_HI;              // DCAEVT1 =  DCAH low(will become active as Comparator output goes low)
//	EPwm6Regs.DCBCTL.bit.EVT2SRCSEL = DC_EVT2;                // DCAEVT1 = DCAEVT1 (not filtered)
//	EPwm6Regs.DCBCTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;       // Take async path
	EDIS;

	// Interrupt where we will change the Compare Values
//	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
//	EPwm6Regs.ETSEL.bit.INTEN = ET_ENABLE;                // Enable INT
//	EPwm6Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}
*/

//===========================================================================
// End of file.
//===========================================================================
