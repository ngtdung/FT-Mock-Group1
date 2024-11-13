/*
 * Clock.h
 *
 *  Created on: Apr 15, 2024
 *      Author: BienTD
 */
#ifndef _CLOCK_H_
#define _CLOCK_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "S32K144.h"
/*******************************************************************************
* Definitions
*******************************************************************************/

/* Enum stores opitonal clock sources */
typedef enum {
    SCG_SCS_SOSC_CLK = 1U,
    SCG_SCS_SIRC_CLK,
    SCG_SCS_FIRC_CLK,
    SCG_SCS_SPLL_CLK = 6U
} SCG_RCCR_ClockSourceType;

/* Enum stores the core clock divider options */
typedef enum {
    SCG_RCCR_DIVCORE_DIV_1,
    SCG_RCCR_DIVCORE_DIV_2,
    SCG_RCCR_DIVCORE_DIV_3,
    SCG_RCCR_DIVCORE_DIV_4,
    SCG_RCCR_DIVCORE_DIV_5,
    SCG_RCCR_DIVCORE_DIV_6,
    SCG_RCCR_DIVCORE_DIV_7,
    SCG_RCCR_DIVCORE_DIV_8,
    SCG_RCCR_DIVCORE_DIV_9,
    SCG_RCCR_DIVCORE_DIV_10,
    SCG_RCCR_DIVCORE_DIV_11,
    SCG_RCCR_DIVCORE_DIV_12,
    SCG_RCCR_DIVCORE_DIV_13,
    SCG_RCCR_DIVCORE_DIV_14,
    SCG_RCCR_DIVCORE_DIV_15,
    SCG_RCCR_DIVCORE_DIV_16
} SCG_RCCR_DivCoreClockType;

/* Enum stores the bus clock divider options */
typedef enum {
    SCG_RCCR_DIVBUS_DIV_1,
    SCG_RCCR_DIVBUS_DIV_2,
    SCG_RCCR_DIVBUS_DIV_3,
    SCG_RCCR_DIVBUS_DIV_4,
    SCG_RCCR_DIVBUS_DIV_5,
    SCG_RCCR_DIVBUS_DIV_6,
    SCG_RCCR_DIVBUS_DIV_7,
    SCG_RCCR_DIVBUS_DIV_8,
    SCG_RCCR_DIVBUS_DIV_9,
    SCG_RCCR_DIVBUS_DIV_10,
    SCG_RCCR_DIVBUS_DIV_11,
    SCG_RCCR_DIVBUS_DIV_12,
    SCG_RCCR_DIVBUS_DIV_13,
    SCG_RCCR_DIVBUS_DIV_14,
    SCG_RCCR_DIVBUS_DIV_15,
    SCG_RCCR_DIVBUS_DIV_16
} SCG_RCCR_DivBusClockType;

/* Struct stores the clock configurations required by the user */
typedef struct {
    SCG_RCCR_ClockSourceType clockSource;
    SCG_RCCR_DivCoreClockType divcore;
    SCG_RCCR_DivBusClockType divbus;
} SystemClockConfigType;

typedef enum {
    PCS_SOSCDIV2_CLK = 1U,
    PCS_SIRCDIV2_CLK,
    PCS_FIRCDIV2_CLK,
    PCS_SPLLDIV2_CLK = 6U
} PCC_PCS_ClockSourceType;

typedef enum {
    SCG_xDIV2_DIV_1 = 1U,
    SCG_xDIV2_DIV_2,
    SCG_xDIV2_DIV_4,
    SCG_xDIV2_DIV_8,
    SCG_xDIV2_DIV_16,
    SCG_xDIV2_DIV_32,
    SCG_xDIV2_DIV_64
} SCG_ClockDIV2Type;

typedef struct {
    PCC_PCS_ClockSourceType clockSource;
    SCG_ClockDIV2Type clockDIV2;
} AsynClockConfigType;

/*******************************************************************************
* Api
*******************************************************************************/

/**
  * @brief  This function allows clocking for peripheral
  * @param  uint8_t Periperal < index of the peripheral in the PCC register >
  * @retval None
  */
void DRV_CLOCK_Enable(uint8_t Periperal);

/**
  * @brief  This function allows configuring the system clock to the desired frequency
  * @param  SystemClockConfigType * UserConfig < User configuration options >
  * @retval None
  */
void DRV_CLOCK_ConfigBusClock(const SystemClockConfigType * UserConfig);

/**
  * @brief  This function allows configuring an asynchronous clock for peripheral functional
  * @param  uint8_t Periperal     < index of the peripheral in the PCC register >
  * @param  AsynClockConfigType * UserConfig < User configuration options >
  * @retval None
  */
void DRV_CLOCK_ConfigAsynClock(uint8_t Periperal, const AsynClockConfigType * UserConfig);

/**
  * @brief  This function allows disable clock for peripheral to save power
  * @param  uint8_t Periperal < index of the peripheral in the PCC register >
  * @retval None
  */
void DRV_CLOCK_Disable(uint8_t Periperal);

#endif /* _CLOCK_H_ */

/*******************************************************************************
* end of file
*******************************************************************************/

