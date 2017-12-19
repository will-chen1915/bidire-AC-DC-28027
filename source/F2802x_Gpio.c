// TI File $Revision: /main/1 $
// Checkin $Date: December 5, 2008   18:01:01 $
//###########################################################################
//
// FILE:	DSP2803x_Gpio.c
//
// TITLE:	DSP2803x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.21 $
// $Release Date: December 1, 2009 $
//###########################################################################

#include "F2802x_Device.h"     // DSP2803x Headerfile Include File
#include "F2802x_Examples.h"   // DSP2803x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio ( void )
{
	/*
	   // Each GPIO pin can be:
	   // a) a GPIO input/output
	   // b) peripheral function 1
	   // c) peripheral function 2
	   // d) peripheral function 3
	   // By default, all are GPIO Inputs
	   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
	   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
	   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO44
	   GpioCtrlRegs.AIOMUX1.all = 0x0000;     // Dig.IO funct. applies to AIO2,4,6,10,12,14

	   GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are GP inputs
	   GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO44 are inputs
	   GpioCtrlRegs.AIODIR.all = 0x0000;      // AIO2,4,6,19,12,14 are digital inputs

	   // Each input can have different qualification
	   // a) input synchronized to SYSCLKOUT
	   // b) input qualified by a sampling window
	   // c) input sent asynchronously (valid for peripheral inputs only)
	   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
	   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
	   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO44 Synch to SYSCLKOUT

	   // Pull-ups can be enabled or disabled.
	   GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
	   GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO44
	   //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
	   //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO44
	*/

	EALLOW;

	//EEPROM	SCLp	SDAp	WPp
	GpioCtrlRegs.GPAMUX2.bit.GPIO29	= 0;//SCLp
	GpioCtrlRegs.GPADIR.bit.GPIO29	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO29	= 0;//Value 0

	GpioCtrlRegs.GPAMUX2.bit.GPIO28	= 0;//SDAp
	GpioCtrlRegs.GPADIR.bit.GPIO28	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO28	= 0;//Value 0


	GpioCtrlRegs.GPBMUX1.bit.GPIO34	= 0;//test Pin R274
	GpioCtrlRegs.GPBDIR.bit.GPIO34	= 1;//Output
	GpioDataRegs.GPBDAT.bit.GPIO34	= 0;//Value 0




	GpioCtrlRegs.GPAMUX1.bit.GPIO6	= 0;//Low enable
	GpioCtrlRegs.GPADIR.bit.GPIO6	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO6	= 1;//Value 0

	GpioCtrlRegs.GPAMUX1.bit.GPIO7	= 0;//High enable
	GpioCtrlRegs.GPADIR.bit.GPIO7	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO7	= 0;//Value 1

	GpioCtrlRegs.GPAMUX1.bit.GPIO12	= 0;//High enable
	GpioCtrlRegs.GPADIR.bit.GPIO12	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO12	= 0;//Value 1


	//SCI TXD
//	GpioCtrlRegs.GPBMUX1.bit.GPIO18 = xxx;//TXDp
//	GpioCtrlRegs.GPBDIR.bit.GPIO18	= 1;//
//	GpioDataRegs.GPBDAT.bit.GPIO18	= 0;//Value 0

	//SCI RXD
//	GpioCtrlRegs.GPBMUX1.bit.GPIO19 = xxx;//RXDp
//	GpioCtrlRegs.GPBDIR.bit.GPIO19	= 1;//
//	GpioDataRegs.GPBDAT.bit.GPIO19	= 0;//Value 0

	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;//LED4 pin
	GpioCtrlRegs.GPADIR.bit.GPIO17	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO17 = 0;//Value 0

	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;//RELAY
	GpioCtrlRegs.GPBDIR.bit.GPIO33	= 1;//Output
	GpioDataRegs.GPBDAT.bit.GPIO33	= 0;//RELAY OFF

	GpioCtrlRegs.GPAMUX1.bit.GPIO4	= 0;//PFC-ON siginal to SEC
	GpioCtrlRegs.GPADIR.bit.GPIO4	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO4	= 0;//Value 0

	//PWM1 for GPIO 	
	GpioCtrlRegs.GPAMUX1.bit.GPIO2	= 0;//L or N line driver
	GpioCtrlRegs.GPADIR.bit.GPIO2	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO2	= 0;//Value 0

	GpioCtrlRegs.GPAMUX1.bit.GPIO3	= 0;//L or N line driver
	GpioCtrlRegs.GPADIR.bit.GPIO3	= 1;//Output
	GpioDataRegs.GPADAT.bit.GPIO3	= 0;//Value 0




//	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;   // Synch to SYSCLKOUT GPIO25 (CAP2)
//	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;//ECAP2

	EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
