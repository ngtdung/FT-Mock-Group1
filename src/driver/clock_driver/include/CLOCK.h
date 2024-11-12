/*
 * SCG.h
 *
 *  Created on: Oct 31, 2024
 *      Author: adm
 */

#ifndef INCLUDE_CLOCK_H_
#define INCLUDE_CLOCK_H_

#include "S32K144.h"

/* ----------------------------------------------------------------------------
   -- Definitions
   ---------------------------------------------------------------------------- */
typedef enum
{
	SCG_SCS_SOSC				= 1U,
	SCG_SCS_SIRC				= 2U,
	SCG_SCS_FIRC				= 3U,
	SCG_SCS_SPLL				= 6U
}SCG_SCSType_e;

typedef enum
{
	SCG_DIVCORE_1				= 0U,
	SCG_DIVCORE_2,
	SCG_DIVCORE_3,
	SCG_DIVCORE_4,
	SCG_DIVCORE_5,
	SCG_DIVCORE_6,
	SCG_DIVCORE_7,
	SCG_DIVCORE_8,
	SCG_DIVCORE_9,
	SCG_DIVCORE_10,
	SCG_DIVCORE_11,
	SCG_DIVCORE_12,
	SCG_DIVCORE_13,
	SCG_DIVCORE_14,
	SCG_DIVCORE_15,
	SCG_DIVCORE_16
}SCG_DIVCOREType_e;

typedef enum
{
	SCG_DIVBUS_1				= 0U,
	SCG_DIVBUS_2,
	SCG_DIVBUS_3,
	SCG_DIVBUS_4,
	SCG_DIVBUS_5,
	SCG_DIVBUS_6,
	SCG_DIVBUS_7,
	SCG_DIVBUS_8,
	SCG_DIVBUS_9,
	SCG_DIVBUS_10,
	SCG_DIVBUS_11,
	SCG_DIVBUS_12,
	SCG_DIVBUS_13,
	SCG_DIVBUS_14,
	SCG_DIVBUS_15,
	SCG_DIVBUS_16
}SCG_DIVBUSType_e;

typedef enum
{
	SCG_DIVSLOW_1				= 0U,
	SCG_DIVSLOW_2,
	SCG_DIVSLOW_3,
	SCG_DIVSLOW_4,
	SCG_DIVSLOW_5,
	SCG_DIVSLOW_6,
	SCG_DIVSLOW_7,
	SCG_DIVSLOW_8,
}SCG_DIVSLOWType_e;

typedef enum
{
	SCG_SYS_FREQ_SLOWRUN	= 48000000U,
	SCG_SYS_FREQ_NORMALRUN	= 80000000U,
	SCG_SYS_FREQ_HSRUN		= 112000000U,
	SCG_SYS_FREQ_HSRUN80	= 80000000U,
	SCG_SYS_FREQ_VLPRUN		= 4000000U
}SCG_SysFreqType_e;

typedef struct
{
	SCG_SCSType_e 		ScsValue;
	SCG_DIVCOREType_e	DivCoreValue;
	SCG_DIVBUSType_e	DivBusValue;
	SCG_DIVSLOWType_e	DivSlowValue;
}SCG_ModeElementType;

static inline void PCC_PeriClockControl(uint8_t PCCIndex, uint8_t EnOrDis)
{
	if(EnOrDis == ENABLE)
	{
		/* Enables corresponding peripheral's clock */
		IP_PCC->PCCn[PCCIndex] |= PCC_PCCn_CGC_MASK;
	}
	else
	{
		/* Disables corresponding peripheral's clock */
		IP_PCC->PCCn[PCCIndex] &= ~PCC_PCCn_CGC_MASK;
	}
}

SCG_SysFreqType_e SCG_GetSysFreq(void);

#endif /* INCLUDE_CLOCK_H_ */
