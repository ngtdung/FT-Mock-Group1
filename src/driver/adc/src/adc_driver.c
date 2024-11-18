/**
*   @file    adc_driver.c
*
*   @version 1.0.0
*
*   @addtogroup ADC
*   @{
*/
#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "adc_driver.h"
#include "devassert.h"
#include <stddef.h>

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/**
 * @brief          Maximum Precision channel for ADC range from 0 to 16
 */
#define ADC_ST_PRICISION_CH_U8           (0U)
#define ADC_ED_PRICISION_CH_U8           (16U)
#define ADC_INVALID_CHANEL               (ADCChannel_t)(16U)

/* Register to pick data */
#define CURRENT_DATA_RESULT_REG           (4U)
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static volatile uint16_t s_latestData = 0;
static IRQCallBack ADC_CallBack = NULL;
static uint8_t s_currentChannel = 0;

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

ADC_Driver_ReturnCode_t ADCDriver_Init(uint8_t Adc_instance, ADCChannel_t channel, IRQCallBack CallBackFunction)
{
    ADC_Driver_ReturnCode_t retVal = Adc_driver_status_error;
    PDB_Type * PDBTarget = NULL;
    uint8_t PDBIndex = 0;
    ADC_Type *adcUserConfig = NULL;

    if( Adc_instance == 0U)
    {
        adcUserConfig = ADC0;
    }
    else if( Adc_instance == 1U)
    {
        adcUserConfig = ADC1;
    }
    else
    {
        /* nothing */
    }

    DEV_ASSERT(channel <= ADC_ED_PRICISION_CH_U8);

    if (adcUserConfig == ADC0)
    {
        PDBTarget = PDB0;
        PDBIndex = PCC_PDB0_INDEX;
        retVal = Adc_driver_status_successed;
    }
    else if (adcUserConfig == ADC1)
    {
        PDBTarget = PDB1;
        PDBIndex = PCC_PDB1_INDEX;
        retVal = Adc_driver_status_successed;
    }
    else
    {
        /* nothing */
    }

    if (Adc_driver_status_successed == retVal)
    {
        adcUserConfig->SC3 = ADC_SC3_CAL_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
        /* Wait for completion */
        while(((adcUserConfig->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT) == 0)
        {};
        /* ADCH: Module disabled for conversions */
        adcUserConfig->SC1[CURRENT_DATA_RESULT_REG] = ADC_SC1_ADCH_MASK;
        /* ADIV = 0: Divide ratio = 1
           MODE = 1: 12-bit conversion */
        adcUserConfig->CFG1 = ADC_CFG1_ADIV(0) | ADC_CFG1_MODE(1);
        /* SMPLTS = 12: sample time is 13 ADC clks */
        adcUserConfig->CFG2 = ADC_CFG2_SMPLTS(12);
        /* ADTRG = 1: HW trigger */
        adcUserConfig->SC2 = ADC_SC2_ADTRG(1);
        /* ADCH = channel: External channel as ADC0 input */
        adcUserConfig->SC1[CURRENT_DATA_RESULT_REG] = ADC_SC1_ADCH(channel);
        /* ADCO = 0: One conversion performed
           AVGE,AVGS = 0: HW average function disabled */
        adcUserConfig->SC3 = 0x00000000;
        /* Enable bus clock in PDB */
        PCC->PCCn[PDBIndex] |= PCC_PCCn_CGC_MASK;
        /* PRESCALER = 6: clk divided by (64 x Mult factor) */
        PDBTarget->SC = PDB_SC_PRESCALER(6)
                        | PDB_SC_TRGSEL(15) /* TRGSEL = 15: Software trigger selected */
                        | PDB_SC_MULT(3) /* MULT = 3: Multiplication factor is 40 */
                        | PDB_SC_CONT_MASK; /* CONT = 1: Enable operation in continuous mode */
                        /* PDB Period = (System Clock / (Prescaler x Mult factor)) / Modulus */
                        /* PDB Period = (48 MHz / (64 x 40)) / 18750 */
                        /* PDB Period = (18750 Hz) / (18750) = 1 Hz */
        PDBTarget->MOD = 18750U;
        /* TOS = 10h: Pre-trigger 4 asserts with DLY match */
        /* EN = 10h: Pre-trigger 4 enabled */
        PDBTarget->CH[0].C1 = (PDB_C1_TOS(0x10) | PDB_C1_EN(0x10));
        /* Delay set to half the PDB period = 9375 */
        PDBTarget->CH[0].DLY[4] = 9375;
        /* Enable PDB. Load MOD and DLY */
        PDBTarget->SC |= PDB_SC_PDBEN_MASK | PDB_SC_LDOK_MASK;
        /* Single initial PDB trigger */
        PDBTarget->SC |= PDB_SC_SWTRIG_MASK;

        ADC_CallBack = CallBackFunction;
    }

    return retVal;
}

ADC_Driver_ReturnCode_t ADCDriver_EnableIRQ(uint8_t Adc_instance, ADCChannel_t channel)
{
    ADC_Driver_ReturnCode_t retVal = Adc_driver_status_error;
    IRQn_Type irqTarget;
    ADC_Type *adcUserConfig = NULL;

    DEV_ASSERT(channel <= ADC_ED_PRICISION_CH_U8);

    if( Adc_instance == 0U)
    {
        adcUserConfig = ADC0;
    }
    else if( Adc_instance == 1U)
    {
    	adcUserConfig = ADC1;
    }
    else
    {
        /* Do nothing */
    }

    if (ADC0 == adcUserConfig)
    {
        retVal = Adc_driver_status_successed;
        irqTarget = ADC0_IRQn;
    }
    else if (ADC1 == adcUserConfig)
    {
        retVal = Adc_driver_status_successed;
        irqTarget = ADC1_IRQn;
    }
    else
    {
        /* Do nothing */
    }

    if (Adc_driver_status_successed == retVal)
    {
        s_currentChannel = channel;
        S32_NVIC->ISER[(uint32_t)(irqTarget) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irqTarget) & (uint32_t)0x1FU));
#ifndef UNITTEST
        /* all interrupts are allow for activity */
//        __asm("cpsie i");
#endif
        /* Select External channel as ADC input, enable interrupt and clear COCO flag if set */
        adcUserConfig->SC1[CURRENT_DATA_RESULT_REG] = ADC_SC1_ADCH(channel) | ADC_SC1_AIEN_MASK;
    }

    return retVal;
}

/**
* @brief
* @details        Interrupt handler.
*
* @param[in]      void.
* @return         void.
*
*/
void ADC0_IRQHandler(void)
{
    s_latestData = ADC0->R[CURRENT_DATA_RESULT_REG];
    if (ADC_CallBack != NULL)
    {
        ADC_CallBack(s_latestData);
    }
}

/**
* @brief
* @details        Interrupt handler.
*
* @param[in]      void.
* @return         void.
*
*/
void ADC1_IRQHandler(void)
{
    s_latestData = ADC1->R[CURRENT_DATA_RESULT_REG];
    if (ADC_CallBack != NULL)
    {
        ADC_CallBack(s_latestData);
    }
}

#ifdef __cplusplus
}
#endif
