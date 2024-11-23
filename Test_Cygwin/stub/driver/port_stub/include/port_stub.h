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
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */
#ifndef _IO
#ifndef PORT_STUB_H
#define PORT_STUB_H

#define     __I
#define     __O
#define     __IO
#endif
/** PORT - Size of Registers Arrays */
#define PORT_PCR_COUNT                            32u

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[PORT_PCR_COUNT];               /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
  __O  uint32_t GICLR;                             /**< Global Interrupt Control Low Register, offset: 0x88 */
  __O  uint32_t GICHR;                             /**< Global Interrupt Control High Register, offset: 0x8C */
  uint8_t RESERVED_0[16];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
  uint8_t RESERVED_1[28];
  __IO uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
  __IO uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
  __IO uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type, *PORT_MemMapPtr;

/** Number of instances of the PORT module. */
#define PORT_INSTANCE_COUNT                      (5u)

/* PORT - Peripheral instance base addresses */

extern PORT_Type* IP_PORTA;
extern PORT_Type* IP_PORTB;
extern PORT_Type* IP_PORTC;
extern PORT_Type* IP_PORTD;
extern PORT_Type* IP_PORTE;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
/*! @{ */

#define PORT_PCR_PS_MASK                         (0x1U)
#define PORT_PCR_PS_SHIFT                        (0U)
#define PORT_PCR_PS_WIDTH                        (1U)
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)

#define PORT_PCR_PE_MASK                         (0x2U)
#define PORT_PCR_PE_SHIFT                        (1U)
#define PORT_PCR_PE_WIDTH                        (1U)
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)

#define PORT_PCR_PFE_MASK                        (0x10U)
#define PORT_PCR_PFE_SHIFT                       (4U)
#define PORT_PCR_PFE_WIDTH                       (1U)
#define PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PFE_SHIFT)) & PORT_PCR_PFE_MASK)

#define PORT_PCR_DSE_MASK                        (0x40U)
#define PORT_PCR_DSE_SHIFT                       (6U)
#define PORT_PCR_DSE_WIDTH                       (1U)
#define PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_DSE_SHIFT)) & PORT_PCR_DSE_MASK)

#define PORT_PCR_MUX_MASK                        (0x700U)
#define PORT_PCR_MUX_SHIFT                       (8U)
#define PORT_PCR_MUX_WIDTH                       (3U)
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)

#define PORT_PCR_LK_MASK                         (0x8000U)
#define PORT_PCR_LK_SHIFT                        (15U)
#define PORT_PCR_LK_WIDTH                        (1U)
#define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_LK_SHIFT)) & PORT_PCR_LK_MASK)

#define PORT_PCR_IRQC_MASK                       (0xF0000U)
#define PORT_PCR_IRQC_SHIFT                      (16U)
#define PORT_PCR_IRQC_WIDTH                      (4U)
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)

#define PORT_PCR_ISF_MASK                        (0x1000000U)
#define PORT_PCR_ISF_SHIFT                       (24U)
#define PORT_PCR_ISF_WIDTH                       (1U)
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)
/*! @} */

/*! @name GPCLR - Global Pin Control Low Register */
/*! @{ */

#define PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT                    (0U)
#define PORT_GPCLR_GPWD_WIDTH                    (16U)
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)

#define PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT                    (16U)
#define PORT_GPCLR_GPWE_WIDTH                    (16U)
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)
/*! @} */

/*! @name GPCHR - Global Pin Control High Register */
/*! @{ */

#define PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT                    (0U)
#define PORT_GPCHR_GPWD_WIDTH                    (16U)
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)

#define PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT                    (16U)
#define PORT_GPCHR_GPWE_WIDTH                    (16U)
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)
/*! @} */

/*! @name GICLR - Global Interrupt Control Low Register */
/*! @{ */

#define PORT_GICLR_GIWE_MASK                     (0xFFFFU)
#define PORT_GICLR_GIWE_SHIFT                    (0U)
#define PORT_GICLR_GIWE_WIDTH                    (16U)
#define PORT_GICLR_GIWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GICLR_GIWE_SHIFT)) & PORT_GICLR_GIWE_MASK)

#define PORT_GICLR_GIWD_MASK                     (0xFFFF0000U)
#define PORT_GICLR_GIWD_SHIFT                    (16U)
#define PORT_GICLR_GIWD_WIDTH                    (16U)
#define PORT_GICLR_GIWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GICLR_GIWD_SHIFT)) & PORT_GICLR_GIWD_MASK)
/*! @} */

/*! @name GICHR - Global Interrupt Control High Register */
/*! @{ */

#define PORT_GICHR_GIWE_MASK                     (0xFFFFU)
#define PORT_GICHR_GIWE_SHIFT                    (0U)
#define PORT_GICHR_GIWE_WIDTH                    (16U)
#define PORT_GICHR_GIWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GICHR_GIWE_SHIFT)) & PORT_GICHR_GIWE_MASK)

#define PORT_GICHR_GIWD_MASK                     (0xFFFF0000U)
#define PORT_GICHR_GIWD_SHIFT                    (16U)
#define PORT_GICHR_GIWD_WIDTH                    (16U)
#define PORT_GICHR_GIWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GICHR_GIWD_SHIFT)) & PORT_GICHR_GIWD_MASK)
/*! @} */

/*! @name ISFR - Interrupt Status Flag Register */
/*! @{ */

#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT                      (0U)
#define PORT_ISFR_ISF_WIDTH                      (32U)
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)
/*! @} */

/*! @name DFER - Digital Filter Enable Register */
/*! @{ */

#define PORT_DFER_DFE_MASK                       (0xFFFFFFFFU)
#define PORT_DFER_DFE_SHIFT                      (0U)
#define PORT_DFER_DFE_WIDTH                      (32U)
#define PORT_DFER_DFE(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_DFER_DFE_SHIFT)) & PORT_DFER_DFE_MASK)
/*! @} */

/*! @name DFCR - Digital Filter Clock Register */
/*! @{ */

#define PORT_DFCR_CS_MASK                        (0x1U)
#define PORT_DFCR_CS_SHIFT                       (0U)
#define PORT_DFCR_CS_WIDTH                       (1U)
#define PORT_DFCR_CS(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_DFCR_CS_SHIFT)) & PORT_DFCR_CS_MASK)
/*! @} */

/*! @name DFWR - Digital Filter Width Register */
/*! @{ */

#define PORT_DFWR_FILT_MASK                      (0x1FU)
#define PORT_DFWR_FILT_SHIFT                     (0U)
#define PORT_DFWR_FILT_WIDTH                     (5U)
#define PORT_DFWR_FILT(x)                        (((uint32_t)(((uint32_t)(x)) << PORT_DFWR_FILT_SHIFT)) & PORT_DFWR_FILT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PORT_Register_Masks */

/*!
 * @}
 */ /* end of group PORT_Peripheral_Access_Layer */


/* S32K144.h, eof. */
#endif /* PORT_STUB_H */