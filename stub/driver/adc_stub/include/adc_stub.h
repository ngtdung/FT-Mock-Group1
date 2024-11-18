/*
** ###################################################################
**     Processor:           S32K144
**     Reference manual:    S32K1XX RM Rev.13
**     Version:             rev. 4.4, 2021-04-26
**     Build:               b210426
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2015-04-09) - Iulian Talpiga
**         Initial version.
**     - rev. 1.1 (2015-05-19) - Bogdan Nitu
**         Updated interrupts table
**         Removed SIM_CHIPCTL_DAC2CMP
**         Compacted PORT_PCR registers
**         Compacted PCC registers
**     - rev. 1.2 (2015-06-02) - Bogdan Nitu
**         Added 'U' suffix to all integer constants
**         Use "" instead of <> for Platform type inclusion
**         CNT register from WDOG module is RW
**     - rev. 1.3 (2015-08-05) - Iulian Talpiga
**         Synchronized with latest RDP
**         Removed OSC32 module
**         Removed reserved registers
**         Incorporated bit band acces macros
**         Switched to standard C99 data types
**         Added 'u' to constants
**         Added size defines for register arrays
**         Define peripheral instance count
**     - rev. 1.4 (2015-08-10) - Iulian Talpiga
**         Compacted TRGMUX registers
**         Defined array index offsets for PCC and TRGMUX
**         Added FPU registers
**         Group FTM channel registers
**         Added interrupt information to peripherals
**         Renamed CAN interrupts according  to the reference manual
**         Added author information to revisions
**     - rev. 1.5 (2015-09-16) - Iulian Talpiga
**         Renamed NVIC and SCB to avoid conflict
**         Compacted CAN Wake-up Message buffers
**         Added CAN embedded RAM
**         Updated interrupts: LPIT, FTFE, LPUART,ACMP
**         Corrected ADC_SC1_ADCH_WIDTH
**         Compacted PDB registers
**         Corrected CAN, FTM, and PDB count defines
**         Guarding register acces macro against redefintion
**     - rev. 1.6 (2015-09-29) - Iulian Talpiga
**         Added WATER and FIFO registers to LPUART.
**     - rev. 1.7 (2015-10-21) - Iulian Talpiga
**         Updated ADC, AIPS, CMP, LMEM, LPTMR, PMC, PORT, RCM, RTC, SCG, SIM
**         Compacted MPU and LPIT
**         Added FSL_SysTick
**         Updated doxygen documentation grouping
**         Updated interrupts: RCM
**     - rev. 1.8 (2016-01-06) - Iulian Talpiga
**         Updated DMA, compacted TCD registers
**         Updated SCG, removed SC2P - SC16P
**         Added 8 and 16 bit access to DATA register, CRC module
**     - rev. 1.9 (2016-02-15) - Iulian Talpiga
**         Updated CRC, renamed DATA union
**         Updated PMC, added CLKBIASDIS bitfield
**         Added FSL_NVIC registers to SVD
**     - rev. 2.0 (2016-04-07) - Iulian Talpiga
**         Updated support for Rev2.0 silicon (0N47T)
**         Updated ADC, AIPS, DMA, FlexIO, FTM, GPIO, LPI2C, LPIT, LPSPI, MCM, MPU, MSCM, PMC, RTC, RCM, PCC, RTC, SCG, SIM, TRGMUX and WDOG  module
**         Updated interrupts
**         Added EIM and ERM modules
**         Added EIM and ERM modules
**     - rev. 2.1 (2016-06-10) - Iulian Talpiga
**         Updated to latest RM
**         Minor changes to: CAN, EIM, LPI2C, MPU, PCC, PMC, RTC, SIM and TRGMUX
**     - rev. 2.2 (2016-08-02) - Iulian Talpiga
**         Updated to latest RM
**         Minor changes to: ADC, CAN, CRC, FTFC, LMEM, LPI2C, MCM, MSCM, PCC, RTC, SIM
**         Added CSE_PRAM
**     - rev. 2.3 (2016-09-09) - Iulian Talpiga
**         Updated to latest RM
**         Minor changes to: PCC, FSL_NVIC and FTM
**     - rev. 2.4 (2016-09-28) - Iulian Talpiga
**         Fix RAMn array size in FlexCAN
**         Fix FCSESTAT bit order
**         Added CP0CFG0, CP0CFG1,CP0CFG2 and CP0CFG3 in MSCM
**         Fixed STIR register in FSL_NVIC
**         Fixed SHPR3 and ACTLR registers in FSL_SCB
**     - rev. 2.5 (2016-11-25) - Iulian Talpiga
**         Fix FRAC bit-field in PCC module
**         Removed BITBAND_ACCESS macros
**         Added MISRA declarations
**         Updated copyright
**         Changed prefix of NVIC, SCB and SysTick to S32_
**     - rev. 2.6 (2017-01-09) - Iulian Talpiga
**         Fix interrupts for CAN, LPUART, FTFC
**     - rev. 2.7 (2017-02-22) - Iulian Talpiga
**         Update header as per rev S32K14XRM Rev. 2, 02/2017
**         Updated modules AIPS, CAN, LPI2C, LPSPI, MCM, MPU, SCG and SIM
**     - rev. 2.8 (2017-03-27) - Iulian Talpiga
**         Synchronized PCC_FlexIO on S32K Family
**     - rev. 3.0 (2017-08-04) - Mihai Volmer
**         Update header as per rev S32K1XXRM Rev. 4, 06/2017
**         Updated modules CAN, MCM and PORTn
**     - rev. 3.1 (2017-09-25) - Andrei Bolojan
**         Update NVIC Size of Registers Arrays
**     - rev. 4.0 (2018-02-28) - Mihai Volmer
**         Updated header as per rev S32K1XXRM Rev. 6, 12/2017
**         Updated modules ERM, I2C, MSCM and SIM
**     - rev. 4.1 (2018-07-19) - Dan Nastasa
**         Updated the header based on S32K1XXRM Rev. 8, 06/2018.
**     - rev. 4.2 (2019-02-19) - Ionut Pavel
**         Updated the header based on S32K1XXRM Rev. 9, 09/2018.
**     - rev. 4.3 (2020-05-14) - Van Nguyen Nam
**         Updated the header based on S32K1XXRM Rev. 12.1, 02/2020.
**     - rev. 4.4 (2021-04-26) - Minh Quan Trinh
**         Updated the header based on S32K1XXRM Rev. 13, 04/2020.
**         Modified AIPS Register Layout
**         Modified LPI2C_MTDR, LPI2C_STDR and LPIT_CLRTEN registers to Write-Only
**         Modified SIM_FCFG1 registers to Read-Only
**         Added RCM_PARAM_ECMU_LOC bit field
**
** ###################################################################
*/

/*!
 * @file S32K144.h
 * @version 4.4
 * @date 2021-04-26
 * @brief Peripheral Access Layer for S32K144
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(S32K144_H_)  /* Check if memory map has not been already included */
#define S32K144_H_
#define MCU_S32K144

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error S32K144 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0400u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0004u

/* ----------------------------------------------------------------------------
   -- Generic macros
   ---------------------------------------------------------------------------- */

/* IO definitions (access restrictions to peripheral registers) */
/**
*   IO Type Qualifiers are used
*   \li to specify the access to peripheral variables.
*   \li for automatic generation of peripheral register debug information.
*/
#ifndef __IO
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
#endif


/**
* @brief 32 bits memory read macro.
*/
#if !defined(REG_READ32)
  #define REG_READ32(address)               (*(volatile uint32_t*)(address))
#endif

/**
* @brief 32 bits memory write macro.
*/
#if !defined(REG_WRITE32)
  #define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/**
* @brief 32 bits bits setting macro.
*/
#if !defined(REG_BIT_SET32)
  #define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address))|= (uint32_t)(mask))
#endif

/**
* @brief 32 bits bits clearing macro.
*/
#if !defined(REG_BIT_CLEAR32)
  #define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address))&= ((uint32_t)~((uint32_t)(mask))))
#endif

/**
* @brief 32 bit clear bits and set with new value
* @note It is user's responsability to make sure that value has only "mask" bits set - (value&~mask)==0
*/
#if !defined(REG_RMW32)
  #define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32_t)~((uint32_t)(mask))))| ((uint32_t)(value)))))
#endif


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer for S32K144
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer_S32K144 Device Peripheral Access Layer for S32K144
 * @{
 */

/* @brief This module covers memory mapped registers available on SoC */

/* ----------------------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */


/** ADC - Size of Registers Arrays */
#define ADC_SC1_COUNT                            16u
#define ADC_R_COUNT                              16u
#define ADC_CV_COUNT                             2u

/** ADC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC1[ADC_SC1_COUNT];                /**< ADC Status and Control Register 1, array offset: 0x0, array step: 0x4 */
  __IO uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x40 */
  __IO uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0x44 */
  __I  uint32_t R[ADC_R_COUNT];                    /**< ADC Data Result Registers, array offset: 0x48, array step: 0x4 */
  __IO uint32_t CV[ADC_CV_COUNT];                  /**< Compare Value Registers, array offset: 0x88, array step: 0x4 */
  __IO uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x90 */
  __IO uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x94 */
  __IO uint32_t BASE_OFS;                          /**< BASE Offset Register, offset: 0x98 */
  __IO uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x9C */
  __IO uint32_t USR_OFS;                           /**< USER Offset Correction Register, offset: 0xA0 */
  __IO uint32_t XOFS;                              /**< ADC X Offset Correction Register, offset: 0xA4 */
  __IO uint32_t YOFS;                              /**< ADC Y Offset Correction Register, offset: 0xA8 */
  __IO uint32_t G;                                 /**< ADC Gain Register, offset: 0xAC */
  __IO uint32_t UG;                                /**< ADC User Gain Register, offset: 0xB0 */
  __IO uint32_t CLPS;                              /**< ADC General Calibration Value Register S, offset: 0xB4 */
  __IO uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register 3, offset: 0xB8 */
  __IO uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register 2, offset: 0xBC */
  __IO uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register 1, offset: 0xC0 */
  __IO uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register 0, offset: 0xC4 */
  __IO uint32_t CLPX;                              /**< ADC Plus-Side General Calibration Value Register X, offset: 0xC8 */
  __IO uint32_t CLP9;                              /**< ADC Plus-Side General Calibration Value Register 9, offset: 0xCC */
  __IO uint32_t CLPS_OFS;                          /**< ADC General Calibration Offset Value Register S, offset: 0xD0 */
  __IO uint32_t CLP3_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 3, offset: 0xD4 */
  __IO uint32_t CLP2_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 2, offset: 0xD8 */
  __IO uint32_t CLP1_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 1, offset: 0xDC */
  __IO uint32_t CLP0_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 0, offset: 0xE0 */
  __IO uint32_t CLPX_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register X, offset: 0xE4 */
  __IO uint32_t CLP9_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 9, offset: 0xE8 */
} ADC_Type, *ADC_MemMapPtr;

 /** Number of instances of the ADC module. */
#define ADC_INSTANCE_COUNT                       (2u)


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
/** Peripheral ADC0 base pointer */
extern ADC_Type *ADC0;
/** Peripheral ADC1 base address */
/** Peripheral ADC1 base pointer */
extern ADC_Type *ADC1;
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE, ADC1_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0, ADC1 }
 /** Number of interrupt vector arrays for the ADC module. */
#define ADC_IRQS_ARR_COUNT                       (1u)
 /** Number of interrupt channels for the ADC module. */
#define ADC_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC0_IRQn, ADC1_IRQn }

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
#define ADC_SC1_ADCH_MASK                        0x1Fu
#define ADC_SC1_ADCH_SHIFT                       0u
#define ADC_SC1_ADCH_WIDTH                       5u
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCH_SHIFT))&ADC_SC1_ADCH_MASK)
#define ADC_SC1_AIEN_MASK                        0x40u
#define ADC_SC1_AIEN_SHIFT                       6u
#define ADC_SC1_AIEN_WIDTH                       1u
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_AIEN_SHIFT))&ADC_SC1_AIEN_MASK)
#define ADC_SC1_COCO_MASK                        0x80u
#define ADC_SC1_COCO_SHIFT                       7u
#define ADC_SC1_COCO_WIDTH                       1u
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_COCO_SHIFT))&ADC_SC1_COCO_MASK)
/* CFG1 Bit Fields */
#define ADC_CFG1_ADICLK_MASK                     0x3u
#define ADC_CFG1_ADICLK_SHIFT                    0u
#define ADC_CFG1_ADICLK_WIDTH                    2u
#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADICLK_SHIFT))&ADC_CFG1_ADICLK_MASK)
#define ADC_CFG1_MODE_MASK                       0xCu
#define ADC_CFG1_MODE_SHIFT                      2u
#define ADC_CFG1_MODE_WIDTH                      2u
#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_MODE_SHIFT))&ADC_CFG1_MODE_MASK)
#define ADC_CFG1_ADIV_MASK                       0x60u
#define ADC_CFG1_ADIV_SHIFT                      5u
#define ADC_CFG1_ADIV_WIDTH                      2u
#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ADIV_SHIFT))&ADC_CFG1_ADIV_MASK)
#define ADC_CFG1_CLRLTRG_MASK                    0x100u
#define ADC_CFG1_CLRLTRG_SHIFT                   8u
#define ADC_CFG1_CLRLTRG_WIDTH                   1u
#define ADC_CFG1_CLRLTRG(x)                      (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_CLRLTRG_SHIFT))&ADC_CFG1_CLRLTRG_MASK)
/* CFG2 Bit Fields */
#define ADC_CFG2_SMPLTS_MASK                     0xFFu
#define ADC_CFG2_SMPLTS_SHIFT                    0u
#define ADC_CFG2_SMPLTS_WIDTH                    8u
#define ADC_CFG2_SMPLTS(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_SMPLTS_SHIFT))&ADC_CFG2_SMPLTS_MASK)
/* R Bit Fields */
#define ADC_R_D_MASK                             0xFFFu
#define ADC_R_D_SHIFT                            0u
#define ADC_R_D_WIDTH                            12u
#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x))<<ADC_R_D_SHIFT))&ADC_R_D_MASK)
/* CV Bit Fields */
#define ADC_CV_CV_MASK                           0xFFFFu
#define ADC_CV_CV_SHIFT                          0u
#define ADC_CV_CV_WIDTH                          16u
#define ADC_CV_CV(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_CV_CV_SHIFT))&ADC_CV_CV_MASK)
/* SC2 Bit Fields */
#define ADC_SC2_REFSEL_MASK                      0x3u
#define ADC_SC2_REFSEL_SHIFT                     0u
#define ADC_SC2_REFSEL_WIDTH                     2u
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_REFSEL_SHIFT))&ADC_SC2_REFSEL_MASK)
#define ADC_SC2_DMAEN_MASK                       0x4u
#define ADC_SC2_DMAEN_SHIFT                      2u
#define ADC_SC2_DMAEN_WIDTH                      1u
#define ADC_SC2_DMAEN(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_DMAEN_SHIFT))&ADC_SC2_DMAEN_MASK)
#define ADC_SC2_ACREN_MASK                       0x8u
#define ADC_SC2_ACREN_SHIFT                      3u
#define ADC_SC2_ACREN_WIDTH                      1u
#define ADC_SC2_ACREN(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACREN_SHIFT))&ADC_SC2_ACREN_MASK)
#define ADC_SC2_ACFGT_MASK                       0x10u
#define ADC_SC2_ACFGT_SHIFT                      4u
#define ADC_SC2_ACFGT_WIDTH                      1u
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFGT_SHIFT))&ADC_SC2_ACFGT_MASK)
#define ADC_SC2_ACFE_MASK                        0x20u
#define ADC_SC2_ACFE_SHIFT                       5u
#define ADC_SC2_ACFE_WIDTH                       1u
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFE_SHIFT))&ADC_SC2_ACFE_MASK)
#define ADC_SC2_ADTRG_MASK                       0x40u
#define ADC_SC2_ADTRG_SHIFT                      6u
#define ADC_SC2_ADTRG_WIDTH                      1u
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADTRG_SHIFT))&ADC_SC2_ADTRG_MASK)
#define ADC_SC2_ADACT_MASK                       0x80u
#define ADC_SC2_ADACT_SHIFT                      7u
#define ADC_SC2_ADACT_WIDTH                      1u
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADACT_SHIFT))&ADC_SC2_ADACT_MASK)
#define ADC_SC2_TRGPRNUM_MASK                    0x6000u
#define ADC_SC2_TRGPRNUM_SHIFT                   13u
#define ADC_SC2_TRGPRNUM_WIDTH                   2u
#define ADC_SC2_TRGPRNUM(x)                      (((uint32_t)(((uint32_t)(x))<<ADC_SC2_TRGPRNUM_SHIFT))&ADC_SC2_TRGPRNUM_MASK)
#define ADC_SC2_TRGSTLAT_MASK                    0xF0000u
#define ADC_SC2_TRGSTLAT_SHIFT                   16u
#define ADC_SC2_TRGSTLAT_WIDTH                   4u
#define ADC_SC2_TRGSTLAT(x)                      (((uint32_t)(((uint32_t)(x))<<ADC_SC2_TRGSTLAT_SHIFT))&ADC_SC2_TRGSTLAT_MASK)
#define ADC_SC2_TRGSTERR_MASK                    0xF000000u
#define ADC_SC2_TRGSTERR_SHIFT                   24u
#define ADC_SC2_TRGSTERR_WIDTH                   4u
#define ADC_SC2_TRGSTERR(x)                      (((uint32_t)(((uint32_t)(x))<<ADC_SC2_TRGSTERR_SHIFT))&ADC_SC2_TRGSTERR_MASK)
/* SC3 Bit Fields */
#define ADC_SC3_AVGS_MASK                        0x3u
#define ADC_SC3_AVGS_SHIFT                       0u
#define ADC_SC3_AVGS_WIDTH                       2u
#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_AVGS_SHIFT))&ADC_SC3_AVGS_MASK)
#define ADC_SC3_AVGE_MASK                        0x4u
#define ADC_SC3_AVGE_SHIFT                       2u
#define ADC_SC3_AVGE_WIDTH                       1u
#define ADC_SC3_AVGE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_AVGE_SHIFT))&ADC_SC3_AVGE_MASK)
#define ADC_SC3_ADCO_MASK                        0x8u
#define ADC_SC3_ADCO_SHIFT                       3u
#define ADC_SC3_ADCO_WIDTH                       1u
#define ADC_SC3_ADCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADCO_SHIFT))&ADC_SC3_ADCO_MASK)
#define ADC_SC3_CAL_MASK                         0x80u
#define ADC_SC3_CAL_SHIFT                        7u
#define ADC_SC3_CAL_WIDTH                        1u
#define ADC_SC3_CAL(x)                           (((uint32_t)(((uint32_t)(x))<<ADC_SC3_CAL_SHIFT))&ADC_SC3_CAL_MASK)
/* BASE_OFS Bit Fields */
#define ADC_BASE_OFS_BA_OFS_MASK                 0xFFu
#define ADC_BASE_OFS_BA_OFS_SHIFT                0u
#define ADC_BASE_OFS_BA_OFS_WIDTH                8u
#define ADC_BASE_OFS_BA_OFS(x)                   (((uint32_t)(((uint32_t)(x))<<ADC_BASE_OFS_BA_OFS_SHIFT))&ADC_BASE_OFS_BA_OFS_MASK)
/* OFS Bit Fields */
#define ADC_OFS_OFS_MASK                         0xFFFFu
#define ADC_OFS_OFS_SHIFT                        0u
#define ADC_OFS_OFS_WIDTH                        16u
#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x))<<ADC_OFS_OFS_SHIFT))&ADC_OFS_OFS_MASK)
/* USR_OFS Bit Fields */
#define ADC_USR_OFS_USR_OFS_MASK                 0xFFu
#define ADC_USR_OFS_USR_OFS_SHIFT                0u
#define ADC_USR_OFS_USR_OFS_WIDTH                8u
#define ADC_USR_OFS_USR_OFS(x)                   (((uint32_t)(((uint32_t)(x))<<ADC_USR_OFS_USR_OFS_SHIFT))&ADC_USR_OFS_USR_OFS_MASK)
/* XOFS Bit Fields */
#define ADC_XOFS_XOFS_MASK                       0x3Fu
#define ADC_XOFS_XOFS_SHIFT                      0u
#define ADC_XOFS_XOFS_WIDTH                      6u
#define ADC_XOFS_XOFS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_XOFS_XOFS_SHIFT))&ADC_XOFS_XOFS_MASK)
/* YOFS Bit Fields */
#define ADC_YOFS_YOFS_MASK                       0xFFu
#define ADC_YOFS_YOFS_SHIFT                      0u
#define ADC_YOFS_YOFS_WIDTH                      8u
#define ADC_YOFS_YOFS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_YOFS_YOFS_SHIFT))&ADC_YOFS_YOFS_MASK)
/* G Bit Fields */
#define ADC_G_G_MASK                             0x7FFu
#define ADC_G_G_SHIFT                            0u
#define ADC_G_G_WIDTH                            11u
#define ADC_G_G(x)                               (((uint32_t)(((uint32_t)(x))<<ADC_G_G_SHIFT))&ADC_G_G_MASK)
/* UG Bit Fields */
#define ADC_UG_UG_MASK                           0x3FFu
#define ADC_UG_UG_SHIFT                          0u
#define ADC_UG_UG_WIDTH                          10u
#define ADC_UG_UG(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_UG_UG_SHIFT))&ADC_UG_UG_MASK)
/* CLPS Bit Fields */
#define ADC_CLPS_CLPS_MASK                       0x7Fu
#define ADC_CLPS_CLPS_SHIFT                      0u
#define ADC_CLPS_CLPS_WIDTH                      7u
#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPS_CLPS_SHIFT))&ADC_CLPS_CLPS_MASK)
/* CLP3 Bit Fields */
#define ADC_CLP3_CLP3_MASK                       0x3FFu
#define ADC_CLP3_CLP3_SHIFT                      0u
#define ADC_CLP3_CLP3_WIDTH                      10u
#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP3_CLP3_SHIFT))&ADC_CLP3_CLP3_MASK)
/* CLP2 Bit Fields */
#define ADC_CLP2_CLP2_MASK                       0x3FFu
#define ADC_CLP2_CLP2_SHIFT                      0u
#define ADC_CLP2_CLP2_WIDTH                      10u
#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP2_CLP2_SHIFT))&ADC_CLP2_CLP2_MASK)
/* CLP1 Bit Fields */
#define ADC_CLP1_CLP1_MASK                       0x1FFu
#define ADC_CLP1_CLP1_SHIFT                      0u
#define ADC_CLP1_CLP1_WIDTH                      9u
#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP1_CLP1_SHIFT))&ADC_CLP1_CLP1_MASK)
/* CLP0 Bit Fields */
#define ADC_CLP0_CLP0_MASK                       0xFFu
#define ADC_CLP0_CLP0_SHIFT                      0u
#define ADC_CLP0_CLP0_WIDTH                      8u
#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP0_CLP0_SHIFT))&ADC_CLP0_CLP0_MASK)
/* CLPX Bit Fields */
#define ADC_CLPX_CLPX_MASK                       0x7Fu
#define ADC_CLPX_CLPX_SHIFT                      0u
#define ADC_CLPX_CLPX_WIDTH                      7u
#define ADC_CLPX_CLPX(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLPX_CLPX_SHIFT))&ADC_CLPX_CLPX_MASK)
/* CLP9 Bit Fields */
#define ADC_CLP9_CLP9_MASK                       0x7Fu
#define ADC_CLP9_CLP9_SHIFT                      0u
#define ADC_CLP9_CLP9_WIDTH                      7u
#define ADC_CLP9_CLP9(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_CLP9_CLP9_SHIFT))&ADC_CLP9_CLP9_MASK)
/* CLPS_OFS Bit Fields */
#define ADC_CLPS_OFS_CLPS_OFS_MASK               0xFu
#define ADC_CLPS_OFS_CLPS_OFS_SHIFT              0u
#define ADC_CLPS_OFS_CLPS_OFS_WIDTH              4u
#define ADC_CLPS_OFS_CLPS_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLPS_OFS_CLPS_OFS_SHIFT))&ADC_CLPS_OFS_CLPS_OFS_MASK)
/* CLP3_OFS Bit Fields */
#define ADC_CLP3_OFS_CLP3_OFS_MASK               0xFu
#define ADC_CLP3_OFS_CLP3_OFS_SHIFT              0u
#define ADC_CLP3_OFS_CLP3_OFS_WIDTH              4u
#define ADC_CLP3_OFS_CLP3_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLP3_OFS_CLP3_OFS_SHIFT))&ADC_CLP3_OFS_CLP3_OFS_MASK)
/* CLP2_OFS Bit Fields */
#define ADC_CLP2_OFS_CLP2_OFS_MASK               0xFu
#define ADC_CLP2_OFS_CLP2_OFS_SHIFT              0u
#define ADC_CLP2_OFS_CLP2_OFS_WIDTH              4u
#define ADC_CLP2_OFS_CLP2_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLP2_OFS_CLP2_OFS_SHIFT))&ADC_CLP2_OFS_CLP2_OFS_MASK)
/* CLP1_OFS Bit Fields */
#define ADC_CLP1_OFS_CLP1_OFS_MASK               0xFu
#define ADC_CLP1_OFS_CLP1_OFS_SHIFT              0u
#define ADC_CLP1_OFS_CLP1_OFS_WIDTH              4u
#define ADC_CLP1_OFS_CLP1_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLP1_OFS_CLP1_OFS_SHIFT))&ADC_CLP1_OFS_CLP1_OFS_MASK)
/* CLP0_OFS Bit Fields */
#define ADC_CLP0_OFS_CLP0_OFS_MASK               0xFu
#define ADC_CLP0_OFS_CLP0_OFS_SHIFT              0u
#define ADC_CLP0_OFS_CLP0_OFS_WIDTH              4u
#define ADC_CLP0_OFS_CLP0_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLP0_OFS_CLP0_OFS_SHIFT))&ADC_CLP0_OFS_CLP0_OFS_MASK)
/* CLPX_OFS Bit Fields */
#define ADC_CLPX_OFS_CLPX_OFS_MASK               0xFFFu
#define ADC_CLPX_OFS_CLPX_OFS_SHIFT              0u
#define ADC_CLPX_OFS_CLPX_OFS_WIDTH              12u
#define ADC_CLPX_OFS_CLPX_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLPX_OFS_CLPX_OFS_SHIFT))&ADC_CLPX_OFS_CLPX_OFS_MASK)
/* CLP9_OFS Bit Fields */
#define ADC_CLP9_OFS_CLP9_OFS_MASK               0xFFFu
#define ADC_CLP9_OFS_CLP9_OFS_SHIFT              0u
#define ADC_CLP9_OFS_CLP9_OFS_WIDTH              12u
#define ADC_CLP9_OFS_CLP9_OFS(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CLP9_OFS_CLP9_OFS_SHIFT))&ADC_CLP9_OFS_CLP9_OFS_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */



/* ----------------------------------------------------------------------------
   -- PCC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PCC_Peripheral_Access_Layer PCC Peripheral Access Layer
 * @{
 */


/** PCC - Size of Registers Arrays */
#define PCC_PCCn_COUNT                           116u

/** PCC - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCCn[PCC_PCCn_COUNT];              /**< PCC Reserved Register 0..PCC CMP0 Register, array offset: 0x0, array step: 0x4 */
} PCC_Type, *PCC_MemMapPtr;

 /** Number of instances of the PCC module. */
#define PCC_INSTANCE_COUNT                       (1u)


/* PCC - Peripheral instance base addresses */
/** Peripheral PCC base address */
/** Peripheral PCC base pointer */
extern PCC_Type *PCC;
/** Array initializer of PCC peripheral base addresses */
#define PCC_BASE_ADDRS                           { PCC_BASE }
/** Array initializer of PCC peripheral base pointers */
#define PCC_BASE_PTRS                            { PCC }

/* PCC index offsets */
#define PCC_FTFC_INDEX                           32
#define PCC_DMAMUX_INDEX                         33
#define PCC_FlexCAN0_INDEX                       36
#define PCC_FlexCAN1_INDEX                       37
#define PCC_FTM3_INDEX                           38
#define PCC_ADC1_INDEX                           39
#define PCC_FlexCAN2_INDEX                       43
#define PCC_LPSPI0_INDEX                         44
#define PCC_LPSPI1_INDEX                         45
#define PCC_LPSPI2_INDEX                         46
#define PCC_PDB1_INDEX                           49
#define PCC_CRC_INDEX                            50
#define PCC_PDB0_INDEX                           54
#define PCC_LPIT_INDEX                           55
#define PCC_FTM0_INDEX                           56
#define PCC_FTM1_INDEX                           57
#define PCC_FTM2_INDEX                           58
#define PCC_ADC0_INDEX                           59
#define PCC_RTC_INDEX                            61
#define PCC_LPTMR0_INDEX                         64
#define PCC_PORTA_INDEX                          73
#define PCC_PORTB_INDEX                          74
#define PCC_PORTC_INDEX                          75
#define PCC_PORTD_INDEX                          76
#define PCC_PORTE_INDEX                          77
#define PCC_FlexIO_INDEX                         90
#define PCC_EWM_INDEX                            97
#define PCC_LPI2C0_INDEX                         102
#define PCC_LPUART0_INDEX                        106
#define PCC_LPUART1_INDEX                        107
#define PCC_LPUART2_INDEX                        108
#define PCC_CMP0_INDEX                           115

/* ----------------------------------------------------------------------------
   -- PCC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PCC_Register_Masks PCC Register Masks
 * @{
 */

/* PCCn Bit Fields */
#define PCC_PCCn_PCD_MASK                        0x7u
#define PCC_PCCn_PCD_SHIFT                       0u
#define PCC_PCCn_PCD_WIDTH                       3u
#define PCC_PCCn_PCD(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_PCCn_PCD_SHIFT))&PCC_PCCn_PCD_MASK)
#define PCC_PCCn_FRAC_MASK                       0x8u
#define PCC_PCCn_FRAC_SHIFT                      3u
#define PCC_PCCn_FRAC_WIDTH                      1u
#define PCC_PCCn_FRAC(x)                         (((uint32_t)(((uint32_t)(x))<<PCC_PCCn_FRAC_SHIFT))&PCC_PCCn_FRAC_MASK)
#define PCC_PCCn_PCS_MASK                        0x7000000u
#define PCC_PCCn_PCS_SHIFT                       24u
#define PCC_PCCn_PCS_WIDTH                       3u
#define PCC_PCCn_PCS(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_PCCn_PCS_SHIFT))&PCC_PCCn_PCS_MASK)
#define PCC_PCCn_CGC_MASK                        0x40000000u
#define PCC_PCCn_CGC_SHIFT                       30u
#define PCC_PCCn_CGC_WIDTH                       1u
#define PCC_PCCn_CGC(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_PCCn_CGC_SHIFT))&PCC_PCCn_CGC_MASK)
#define PCC_PCCn_PR_MASK                         0x80000000u
#define PCC_PCCn_PR_SHIFT                        31u
#define PCC_PCCn_PR_WIDTH                        1u
#define PCC_PCCn_PR(x)                           (((uint32_t)(((uint32_t)(x))<<PCC_PCCn_PR_SHIFT))&PCC_PCCn_PR_MASK)

/*!
 * @}
 */ /* end of group PCC_Register_Masks */


/*!
 * @}
 */ /* end of group PCC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PDB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Peripheral_Access_Layer PDB Peripheral Access Layer
 * @{
 */


/** PDB - Size of Registers Arrays */
#define PDB_CH_COUNT                             2u
#define PDB_DLY_COUNT                            8u
#define PDB_POnDLY_COUNT                         1u

/** PDB - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status and Control register, offset: 0x0 */
  __IO uint32_t MOD;                               /**< Modulus register, offset: 0x4 */
  __I  uint32_t CNT;                               /**< Counter register, offset: 0x8 */
  __IO uint32_t IDLY;                              /**< Interrupt Delay register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x28 */
    __IO uint32_t C1;                                /**< Channel n Control register 1, array offset: 0x10, array step: 0x28 */
    __IO uint32_t S;                                 /**< Channel n Status register, array offset: 0x14, array step: 0x28 */
    __IO uint32_t DLY[PDB_DLY_COUNT];                /**< Channel n Delay 0 register..Channel n Delay 7 register, array offset: 0x18, array step: index*0x28, index2*0x4 */
  } CH[PDB_CH_COUNT];
       uint8_t RESERVED_0[304];
  __IO uint32_t POEN;                              /**< Pulse-Out n Enable register, offset: 0x190 */
  union {                                          /* offset: 0x194, array step: 0x4 */
    __IO uint32_t PODLY;                             /**< Pulse-Out n Delay register, array offset: 0x194, array step: 0x4 */
    struct {                                         /* offset: 0x194, array step: 0x4 */
      __IO uint16_t DLY2;                              /**< PDB1_DLY2 register...PDB0_DLY2 register., array offset: 0x194, array step: 0x4 */
      __IO uint16_t DLY1;                              /**< PDB1_DLY1 register...PDB0_DLY1 register., array offset: 0x196, array step: 0x4 */
    } ACCESS16BIT;
  } POnDLY[PDB_POnDLY_COUNT];
} PDB_Type, *PDB_MemMapPtr;

 /** Number of instances of the PDB module. */
#define PDB_INSTANCE_COUNT                       (2u)


/* PDB - Peripheral instance base addresses */
/** Peripheral PDB0 base address */
/** Peripheral PDB0 base pointer */
extern PDB_Type *PDB0;
/** Peripheral PDB1 base address */
/** Peripheral PDB1 base pointer */
extern PDB_Type *PDB1;
/** Array initializer of PDB peripheral base addresses */
#define PDB_BASE_ADDRS                           { PDB0_BASE, PDB1_BASE }
/** Array initializer of PDB peripheral base pointers */
#define PDB_BASE_PTRS                            { PDB0, PDB1 }
 /** Number of interrupt vector arrays for the PDB module. */
#define PDB_IRQS_ARR_COUNT                       (1u)
 /** Number of interrupt channels for the PDB module. */
#define PDB_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the PDB peripheral type */
#define PDB_IRQS                                 { PDB0_IRQn, PDB1_IRQn }

/* ----------------------------------------------------------------------------
   -- PDB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Masks PDB Register Masks
 * @{
 */

/* SC Bit Fields */
#define PDB_SC_LDOK_MASK                         0x1u
#define PDB_SC_LDOK_SHIFT                        0u
#define PDB_SC_LDOK_WIDTH                        1u
#define PDB_SC_LDOK(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_LDOK_SHIFT))&PDB_SC_LDOK_MASK)
#define PDB_SC_CONT_MASK                         0x2u
#define PDB_SC_CONT_SHIFT                        1u
#define PDB_SC_CONT_WIDTH                        1u
#define PDB_SC_CONT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_CONT_SHIFT))&PDB_SC_CONT_MASK)
#define PDB_SC_MULT_MASK                         0xCu
#define PDB_SC_MULT_SHIFT                        2u
#define PDB_SC_MULT_WIDTH                        2u
#define PDB_SC_MULT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_SC_MULT_SHIFT))&PDB_SC_MULT_MASK)
#define PDB_SC_PDBIE_MASK                        0x20u
#define PDB_SC_PDBIE_SHIFT                       5u
#define PDB_SC_PDBIE_WIDTH                       1u
#define PDB_SC_PDBIE(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBIE_SHIFT))&PDB_SC_PDBIE_MASK)
#define PDB_SC_PDBIF_MASK                        0x40u
#define PDB_SC_PDBIF_SHIFT                       6u
#define PDB_SC_PDBIF_WIDTH                       1u
#define PDB_SC_PDBIF(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBIF_SHIFT))&PDB_SC_PDBIF_MASK)
#define PDB_SC_PDBEN_MASK                        0x80u
#define PDB_SC_PDBEN_SHIFT                       7u
#define PDB_SC_PDBEN_WIDTH                       1u
#define PDB_SC_PDBEN(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBEN_SHIFT))&PDB_SC_PDBEN_MASK)
#define PDB_SC_TRGSEL_MASK                       0xF00u
#define PDB_SC_TRGSEL_SHIFT                      8u
#define PDB_SC_TRGSEL_WIDTH                      4u
#define PDB_SC_TRGSEL(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_TRGSEL_SHIFT))&PDB_SC_TRGSEL_MASK)
#define PDB_SC_PRESCALER_MASK                    0x7000u
#define PDB_SC_PRESCALER_SHIFT                   12u
#define PDB_SC_PRESCALER_WIDTH                   3u
#define PDB_SC_PRESCALER(x)                      (((uint32_t)(((uint32_t)(x))<<PDB_SC_PRESCALER_SHIFT))&PDB_SC_PRESCALER_MASK)
#define PDB_SC_DMAEN_MASK                        0x8000u
#define PDB_SC_DMAEN_SHIFT                       15u
#define PDB_SC_DMAEN_WIDTH                       1u
#define PDB_SC_DMAEN(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_DMAEN_SHIFT))&PDB_SC_DMAEN_MASK)
#define PDB_SC_SWTRIG_MASK                       0x10000u
#define PDB_SC_SWTRIG_SHIFT                      16u
#define PDB_SC_SWTRIG_WIDTH                      1u
#define PDB_SC_SWTRIG(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_SWTRIG_SHIFT))&PDB_SC_SWTRIG_MASK)
#define PDB_SC_PDBEIE_MASK                       0x20000u
#define PDB_SC_PDBEIE_SHIFT                      17u
#define PDB_SC_PDBEIE_WIDTH                      1u
#define PDB_SC_PDBEIE(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_SC_PDBEIE_SHIFT))&PDB_SC_PDBEIE_MASK)
#define PDB_SC_LDMOD_MASK                        0xC0000u
#define PDB_SC_LDMOD_SHIFT                       18u
#define PDB_SC_LDMOD_WIDTH                       2u
#define PDB_SC_LDMOD(x)                          (((uint32_t)(((uint32_t)(x))<<PDB_SC_LDMOD_SHIFT))&PDB_SC_LDMOD_MASK)
/* MOD Bit Fields */
#define PDB_MOD_MOD_MASK                         0xFFFFu
#define PDB_MOD_MOD_SHIFT                        0u
#define PDB_MOD_MOD_WIDTH                        16u
#define PDB_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_MOD_MOD_SHIFT))&PDB_MOD_MOD_MASK)
/* CNT Bit Fields */
#define PDB_CNT_CNT_MASK                         0xFFFFu
#define PDB_CNT_CNT_SHIFT                        0u
#define PDB_CNT_CNT_WIDTH                        16u
#define PDB_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_CNT_CNT_SHIFT))&PDB_CNT_CNT_MASK)
/* IDLY Bit Fields */
#define PDB_IDLY_IDLY_MASK                       0xFFFFu
#define PDB_IDLY_IDLY_SHIFT                      0u
#define PDB_IDLY_IDLY_WIDTH                      16u
#define PDB_IDLY_IDLY(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_IDLY_IDLY_SHIFT))&PDB_IDLY_IDLY_MASK)
/* C1 Bit Fields */
#define PDB_C1_EN_MASK                           0xFFu
#define PDB_C1_EN_SHIFT                          0u
#define PDB_C1_EN_WIDTH                          8u
#define PDB_C1_EN(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_C1_EN_SHIFT))&PDB_C1_EN_MASK)
#define PDB_C1_TOS_MASK                          0xFF00u
#define PDB_C1_TOS_SHIFT                         8u
#define PDB_C1_TOS_WIDTH                         8u
#define PDB_C1_TOS(x)                            (((uint32_t)(((uint32_t)(x))<<PDB_C1_TOS_SHIFT))&PDB_C1_TOS_MASK)
#define PDB_C1_BB_MASK                           0xFF0000u
#define PDB_C1_BB_SHIFT                          16u
#define PDB_C1_BB_WIDTH                          8u
#define PDB_C1_BB(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_C1_BB_SHIFT))&PDB_C1_BB_MASK)
/* S Bit Fields */
#define PDB_S_ERR_MASK                           0xFFu
#define PDB_S_ERR_SHIFT                          0u
#define PDB_S_ERR_WIDTH                          8u
#define PDB_S_ERR(x)                             (((uint32_t)(((uint32_t)(x))<<PDB_S_ERR_SHIFT))&PDB_S_ERR_MASK)
#define PDB_S_CF_MASK                            0xFF0000u
#define PDB_S_CF_SHIFT                           16u
#define PDB_S_CF_WIDTH                           8u
#define PDB_S_CF(x)                              (((uint32_t)(((uint32_t)(x))<<PDB_S_CF_SHIFT))&PDB_S_CF_MASK)
/* DLY Bit Fields */
#define PDB_DLY_DLY_MASK                         0xFFFFu
#define PDB_DLY_DLY_SHIFT                        0u
#define PDB_DLY_DLY_WIDTH                        16u
#define PDB_DLY_DLY(x)                           (((uint32_t)(((uint32_t)(x))<<PDB_DLY_DLY_SHIFT))&PDB_DLY_DLY_MASK)
/* POEN Bit Fields */
#define PDB_POEN_POEN_MASK                       0xFFu
#define PDB_POEN_POEN_SHIFT                      0u
#define PDB_POEN_POEN_WIDTH                      8u
#define PDB_POEN_POEN(x)                         (((uint32_t)(((uint32_t)(x))<<PDB_POEN_POEN_SHIFT))&PDB_POEN_POEN_MASK)
/* POnDLY_PODLY Bit Fields */
#define PDB_POnDLY_PODLY_DLY2_MASK               0xFFFFu
#define PDB_POnDLY_PODLY_DLY2_SHIFT              0u
#define PDB_POnDLY_PODLY_DLY2_WIDTH              16u
#define PDB_POnDLY_PODLY_DLY2(x)                 (((uint32_t)(((uint32_t)(x))<<PDB_POnDLY_PODLY_DLY2_SHIFT))&PDB_POnDLY_PODLY_DLY2_MASK)
#define PDB_POnDLY_PODLY_DLY1_MASK               0xFFFF0000u
#define PDB_POnDLY_PODLY_DLY1_SHIFT              16u
#define PDB_POnDLY_PODLY_DLY1_WIDTH              16u
#define PDB_POnDLY_PODLY_DLY1(x)                 (((uint32_t)(((uint32_t)(x))<<PDB_POnDLY_PODLY_DLY1_SHIFT))&PDB_POnDLY_PODLY_DLY1_MASK)
/* POnDLY_ACCESS16BIT_DLY2 Bit Fields */
#define PDB_POnDLY_ACCESS16BIT_DLY2_DLY2_MASK    0xFFFFu
#define PDB_POnDLY_ACCESS16BIT_DLY2_DLY2_SHIFT   0u
#define PDB_POnDLY_ACCESS16BIT_DLY2_DLY2_WIDTH   16u
#define PDB_POnDLY_ACCESS16BIT_DLY2_DLY2(x)      (((uint16_t)(((uint16_t)(x))<<PDB_POnDLY_ACCESS16BIT_DLY2_DLY2_SHIFT))&PDB_POnDLY_ACCESS16BIT_DLY2_DLY2_MASK)
/* POnDLY_ACCESS16BIT_DLY1 Bit Fields */
#define PDB_POnDLY_ACCESS16BIT_DLY1_DLY1_MASK    0xFFFFu
#define PDB_POnDLY_ACCESS16BIT_DLY1_DLY1_SHIFT   0u
#define PDB_POnDLY_ACCESS16BIT_DLY1_DLY1_WIDTH   16u
#define PDB_POnDLY_ACCESS16BIT_DLY1_DLY1(x)      (((uint16_t)(((uint16_t)(x))<<PDB_POnDLY_ACCESS16BIT_DLY1_DLY1_SHIFT))&PDB_POnDLY_ACCESS16BIT_DLY1_DLY1_MASK)

/*!
 * @}
 */ /* end of group PDB_Register_Masks */


/*!
 * @}
 */ /* end of group PDB_Peripheral_Access_Layer */



/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */


/*!
 * @}
 */ /* end of group Peripheral_access_layer_S32K144 */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility for S32K144
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols_S32K144 Backward Compatibility for S32K144
 * @{
 */

/* No backward compatibility issues. */

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols_S32K144 */


#else /* #if !defined(S32K144_H_) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0400u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0400u) */
#endif  /* #if !defined(S32K144_H_) */

/* S32K144.h, eof. */
