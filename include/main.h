/*
 * main.h
 *
 *  Created on: 2017Äê9ÔÂ4ÈÕ
 *      Author: zxid
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stdint.h"



typedef 	unsigned char 	BYTE;
typedef     unsigned int	WORD;
typedef     unsigned short	u16;
typedef     		 short	i16;
typedef     unsigned long	u32;
typedef     		long	i32;



typedef struct
{
	signed short int inter_A1;
	signed short int inter_A2;
	signed short int inter_A3;
	signed short int error_z1;
	signed short int error_z2;
	long Uout_z1;


}	CTRL2P2Z_coeff;
extern CTRL2P2Z_coeff  CTRL2P2Z_COEFF_VOLTAGE_LOOP;
extern CTRL2P2Z_coeff  CTRL2P2Z_COEFF_current_LOOP;
//extern CTRL2P2Z_coeff CTRL2P2Z_COEFF_inter_LOOP;

typedef union
{
	struct
	{
		unsigned TimerExpired		:1;
		unsigned TaskRunning	:1;
		unsigned TaskTooLong	:1;
	} bits;
	BYTE         byByte;
} T_TimerFlags;


typedef struct tagT_Timer
{
	WORD 			wTimerValue;                 	// contains the timer value
	char 			byThreadLevel;		    		// Contains the Thread Level, 0xFF means that timer is called

	T_TimerFlags 	tTimerFlags;
} T_Timer;



typedef struct tagT_AllTimers_1ms
{
	T_Timer t_High_Level_Task_1;
	T_Timer t_Normal_Level_Task_1;
	T_Timer t_Fault_check_Task;
	T_Timer t_filter_Task;

} T_AllTimers_1ms;

typedef struct tagT_AllTimers_10ms
{

	T_Timer	t_Start_Up_Delay_Timer_2;
	T_Timer t_Low_Level_Task_1;
	T_Timer t_WDT_Reset_Timer;							//used to reset WDT timer


} T_AllTimers_10ms;

typedef struct tagT_AllTimers_100ms
{
	T_Timer  t_CPU_Usage_Timer;
	T_Timer  t_Start_Up_Delay_Timer;

} T_AllTimers_100ms;

typedef struct tagT_AllTimers_1sec
{
	T_Timer t_Timers_1secTimer;
	T_Timer t_Bulk_OV_Reset_Timer;
} T_AllTimers_1sec;


typedef struct tagT_AllTimers
{
	T_AllTimers_1ms         t_Timers_1ms;
	T_AllTimers_10ms        t_Timers_10ms;
	T_AllTimers_100ms       t_Timers_100ms;
	T_AllTimers_1sec        t_Timers_1sec;
	unsigned char                   by10msecCounter;
	unsigned char                     by100msecCounter;
	unsigned char                     by1secCounter;
} T_AllTimers;


extern volatile T_AllTimers 	t_Timers;



typedef enum _TAG_STATE_Machine
{
	Battery_STANDBY=0,
	Check_batery,
	Boost_batter,
	Charge__low_battery,
	Stop_charge

} Machine;

extern Machine Charge_process;

//typedef union POWER_FLAGS_TAG
//{
//	unsigned int flags;
//	struct
//	{
//		unsigned AC_UV 					:1;
//		unsigned AC_OV            	  	:1;
//		unsigned VbusOVFault          	:1;
//		unsigned PS_shutdown       		:1;

//		unsigned Charge_enable           :1;
//		unsigned High_battery_ov            :1;
//		unsigned High_battery_uv           :1;
//		unsigned Low_battery_uv            :1;

//		unsigned Low_battery_ov                :1;
//		unsigned Charger_oc               :1;
//		unsigned OT             :1;
//		unsigned VBOOST_UV             :1;

//		unsigned VBOOST_OV             :1;
//		unsigned RES		:3;
//	} b;
//} POWER_FLAGS;

//extern POWER_FLAGS POWERFlags;


typedef enum _TAG_STATE_MACHINE
{
	STATE_STANDBY=0,
	STATE_CALI_CURR_ZRO,
	STATE_SOFT_START,
	STATE_RUN,
	STATE_RESTART_INIT,
	STATE_RESTART_DELAY,
	STATE_CONTROL_INIT
} MACHINE;

extern MACHINE uPowerState;

//typedef union P_FLAGS_TAG
//{
//	unsigned int flags;
//	struct
//	{
//		unsigned int  LLC_power   :1;
//		unsigned int  LLC_isrunning  :1;
//		unsigned int  Boost_power   :1;
//		unsigned int  SR_ON   :1;
//		unsigned int  Charge_ONCE   :1;
//		unsigned int  resverd   :11;

//	} b;
//} P_FLAGS;

typedef union PFC_FLAGS_TAG
{
	unsigned int flags;
	struct
	{
		unsigned AC_OV			:1;	// Startup sync
		unsigned AC_UV			:1; // Gain mode
//    	unsigned enable	 		:1;	// PFC enable flag
		unsigned VbusOVFault	 		:1;	// PFC enable flag
		unsigned started		:1;	// Softstart tracking
//    	unsigned gain			:1;	// Gain mode

		unsigned ramp			:1;	// Indicates the ref is ramping
		unsigned droop_en		:1;	// Bus drooping enable flag
		unsigned bus_ctl		:1;	// Vbus control event
		unsigned bus_up			:1;	// Droop override flag

		unsigned CBC_OC		:1;	// Indicates one or two phase operation
		unsigned valley			:1;	// Indicates the line cycle valley
		unsigned Is_N_greater_than_L	:1;	// Indicates zero dv/dt crossover in line
		unsigned t1ms_Triger		:1;

		unsigned t200us_Triger      :1;
		unsigned PFC_Neg_off         :1;
		unsigned PFC_Pos_off         :1;
		unsigned bus_ctl_fast	:1;
	} b;
} PFC_FLAGS;

extern PFC_FLAGS uPFCFlags;


#define True 1
#define  Fause 0

#define TRUE 1
#define  FALSE 0

#define END_VALUE_10MSEC  10  	//This value is based on the 1 msec timer. For 10msec = 10 x  1msec
#define END_VALUE_100MSEC 10  	//This value is based on the 10 msec timer. For 100msec = 10 x  10msec
#define END_VALUE_1SEC	  10 	//This value is based on the 100 msec timer. For 1 sec =  10 x 100msec

//#define	Test_duty
#define  Fault_check_time_1MS_5    5

#define  PSU_process_time_1MS_1    1

#define  PSU_process_time_1MS_100    200

#define  PSU_process_time_1MS_10    10



//#define  MAX_POWER          2800*65535


#define  UV_24V_LOST   V_24V_gain*9

#define  UV_24V_LOST_RECOVER   V_24V_gain*11


//TODO
#define V_BULK_GAIN					(5.6875)
#define V_IN_AC_GAIN				(000)


//#define mVbus_Control_Trig()		(uPFCFlags.b.bus_ctl)
#define m200US_Trig()				(uPFCFlags.b.t200us_Triger)
#define MAX_PFC_DUTY          		(u16)((double)EPWM_PFC_SW_FREQUENCY*0.95)
#define MIN_PFC_DUTY          		(u16)(3)

#define AD_u16_I_AC_ZERO          		(1500)
#define	PFC_BUS_VSQUARE_SAT				(1200)
#define PRI_VBUS_OV_WARN          		(u16)((double)430*V_BULK_GAIN)
#define PRI_VBUS_OV_FAULT          		(u16)((double)440*V_BULK_GAIN)
#define PRI_VBUS_UP          			(u16)((double)360*V_BULK_GAIN)
#define PRI_VBUS_30V          			(u16)((double)30*V_BULK_GAIN)
#define PRI_VBUS_45V          			(u16)((double)45*V_BULK_GAIN)
#define PRI_VBUS_60V          			(u16)((double)60*V_BULK_GAIN)
#define PRI_VBUS_80V          			(u16)((double)80*V_BULK_GAIN)
#define PRI_VBUS_100V          			(u16)((double)100*V_BULK_GAIN)
#define PRI_VBUS_120V          			(u16)((double)120*V_BULK_GAIN)
#define PRI_VBUS_140V          			(u16)((double)140*V_BULK_GAIN)
#define PRI_VBUS_160V          			(u16)((double)160*V_BULK_GAIN)
#define PRI_VBUS_180V          			(u16)((double)180*V_BULK_GAIN)
#define PRI_VBUS_200V          			(u16)((double)200*V_BULK_GAIN)
#define PRI_VBUS_250V          			(u16)((double)250*V_BULK_GAIN)
#define PRI_VBUS_300V          			(u16)((double)300*V_BULK_GAIN)
#define PRI_VBUS_350V          			(u16)((double)350*V_BULK_GAIN)
#define PRI_VBUS_380V          			(u16)((double)380*V_BULK_GAIN)
#define PRI_VBUS_400V          			(u16)((double)400*V_BULK_GAIN)
#define PRI_VBUS_420V          			(u16)((double)420*V_BULK_GAIN)
#define PRI_VBUS_450V          			(u16)((double)450*V_BULK_GAIN)

#define CNT_PWR_STAT_TIME_MS(x)   		(u16)((double)x*5)	//x<13100 ~ 13s


//#define EPWM1A_DB						EPwm1Regs.DBRED 				
//#define EPWM1B_DB						EPwm1Regs.DBFED 

#define PFC_EPWMxA_CMPA						EPwm1Regs.CMPA.half.CMPA 				
#define PFC_EPWMxB_CMPB						EPwm1Regs.CMPB 				

#define GL_SR_ClrVal()						GpioDataRegs.GPADAT.bit.GPIO2 = 0;
#define GL_SR_SetVal()						GpioDataRegs.GPADAT.bit.GPIO2 = 1;

#define GH_SR_ClrVal()						GpioDataRegs.GPADAT.bit.GPIO3 = 0;
#define GH_SR_SetVal()						GpioDataRegs.GPADAT.bit.GPIO3 = 1;

#define L_LINE_SR_ON()						GpioDataRegs.GPADAT.bit.GPIO0	= 1;//Value 0
#define L_LINE_SR_OFF()						GpioDataRegs.GPADAT.bit.GPIO0	= 0;//Value 0

#define N_LINE_SR_ON()						GpioDataRegs.GPADAT.bit.GPIO1	= 1;//Value 0
#define N_LINE_SR_OFF()						GpioDataRegs.GPADAT.bit.GPIO1	= 0;//Value 0

#define DUTY_EPWMA_OFF 						(EPWM_PFC_SW_FREQUENCY)
#define DUTY_EPWMB_OFF 						(0)
//#define DUTY_EPWMA_OFF 						(EPWM_PFC_SW_FREQUENCY>>1)

#define TEST_SET()							GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
#define TEST_CLR()							GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
#define TEST_TOGGLE()						GpioDataRegs.GPBDAT.bit.GPIO34 = ~GpioDataRegs.GPBDAT.bit.GPIO34;

#define LED_ON()							GpioDataRegs.GPADAT.bit.GPIO17 = 1;//Value 0
#define LED_OFF()							GpioDataRegs.GPADAT.bit.GPIO17 = 0;//Value 0
#define LED_TOGGLE()						GpioDataRegs.GPADAT.bit.GPIO17 = ~GpioDataRegs.GPADAT.bit.GPIO17;//Value 0

#define RELAY_ON()							GpioDataRegs.GPBDAT.bit.GPIO33	= 1;
#define RELAY_OFF()							GpioDataRegs.GPBDAT.bit.GPIO33	= 0;

#define IO_2_SEC_PFC_ON()							GpioDataRegs.GPADAT.bit.GPIO4	= 0;//Verfied
#define IO_2_SEC_PFC_OFF()							GpioDataRegs.GPADAT.bit.GPIO4	= 1;//Verfied


#define PFC_PROTECT1_EN()							GpioDataRegs.GPADAT.bit.GPIO6	= 1;//
#define PFC_PROTECT1_DIS()							GpioDataRegs.GPADAT.bit.GPIO6	= 0;//

#define PFC_PROTECT2_EN()							GpioDataRegs.GPADAT.bit.GPIO7	= 0;//
#define PFC_PROTECT2_DIS()							GpioDataRegs.GPADAT.bit.GPIO7	= 1;//

#define PFC_PROTECT3_EN()							GpioDataRegs.GPADAT.bit.GPIO12	= 0;//
#define PFC_PROTECT3_DIS()							GpioDataRegs.GPADAT.bit.GPIO12	= 1;//





/********************************* DEFINES ***********************************/
#define RESOLUTION        ((1<<15) - 1)
#define ADC_RESOLUTION    ((1<<12) - 1)

//#define IPV_RANGE   		(281.6)	// Input voltage measurable range, V
//#define IPV_RANGE   		(502)	// Input voltage measurable range, V
//#define IPV_RANGE   		(446.8)	// Input voltage measurable range, V
#define IPV_RANGE   		(442.4)	// Input voltage measurable range, V

#define IP_V(x)     		((uint16_t)((double)x*ADC_RESOLUTION/IPV_RANGE)) // Input voltage scale in Q15



//#define IP_BULKV_RANGE  (496.2)	// Bulk voltage measurable range, V
//#define IP_BULKV_RANGE  (464.39)
//#define IP_BULKV_RANGE  (464.4)	// Bulk voltage measurable range, V
#define IP_BULKV_RANGE  (481.53)//coefficient  of ï¿½0.00685311*Vbulkï¿½
#define IP_BULKV(x)   	((uint16_t)((double)x*RESOLUTION/IP_BULKV_RANGE)) // Input voltage scale in Q15   521VMax



//#define IPI_RANGE_IIN1  (38.49)	//Input current measurable range if IIN1, A
//#define IP_A_IIN1(x)    ((uint16_t)((double)x*RESOLUTION/IPI_RANGE)) // Input current scale in Q15

//x*0.01*(33/1.21)*20/22 = 3.3
//                     x = 13.31A

//#define IPI_RANGE_IIN1  (18.15)	//Input current measurable range if IIN1, A
#define IPI_RANGE_IIN1  (13.31)	//Input current measurable range if IIN1, A
#define IP_A_IIN1(x)    ((uint16_t)((double)x*RESOLUTION/IPI_RANGE_IIN1)) // Input current scale in Q15

//#define IPI_RANGE_IIN2  (18.15)	//Input current measurable range if IIN2, A
#define IPI_RANGE_IIN2  (29.27)	//Input current measurable range if IIN2, A
#define IP_A_IIN2(x)    ((uint16_t)((double)x*RESOLUTION/IPI_RANGE_IIN2)) // Input current scale in Q15

//#define IPI_RANGE_IIN2   (39.5)	//Input current measurable range, A
//#define IP_A_IIN2(x)     ((uint32_t)((double)x*RESOLUTION/IPI_RANGE_CH2)) // Input current scale in Q15
//#define K16_VAC_DIFF_PRT_TH     IP_V(7.5)

//offset of IIN1 and IIN2 current sense
#define IIN1_OFFSET	(0.10)		//IIN1 Current sense offest voltage, V
#define K16_IIN1_ADC_OFFSET		(uint16_t)((double)(IIN1_OFFSET*ADC_RESOLUTION)/3.3)
#define IIN2_OFFSET	(0.12)		//IIN2 Current sense offest voltage, V
#define K16_IIN2_ADC_OFFSET		(uint16_t)((double)(IIN2_OFFSET*ADC_RESOLUTION)/3.3)
	
#define K16_BULK_OV_CLR_TH					     IP_BULKV(410)

#define K16_VIN_208V                     IP_V(158)
#define K16_VIN_100V                     IP_V(100)

#define K16_VIN_208V_OC_FAULT_LIMIT      IP_A_IIN2(9)
#define K16_VIN_208V_OC_FAULT_CLR_LIMIT  IP_A_IIN2(8.5)
#define K16_VIN_100V_OC_FAULT_LIMIT      IP_A_IIN2(4.5)
#define K16_VIN_100V_OC_FAULT_CLR_LIMIT  IP_A_IIN2(4)


#define  test_cnt   1500

//#define  Vol_loop_only

//Voltage/3.3*4095*8=12280
#define Temper_Vol(x) (uint16_t)((32760*(double)x)/3.3)
//1.237-->110C
//1.278-->108C
#define K16_PRI_HS_OTP_THD     Temper_Vol(1.278)

//1.568V-->95C
//1.568/3.3*4095*8=15565.96
#define K16_PRI_HS_OTP_CLR_THD Temper_Vol(1.568)


//Moving average calculation
#define K8_MOVING_AVG_BUFF_SIZE 32	//Array size is 32
#define K8_MOVING_AVG_SUM_SHIFT 5		//2^n=32, so n =5

#define	PRI_VBUS_ADJ_HYST			12
#define	PRI_VBUS_ADJ_SLOPE			38

/******************************** TYPEDEFS ***********************************/
typedef enum tag_FreqStateType
{
    INPUT_FREQUENCY_LOW		= 0,
    INPUT_FREQUENCY_NORMAL	,
    INPUT_FREQUENCY_HIGH
}FreqStateType;

typedef struct
{
	uint32_t u32Buff[K8_MOVING_AVG_BUFF_SIZE];
	uint32_t bufPtr;
	uint64_t u64SampleSum;
}T_movingAvg32;

typedef union tagu32WordsType {
    unsigned long LongWord;

    struct {
        unsigned LSW : 16;
        unsigned MSW : 16;
    }bit;
} u32WordsType;

//typedef unsigned long uint32_t;
//typedef unsigned short uint16_t;
typedef unsigned char uint8_t;






//extern P_FLAGS uPFlags;

//extern u16 u16LLC_frequence;
//extern u16 u16LLC_frequence_deadtime;

//extern u16  V_charge_target;
//extern u16  I_charge_target;

//extern u16 V_charge_ref;
//extern u16 I_charge_ref;
//extern u16  Avg_u16_V_lowbattery;
//extern u16  Avg_u16_V_Highbattery;
//extern u16  Avg_u16_V_Boostout;
//extern u16  Avg_u16_V_24v;
//extern u16  Avg_u16_V_tempurtaion;
//extern u16  Avg_u16_I_LLC1;

//extern u16  AD_u16_V_lowbattery;
//extern u16  AD_u16_V_Highbattery;
//extern u16  AD_u16_V_Boostout;
//extern u16  AD_u16_V_24v;
//extern u16  AD_u16_I_LLC1;
//extern u16  AD_u16_I_LLC2;
//extern u16  AD_u16_V_tempurtaion;
//extern u16  AD_u16_l_boost1;
//extern u16  AD_u16_l_boost2;
//extern u32  Max_power_target;


////////////////////////////////////
extern u16	AD_u16_I_AC;
extern u16	AD_u16_CALI_I_ZRO;
extern u16	AD_u16_U_HV_FB;
extern u16	AD_u16_U_AC_L_FB;
extern u16	AD_u16_U_AC_N_FB;
extern u16	AD_u16_U_3V_REF;

extern u16	uIctl_Ref;
extern u16	u16Xvin;
extern u16	u16Xiin;
extern u16	uVbus_Area;
extern u16	uVbus_Ref;
//extern u32	u32AvgVbus;
extern u16	u16AvgVbus;
extern u16	uVbus_Gain_Adj_AC;
extern u16	uIsenseAdj;
extern u16 u8IpSampleCnt;
extern u32 u32IpVoltSumOfSquare;
extern u16 u16IpVoltRMS;
extern u16	uAvgSqVin_z1;
extern u16	uVbus_Ref_Target;
extern u16	Flag_Txd;
extern i16	iVbus_Err;
extern u16	temp;



//extern void 	PSU_process ( void );
extern void Power_state_control ( void );
extern void Timer_Handler_GS ( void );
extern void Thread_Handler_GS ( void );
//extern  short PI_Boost_internal ( int Voutref, int VoutT,long Max_out,CTRL2P2Z_coeff* CTRL2p2z,long U32Min_out );
extern  short PI_Boost_internal ( int error,long Max_out,CTRL2P2Z_coeff* CTRL2p2z,long U32Min_out );
extern  short PI_VBus ( i16 error, i32 Max_out,CTRL2P2Z_coeff* CTRL2p2z,i32 U32Min_out );
extern void Vbus_Generate_Err ( void );
extern void Check_Fast_Bus_Voltage_Conditions ( void );
extern void Vbus_Control ( void );
extern void Vbus_Feedforward_Scaling ( void );
extern void InitThread ( void );
extern void period_200us_repetitive ( void );
extern void period_1ms_repetitive ( void );
extern void Vbus_Ref_Control_Process ( void );
extern void Filter_date ( void );


#endif /* INC_MAIN_H_ */
