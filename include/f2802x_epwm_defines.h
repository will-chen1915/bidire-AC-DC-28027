//###########################################################################
//
// FILE:   F2802x_EPwm_defines.h
//
// TITLE:  #defines used in EPwm examples
//
//###########################################################################
// $TI Release: F2802x Support Library v230 $
// $Release Date: Fri May  8 07:43:05 CDT 2015 $
// $Copyright: Copyright (C) 2008-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2802x_EPWM_DEFINES_H
#define F2802x_EPWM_DEFINES_H

#define ADD_BY_SEAN
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ADD_BY_SEAN

#define Reay_FRQUENCY      900//540
//#define Reay_FRQUENCY      540
#define Reay_step_duty     90//
#define  Reay_step_duty_max  (Reay_FRQUENCY+Reay_step_duty)

#define EPWM_SYSCLKOUT						(60)//MHz
#define EPWM_100KHZ							(100)//KHz
#define EPWM_20KHZ							(20)//KHz
#define EPWM_PFC_SW_KHZ(x)					((Uint16)((double)EPWM_SYSCLKOUT*500/x+0.5))// Switching frequency KHz
#define EPWM_PFC_DEAD_BAND_NS(x)			((Uint16)((double)x*EPWM_SYSCLKOUT/1000+0.5))// Switching frequency KHz
#define EPWM_LLC_SW_KHZ(x)					((Uint16)((double)EPWM_SYSCLKOUT*500/x+0.5))// Switching frequency KHz
#define EPWM_LLC_DEAD_BAND_NS(x)			((Uint16)((double)x*EPWM_SYSCLKOUT/1000+0.5))// Switching frequency KHz

#define EPWM_PFC_SW_FREQUENCY				(EPWM_PFC_SW_KHZ(EPWM_20KHZ))  //Switching frequency 20KHz
#define EPWM_PFC_MAX_CMPA					(Uint16)((double)0.9*EPWM_PFC_SW_FREQUENCY)// Max duty: 90%
#define EPWM_PFC_MIN_CMPA					(0)
#define EPWM_PFC_DRV_DEAD_BAND      		(EPWM_PFC_DEAD_BAND_NS(400))	//dead-band xxxns


#define EPWM_LLC_SW_HI_FREQUENCY				(EPWM_LLC_SW_KHZ(220))	//Switching frequency 200KHz

#define EPWM_LLC_SW_FREQUENCY				(EPWM_LLC_SW_KHZ(115))	//Switching frequency 100KHz
#define EPWM_LLC_MAX_FREQUENCY				(EPWM_LLC_SW_KHZ(300))
#define EPWM_LLC_MIN_FREQUENCY      		(EPWM_LLC_SW_KHZ(80))

#define EPWM_LLC_SW_FREQUENCY_boost				(EPWM_LLC_SW_KHZ(115))	//Switching frequency 115k

#define EPWM_LLC_DRV_DEAD_BAND_normal      		(EPWM_LLC_DEAD_BAND_NS(200))	//dead-band 200ns

#define EPWM_LLC_DRV_DEAD_BAND      		(EPWM_LLC_DEAD_BAND_NS(250))	//dead-band 200ns
#define EPWM_LLC_SR_DEAD_BAND      			(EPWM_LLC_DEAD_BAND_NS(350))	//dead-band 300ns
#define EPWM_LLC_DRV_DEAD_BAND_max      	(EPWM_LLC_DEAD_BAND_NS(900))	//(EPWM_LLC_DEAD_BAND_NS(900))	//dead-band 300ns
#define EPWM_LLC_SR_DEAD_BAND_max      			(EPWM_LLC_DEAD_BAND_NS(300))	//dead-band 300ns
#endif

// TBCTL (Time-Base Control)
//==========================
// CTRMODE bits
#define TB_COUNT_UP           0x0
#define TB_COUNT_DOWN         0x1
#define TB_COUNT_UPDOWN       0x2
#define TB_FREEZE             0x3
// PHSEN bit
#define TB_DISABLE            0x0
#define TB_ENABLE             0x1
// PRDLD bit
#define TB_SHADOW             0x0
#define TB_IMMEDIATE          0x1
// SYNCOSEL bits
#define TB_SYNC_IN            0x0
#define TB_CTR_ZERO           0x1
#define TB_CTR_CMPB           0x2
#define TB_SYNC_DISABLE       0x3
// HSPCLKDIV and CLKDIV bits
#define TB_DIV1               0x0
#define TB_DIV2               0x1
#define TB_DIV4               0x2
// PHSDIR bit
#define TB_DOWN               0x0
#define TB_UP                 0x1

// CMPCTL (Compare Control)
//==========================
// LOADAMODE and LOADBMODE bits
#define CC_CTR_ZERO           0x0
#define CC_CTR_PRD            0x1
#define CC_CTR_ZERO_PRD       0x2
#define CC_LD_DISABLE         0x3
// SHDWAMODE and SHDWBMODE bits
#define CC_SHADOW             0x0
#define CC_IMMEDIATE          0x1

// AQCTLA and AQCTLB (Action Qualifier Control)
//=============================================
// ZRO, PRD, CAU, CAD, CBU, CBD bits
#define AQ_NO_ACTION          0x0
#define AQ_CLEAR              0x1
#define AQ_SET                0x2
#define AQ_TOGGLE             0x3

// DBCTL (Dead-Band Control)
//==========================
// OUT MODE bits
#define DB_DISABLE            0x0
#define DBB_ENABLE            0x1
#define DBA_ENABLE            0x2
#define DB_FULL_ENABLE        0x3
// POLSEL bits
#define DB_ACTV_HI            0x0
#define DB_ACTV_LOC           0x1
#define DB_ACTV_HIC           0x2
#define DB_ACTV_LO            0x3
// IN MODE
#define DBA_ALL               0x0
#define DBB_RED_DBA_FED       0x1
#define DBA_RED_DBB_FED       0x2
#define DBB_ALL               0x3

// CHPCTL (chopper control)
//==========================
// CHPEN bit
#define CHP_DISABLE           0x0
#define CHP_ENABLE            0x1
// CHPFREQ bits
#define CHP_DIV1              0x0
#define CHP_DIV2              0x1
#define CHP_DIV3              0x2
#define CHP_DIV4              0x3
#define CHP_DIV5              0x4
#define CHP_DIV6              0x5
#define CHP_DIV7              0x6
#define CHP_DIV8              0x7
// CHPDUTY bits
#define CHP1_8TH              0x0
#define CHP2_8TH              0x1
#define CHP3_8TH              0x2
#define CHP4_8TH              0x3
#define CHP5_8TH              0x4
#define CHP6_8TH              0x5
#define CHP7_8TH              0x6

// TZSEL (Trip Zone Select)
//==========================
// CBCn and OSHTn bits
#define TZ_DISABLE            0x0
#define TZ_ENABLE             0x1

// TZCTL (Trip Zone Control)
//==========================
// TZA and TZB bits
#define TZ_HIZ                0x0
#define TZ_FORCE_HI           0x1
#define TZ_FORCE_LO           0x2
#define TZ_NO_CHANGE          0x3

// TZDCSEL (Trip Zone Digital Compare)
//==========================
// DCAEVT1, DCAEVT2, DCBEVT1, DCBEVT2 bits
#define TZ_EVT_DISABLE        0x0
#define TZ_DCAH_LOW           0x1
#define TZ_DCAH_HI            0x2
#define TZ_DCAL_LOW           0x3
#define TZ_DCAL_HI            0x4
#define TZ_DCAL_HI_DCAH_LOW   0x5

#define TZ_DCBH_LOW           0x1
#define TZ_DCBH_HI            0x2
#define TZ_DCBL_LOW           0x3
#define TZ_DCBL_HI            0x4
#define TZ_DCBL_HI_DCBH_LOW   0x5

#ifdef ADD_BY_SEAN
#define	TZ_INT_DISABLE		0x0
#define	TZ_INT_ENABLE		0x1
#endif
// ETSEL (Event Trigger Select)
//=============================
#define ET_DCAEVT1SOC         0x0
#define ET_CTR_ZERO           0x1
#define ET_CTR_PRD            0x2
#define ET_CTR_PRDZERO        0x3
#define ET_CTRU_CMPA          0x4
#define ET_CTRD_CMPA          0x5
#define ET_CTRU_CMPB          0x6
#define ET_CTRD_CMPB          0x7
#ifdef ADD_BY_SEAN
#define	ET_DISABLE		0x0
#define	ET_ENABLE		0x1
#endif

// ETPS (Event Trigger Pre-scale)
//===============================
// INTPRD, SOCAPRD, SOCBPRD bits
#define ET_DISABLE            0x0
#define ET_1ST                0x1
#define ET_2ND                0x2
#define ET_3RD                0x3

//--------------------------------
// HRPWM (High Resolution PWM)
//================================
// HRCNFG
#define HR_DISABLE            0x0
#define HR_REP                0x1
#define HR_FEP                0x2
#define HR_BEP                0x3

#define HR_CMP                0x0
#define HR_PHS                0x1

#define HR_CTR_ZERO           0x0
#define HR_CTR_PRD            0x1
#define HR_CTR_ZERO_PRD       0x2

#define HR_NORM_B             0x0
#define HR_INVERT_B           0x1
//--------------------------------
// DC (Digital Compare)
//================================
// DCTRIPSEL
#define DC_TZ1                0x0
#define DC_TZ2                0x1
#define DC_TZ3                0x2
#define DC_COMP1OUT           0x8
#define DC_COMP2OUT           0x9
#define DC_COMP3OUT           0xA
// DCFCTL
#define DC_SRC_DCAEVT1        0x0
#define DC_SRC_DCAEVT2        0x1
#define DC_SRC_DCBEVT1        0x2
#define DC_SRC_DCBEVT2        0x3

#define DC_PULSESEL_PRD       0x0
#define DC_PULSESEL_ZERO      0x1

#define DC_BLANK_DISABLE      0x0
#define DC_BLANK_ENABLE       0x1

#define DC_BLANK_NOTINV       0x0
#define DC_BLANK_INV          0x1
//DCACTL/DCBCTL
#define DC_EVT1               0x0
#define DC_EVT2               0x0
#define DC_EVT_FLT            0x1
#define DC_EVT_SYNC           0x0
#define DC_EVT_ASYNC          0x1
#define DC_SOC_DISABLE        0x0
#define DC_SOC_ENABLE         0x1


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2802x_EPWM_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
