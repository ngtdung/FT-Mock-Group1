/**
*   @file    PORT_Driver.c
*
*   @version 1.0.0
*
*   @addtogroup PORT
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

#include "PORT_Driver.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define PORT_NUMBER_OF_PINS             17
#define PORT_EXTRACT_INSTANCE(value)    (uint8_t)(((value) & 0xE0) >> 5)
#define PORT_EXTRACT_PIN(value)         (uint8_t)((value) & 0x1F)

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

PORT_Type *g_portBase[PORT_MAX_INSTANCE] = IP_PORT_BASE_PTRS;

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


DRV_PORT_ReturnCode_type DRV_PORT_InitPin(PORT_PinConfig_type *pinConfig)
{
    DRV_PORT_ReturnCode_type retVal = DRV_PORT_RETURN_CODE_ERROR;
    uint8_t pin = PORT_EXTRACT_PIN(pinConfig->pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinConfig->pinCode);
    PORT_Type *base = g_portBase[port_instance];

    if ((pin < PORT_NUMBER_OF_PINS) && (port_instance < PORT_MAX_INSTANCE) && ((void *)0 != pinConfig))
    {
        retVal = DRV_PORT_RETURN_CODE_SUCCESSED;
    }

    if(DRV_PORT_RETURN_CODE_SUCCESSED == retVal)
    {
        /* Pullup/pulldown configure */
        if (PORT_PULL_ENABLE == pinConfig->userConfig.isPullEnable)
        {
            base->PCR[pin] |= PORT_PCR_PE_MASK;
            if (PORT_INTERNAL_PULL_DOWN == pinConfig->userConfig.pullSelect)
            {
                base->PCR[pin] &= PORT_PCR_PS_MASK;
            }
            else
            {
                base->PCR[pin] |= PORT_PCR_PS_MASK;
            }
        }
        /* Passive filter configure */
        if (PORT_PASSIVE_FILTER_ENABLE == pinConfig->userConfig.isPassiveFilterEnable)
        {
            base->PCR[pin] |= PORT_PCR_PFE_MASK;
        }
        /* Driver strength mode */
        if (PORT_DRIVER_STRENGTH_LOW == pinConfig->userConfig.driverStrengthMode)
        {
            base->PCR[pin] &= PORT_PCR_DSE_MASK;
        }
        else
        {
            base->PCR[pin] |= PORT_PCR_DSE_MASK;
        }
        /* Pin muxing control */
        if (PORT_MUX_ANALOG != pinConfig->userConfig.muxMode)
        {
            base->PCR[pin] &= PORT_PCR_MUX_MASK;
            base->PCR[pin] |= PORT_PCR_MUX((uint8_t)pinConfig->userConfig.muxMode);
        }
        /* Lock register */
        if (pinConfig->userConfig.isLockRegisterEnable)
        {
            base->PCR[pin] |= PORT_PCR_LK_MASK;
        }
        /* Interrupt configure */
        if (PORT_INT_DISABLE != pinConfig->userConfig.interruptMode)
        {
            base->PCR[pin] &= PORT_PCR_IRQC_MASK;
            base->PCR[pin] |= PORT_PCR_IRQC((uint8_t)pinConfig->userConfig.interruptMode);
        }
    }

    return retVal;
}

DRV_PORT_ReturnCode_type DRV_PORT_InitMultiplePin(PORT_PinConfig_type *arrayPinsConfig[], int8_t numberOfConfigPin)
{
    DRV_PORT_ReturnCode_type retVal = DRV_PORT_RETURN_CODE_SUCCESSED;

    if ((arrayPinsConfig == NULL) || (numberOfConfigPin <= 0))
    {
        retVal = DRV_PORT_RETURN_CODE_ERROR;
    }
    else
    {
        for (int8_t i = 0; i < numberOfConfigPin; i++)
        {
            /* Check if a Pin configuration is valid or not */
            if (arrayPinsConfig[i] == NULL)
            {
                retVal = DRV_PORT_RETURN_CODE_ERROR;
                break;
            }

            /* Check if init a pin success or not */
            retVal = DRV_PORT_InitPin(arrayPinsConfig[i]);

            if (retVal != DRV_PORT_RETURN_CODE_SUCCESSED)
            {
                break;
            }
        }
    }

    return retVal;
}

uint8_t DRV_PORT_ReadInterruptFlagPin(uint8_t pinCode)
{
    uint8_t pin = PORT_EXTRACT_PIN(pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
    PORT_Type *base = g_portBase[port_instance];

    assert(pin < PORT_NUMBER_OF_PINS);
    assert(port_instance < PORT_MAX_INSTANCE);
    return (uint8_t)((base->PCR[pin] & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT);
}

void DRV_PORT_ClearInterruptFlagPin(uint8_t pinCode)
{
    uint8_t pin = PORT_EXTRACT_PIN(pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
    PORT_Type *base = g_portBase[port_instance];

    assert(pin < PORT_NUMBER_OF_PINS);
    assert(port_instance < PORT_MAX_INSTANCE);
    base->PCR[pin] |= (1 << PORT_PCR_ISF_SHIFT);
}

DRV_PORT_ReturnCode_type DRV_PORT_DeinitPin(uint8_t pinCode)
{
    DRV_PORT_ReturnCode_type retVal = DRV_PORT_RETURN_CODE_ERROR;
    uint8_t pin = PORT_EXTRACT_PIN(pinCode);
    uint8_t port_instance = PORT_EXTRACT_INSTANCE(pinCode);
    PORT_Type *base = g_portBase[port_instance];

    if ((pin < PORT_NUMBER_OF_PINS) && (port_instance < PORT_MAX_INSTANCE))
    {
        retVal == DRV_PORT_RETURN_CODE_SUCCESSED;
    }

    if (DRV_PORT_RETURN_CODE_SUCCESSED == retVal)
    {
        /* Avoid write into reserved bit */
        base->PCR[pin] &= PORT_PCR_PS_MASK;
        base->PCR[pin] &= PORT_PCR_PE_MASK;
        base->PCR[pin] &= PORT_PCR_PFE_MASK;
        base->PCR[pin] &= PORT_PCR_DSE_MASK;
        base->PCR[pin] &= PORT_PCR_MUX_MASK;
        base->PCR[pin] &= PORT_PCR_LK_MASK;
        base->PCR[pin] &= PORT_PCR_IRQC_MASK;
        /* Write 1 to clear */
        base->PCR[pin] |= PORT_PCR_ISF_MASK;
    }

    return retVal;
}

void DRV_PORT_DeinitMultiplePin(uint8_t *arrayPinCode, uint8_t numberOfConfigPin)
{
    if (((void *)0 != arrayPinCode) && (0 != numberOfConfigPin))
    {
        while(numberOfConfigPin)
        {
            DRV_PORT_DeinitPin(arrayPinCode[numberOfConfigPin - 1]);
            numberOfConfigPin--;
        }
    }
}

#ifdef __cplusplus
}
#endif
