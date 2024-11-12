/*
 * SCG.c
 *
 *  Created on: Oct 31, 2024
 *      Author: adm
 */

#include "CLOCK.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */

typedef enum
{
	SCG_MODE_NORMAL_RUN					= 0U,
	SCG_MODE_VLPOWER_RUN				= 2U,
	SCG_MODE_HSPEED_RUN					= 3U
}SCG_ModeType_e;

typedef enum
{
	SCG_MODE_VALUE_SLOW_RUN 			= 0x03000001U,
	SCG_MODE_VALUE_NORMAL_RUN  			= 0x06010012U,
	SCG_MODE_VALUE_HIGHSPEED_RUN		= 0x06000013U,
	SCG_MODE_VALUE_HIGHSPEED80_RUN		= 0x06010012U,
	SCG_MODE_VALUE_VLOWPOWER_RUN		= 0x06010003U
}SCG_ModeValueType_e;

#define SCG_GET_SYS_FREQ(RegisterValue) \
	((RegisterValue == SCG_MODE_VALUE_SLOW_RUN)      	 ? SCG_SYS_FREQ_SLOWRUN 	: \
	 (RegisterValue == SCG_MODE_VALUE_NORMAL_RUN)    	 ? SCG_SYS_FREQ_NORMALRUN 	: \
	 (RegisterValue == SCG_MODE_VALUE_HIGHSPEED_RUN)  	 ? SCG_SYS_FREQ_HSRUN 		: \
	 (RegisterValue == SCG_MODE_VALUE_HIGHSPEED80_RUN)   ? SCG_SYS_FREQ_HSRUN80 	: \
	 (RegisterValue == SCG_MODE_VALUE_VLOWPOWER_RUN)     ? SCG_SYS_FREQ_VLPRUN 		: 0)

SCG_SysFreqType_e SCG_GetSysFreq(void)
{
	SCG_SysFreqType_e RetVal				= SCG_SYS_FREQ_SLOWRUN;
	SCG_ModeType_e RunMode 					= SCG_MODE_NORMAL_RUN;
	volatile uint32_t *RunModeRegister;

	RunMode = (IP_SMC->PMCTRL >> SMC_PMCTRL_RUNM_SHIFT) & SMC_PMCTRL_RUNM_MASK;

	if(RunMode == SCG_MODE_NORMAL_RUN)
	{
		RunModeRegister = &(IP_SCG->RCCR);
	}
	else if(RunMode == SCG_MODE_VLPOWER_RUN)
	{
		RunModeRegister = &(IP_SCG->VCCR);
	}
	else
	{
		RunModeRegister = &(IP_SCG->HCCR);
	}

	RetVal = SCG_GET_SYS_FREQ(*RunModeRegister);

	return RetVal;
}
