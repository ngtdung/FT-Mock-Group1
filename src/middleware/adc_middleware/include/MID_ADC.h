/**
*   @file    ADC_MiddleWare.h
*
*   @version 1.0.0
*
*   @addtogroup ADC
*   @{
*/
#ifndef __ADC_MIDDLEWARE_H__
#define __ADC_MIDDLEWARE_H__

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
#include "types_common.h"
#include "Driver_Header.h"

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
typedef void (*ADC_Middleware_Callback)(uint16_t data); /* Definition of ADC call back */

typedef enum{
    ADC_MIDDLEWARE_RETURN_CODE_ERROR     = 0u,
    ADC_MIDDLEWARE_RETURN_CODE_SUCCESSED = 1u
}MID_ADC_ReturnCode_type;

typedef struct MID_ADC_ConfigStruct_type
{
    ADC_Type *adcHwUnitId;
    ADC_Channel_type channel;
    ADC_Middleware_Callback callback;
    Node_Config_Data_Struct_type *nodeConfigPtr;
} MID_ADC_ConfigStruct_type;

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
MID_ADC_ReturnCode_type MID_ADC_Init(MID_ADC_ConfigStruct_type *adcConfig);

uint16_t MID_ADC_ReadData(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_MIDDLEWARE_H__ */
