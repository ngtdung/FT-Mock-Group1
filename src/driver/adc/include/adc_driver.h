/**
*   @file    adc_driver.h
*
*   @version 1.0.0
*
*   @addtogroup ADC
*   @{
*/
#ifndef __ADC_DRIVER_H__
#define __ADC_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <stdint.h>
#include "S32K144.h"

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
typedef enum ADC_Driver_ReturnCode_t
{
    Adc_driver_status_error     = 0u,
    Adc_driver_status_successed = 1u
} ADC_Driver_ReturnCode_t;

typedef enum ADCChannel_t {
    ADC_Channel0  = 0,
    ADC_Channel1  = 1,
    ADC_Channel2  = 2,
    ADC_Channel3  = 3,
    ADC_Channel4  = 4,
    ADC_Channel5  = 5,
    ADC_Channel6  = 6,
    ADC_Channel7  = 7,
    ADC_Channel8  = 8,
    ADC_Channel9  = 9,
    ADC_Channel10 = 10,
    ADC_Channel11 = 11,
    ADC_Channel12 = 12,
    ADC_Channel13 = 13,
    ADC_Channel14 = 14,
    ADC_Channel15 = 15
} ADCChannel_t;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef void (*IRQCallBack)(uint16_t dataOrigin);

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief          Initializes the ADC hardware unit and the driver.
* @details        This function will initialize both the ADC HW unit and the driver structures.
*
* @param[in]      channel: select external channel set as input to read ADC data
*                 Adc_instance as ADC0 or ADC1 selection
*                 CallBackFunction
*
* @return         - Adc_driver_status_successed      All data input is valid
*                 - Adc_driver_status_error
*
* @api
*
* @post           Initializes the driver.
*/
ADC_Driver_ReturnCode_t ADCDriver_Init(uint8_t Adc_instance, ADCChannel_t channel, IRQCallBack CallBackFunction);
/**
* @brief          Enables ADC interrupt for the requested ADC0/ADC1 with Channel 0-15/0-15.
* @details        This function will enable the HW trigger source depend on PDB signal
*
* @param[in]      channel: select external channel set as input to read ADC data
*                 Adc_instance as ADC0 or ADC1 selection
*
* @return         - Adc_driver_status_successed      All data input is valid
*                 - Adc_driver_status_error
*
* @api
*/
ADC_Driver_ReturnCode_t ADCDriver_EnableIRQ(uint8_t Adc_instance, ADCChannel_t channel);

void ADC0_IRQHandler(void);
void ADC1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_DRIVER_H__ */
