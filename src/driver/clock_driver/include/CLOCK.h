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

typedef enum
{
	CLOCK_NOSRC_CLK			= 0U,
	CLOCK_SOSCDIV2_CLK		= 1U,
	CLOCK_SIRCDIV2_CLK		= 2U,
	CLOCK_FIRCDIV2_CLK		= 3U,
	CLOCK_SPLLDIV2_CLK		= 6U
}Clock_PeriClockSrc_e;

typedef enum
{
	CLOCK_DIV_DISABLED		= 0U,
	CLOCK_DIV_1					,
	CLOCK_DIV_2					,
	CLOCK_DIV_4					,
	CLOCK_DIV_8					,
	CLOCK_DIV_16				,
	CLOCK_DIV_32				,
	CLOCK_DIV_64
}Clock_ClkDiv_e;

typedef struct
{
	SCG_SCSType_e 		ScsValue;
	SCG_DIVCOREType_e	DivCoreValue;
	SCG_DIVBUSType_e	DivBusValue;
	SCG_DIVSLOWType_e	DivSlowValue;
}SCG_ModeElementType;

/**
 * @brief Control peripheral clock of a specific module
 *
 * @param PCCIndex: Index of the module to control the clock
 * @param ClkSrc: Clock source for the module
 * @param DivVal: Divider value for the module's clock
 * @param EnOrDis: Enable or disable the peripheral clock
 */
void PCC_PeriClockControl(uint8_t PCCIndex, Clock_PeriClockSrc_e ClkSrc, Clock_ClkDiv_e DivVal, uint8_t EnOrDis);

/**
 * @brief Get the current system frequency
 *
 * @return System frequency
 */
SCG_SysFreqType_e SCG_GetSysFreq(void);

#endif /* INCLUDE_CLOCK_H_ */